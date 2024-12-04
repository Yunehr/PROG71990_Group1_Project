#include "header.h"
//#include <stdio.h>
#define FILENAME "tasks.txt"


int main(void) {
	PTTASK tasks[MAX_TASKS] = { NULL }; // NULL is potentially causing errors in line 30
	int taskCount = 0;
	int MenuInput = 0;
	// int validInput = 0;		// is this needed still???

	bool Check = ReadTaskListFromFile(&tasks, FILENAME);
	if (Check == false) {
		ReadTaskListFromFile(&tasks, FILENAME);
	}

	do {
		DisplayMenu();
		//If Menuinput = 0 loop will end, so this would be fine.
		scanf_s("%d", &MenuInput);

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
			AddTask(&tasks);	//TODO: verify if tasks.data == NULL or initialize  to zero when tasks is created
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

			printf("Quitting the program");
			WriteTaskListToFile(tasks, FILENAME);
			for (int i = 0; i < taskCount; i++) {
				free(tasks[i]);
			}
			break;
		default:
			printf("Invalid input please try again");
			break;
		}
	} while (MenuInput);


	return 0;

}