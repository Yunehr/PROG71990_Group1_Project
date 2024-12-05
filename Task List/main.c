#include "header.h"
#define _CRT_SECURE_NO_WARNINGS

int main(void) {
	TASK tasks;
	int MenuInput = 0;
	InitiateTask(&tasks);
	do {
		DisplayMenu();
		//If Menuinput = 0 loop will end, so this would be fine.
		printf("Please choose:");
		scanf("%d", &MenuInput);

		//if (validInput != 1) {
		//	while (getchar() != '\n');
		//	printf("Invalid Input. Please enter a number between 1 and 8:\n");

		//}
		//else if (MenuInput < 1 || MenuInput > 8) {
		//	printf("Invalid Input. Please enter a number between 1 and 8: \n");
		//}
		switch (MenuInput)
		{
		case ADD:
			AddTask(&tasks);
			break;
		case DELETE:
			DeleteTask(&tasks);
			break;
		case UPDATE:
			UpdateTask(&tasks);
			break;
		case DISPLAYSINGLE:
			//display a single task:
			DisplaySingle(&tasks);
			break;
		case DISPLAYRANGE:
			//display a range of tasks;
			DisplayByRange(&tasks);
			break;
		case DISPLAYALL:
			//display a range of tasks;
			DisplayAll(&tasks);
			break;
		case SEARCH:
			//search for a task;
			SearchTask(&tasks);
			break;
		case EXIT:
			SaveTask(&tasks);
			DestroyTask(&tasks);
			break;
		default:
			printf("Invalid input please input again");
			break;
		}
	} while (MenuInput);


	return 0;

}