#include <stdio.h>
#include "header.h"

int main(void) {
	PTTASK tasks[MAX_TASKS] = { NULL };
	int taskCount = 0;
	int MenuInput;
	int validInput;

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
			AddTask(tasks, &taskCount);
			break;
		case DELETE:
			DeleteTask(tasks, &taskCount);
			break;
		case UPDATE:
			UpdateTask(tasks, taskCount);
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
			break;
		case EXIT:
			printf("Quitting the program");
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