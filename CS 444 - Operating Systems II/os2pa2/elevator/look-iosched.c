/*
 * elevator clook implementation
 */
#include <linux/blkdev.h>
#include <linux/elevator.h>
#include <linux/bio.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/init.h>

struct look_data {
	struct list_head queue;
};

sector_t currPosition = -1;

static void look_merged_requests(struct request_queue *q, struct request *rq,
				 struct request *next)
{
	list_del_init(&next->queuelist);
}

static int look_dispatch(struct request_queue *q, int force)
{
	struct look_data *nd = q->elevator->elevator_data;

	if (!list_empty(&nd->queue)) {
		struct request *rq;
		rq = list_entry(nd->queue.next, struct request, queuelist);
		list_del_init(&rq->queuelist);
		elv_dispatch_sort(q, rq);
    currPosition = blk_rq_pos(rq);            //keep track of the disk head
    printk("C-Look Dispatch: %llu\n", blk_rq_pos(rq));      //print sector # to screen
		return 1;
	}
	return 0;
}

static void look_add_request(struct request_queue *q, struct request *rq)
{
	struct look_data *nd = q->elevator->elevator_data;
  struct list_head *curr;

  if(!list_empty(&nd->queue)){
    list_for_each(curr, &nd->queue){        //use macro from list.h to iterate over the list. This is the same as for (pos = (head)->next; pos != (head); pos = pos->next)
      struct request *r = list_entry(curr, struct request, queuelist);            //copy the current entry
      if(blk_rq_pos(rq) < currPosition){                            //check if request sector is lower than current disk head position
        if(blk_rq_pos(rq) <= blk_rq_pos(r))                         //if the current iteration is greater than request, insert request here
          break;
      }else{                                                      //else request sector is bigger than current head position
        if(blk_rq_pos(rq) <= blk_rq_pos(r))                       //insert request at sorted position
          break;
      }
    }
    list_add_tail(&rq->queuelist, curr);                          //add the request
  }else{
    list_add(&rq->queuelist, &nd->queue);                         //add request if list was empty
  }
  printk("C-Look Add: %llu\n", blk_rq_pos(rq));                   //print what was added
}

static struct request *
look_former_request(struct request_queue *q, struct request *rq)
{
	struct look_data *nd = q->elevator->elevator_data;

	if (rq->queuelist.prev == &nd->queue)
		return NULL;
	return list_entry(rq->queuelist.prev, struct request, queuelist);
}

static struct request *
look_latter_request(struct request_queue *q, struct request *rq)
{
	struct look_data *nd = q->elevator->elevator_data;

	if (rq->queuelist.next == &nd->queue)
		return NULL;
	return list_entry(rq->queuelist.next, struct request, queuelist);
}

static int look_init_queue(struct request_queue *q, struct elevator_type *e)
{
	struct look_data *nd;
	struct elevator_queue *eq;

	eq = elevator_alloc(q, e);
	if (!eq)
		return -ENOMEM;

	nd = kmalloc_node(sizeof(*nd), GFP_KERNEL, q->node);
	if (!nd) {
		kobject_put(&eq->kobj);
		return -ENOMEM;
	}
	eq->elevator_data = nd;

	INIT_LIST_HEAD(&nd->queue);

	spin_lock_irq(q->queue_lock);
	q->elevator = eq;
	spin_unlock_irq(q->queue_lock);
	return 0;
}

static void look_exit_queue(struct elevator_queue *e)
{
	struct look_data *nd = e->elevator_data;

	BUG_ON(!list_empty(&nd->queue));
	kfree(nd);
}

static struct elevator_type elevator_look = {
	.ops = {
		.elevator_merge_req_fn		= look_merged_requests,
		.elevator_dispatch_fn		= look_dispatch,
		.elevator_add_req_fn		= look_add_request,
		.elevator_former_req_fn		= look_former_request,
		.elevator_latter_req_fn		= look_latter_request,
		.elevator_init_fn		= look_init_queue,
		.elevator_exit_fn		= look_exit_queue,
	},
	.elevator_name = "look",
	.elevator_owner = THIS_MODULE,
};

static int __init look_init(void)
{
	return elv_register(&elevator_look);
}

static void __exit look_exit(void)
{
	elv_unregister(&elevator_look);
}

module_init(look_init);
module_exit(look_exit);




MODULE_AUTHOR("Group 9");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("C-Look IO scheduler");
