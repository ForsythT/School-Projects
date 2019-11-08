#include "list.h"

int is_int(char [3]);

int main (){
	char filename[20];
	struct list l;
	FILE *fileptr;
	//int yes = 1;
	char num[3], num2[3], num3[3], pos[3]; //We will read positive integers 0-99
	
	init(&l);	
	printf("Enter filename: ");
	scanf("%s", filename);
	fileptr = fopen (filename,"r");
	
	//continue reading until we are at the end of the file
	while (fscanf(fileptr, "%s", num)!=EOF){
		if(is_int(num) == 1){
			printf("Number is: %d\n", atoi(num));
			printf("Here\n");
			push_front(&l, atoi(num)); //push to front of list
			printf("Here\n");
			push_back(&l, atoi(num)); //push to back of list
			printf("Here\n");
		}
	
	}
	printf("\n");
	printf("Length of list: %d\n", length(l)); //print length of the list
	print(l); //print the contents of the list
	printf("\n");

	sort_ascending(&l); //sort in ascending order
	printf("Ascending Order\n");
	print(l); //print the contents of the list
	printf("\n");

	sort_descending(&l); //sort in descending order
	printf("Descending Order\n");
	print(l); //print the contents of the list
	printf("\n");
	
	printf("Enter a number to be removed: "); //prompt user for the value/integer to remove
	scanf("%s", &num2);
	while(is_int(num2) != 1){
		printf("Enter a number to be removed: ");
		scanf("%s", &num2);
	}
	remove_val(&l, atoi(num2)); //remove specific value/integer from the list
	print(l); //print the contents of the list
	
	printf("Enter a number to add: "); //prompt user for item/int to add and location in list
	scanf("%s", &num3);
	while(is_int(num3) != 1){
		printf("Enter a number to add: ");
		scanf("%s", &num3);
	}
	printf("Enter a position to add it at: ");
	scanf("%s", &pos);
	while(is_int(pos) != 1){
		printf("Enter a position to add it at: ");
		scanf("%s", &pos);
	}
	
	insert(&l, atoi(num3), atoi(pos)); //insert int into specific location
	print(l);//print the contents of the list
	
	clear(&l);//clear list – no memory leaks
	fclose (fileptr);
	return 0;
}

int is_int(char num[3]){
	int i = 0;
	for(i; i < strlen(num); i++){
		if(i < 2){
			if(num[i] < '0' || num[i] > '9'){
				printf("Invalid integer. Please only input integers between 0 and 99.\n");
				return 0;
			}
		}
		else{
			if(num[i] != '\0')
				printf("Invalid integer. Please only input integers between 0 and 99.\n");
				return 0;
		}
	}
	return 1;
}
