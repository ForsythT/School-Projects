#include "pubsub.h"
Queue g_buffer;

struct Event ProduceEvent() {
    Event e;
    e.value = getRandom(1, 1000);
    e.sleep_time = getRandom(2, 9);
    sleep(getRandom(3, 7)); // wait before "producing" a new item
    return e;
}

// push/enqueue event into buffer
void PublishEvent(Event e) {
    enqueue(&g_buffer, e);
}

// pull/dequeue event out of buffer
struct Event SubscribeEvent() {
    return *(dequeue(&g_buffer));
}

/*int main(void)
{
    int i;
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);
    return 0;
}*/
