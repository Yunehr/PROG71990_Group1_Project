
#include <stdio.h>
#include "header.h"


int main(void) {
	PTTASK tasks[MAX_TASKS] = { NULL };
	int taskCount = 0;
	int MenuInput;
	int validInput;

	do {
		DisplayMenu();
		validInput = scanf_s("%d", &MenuInput);

		if (validInput != 1) {
			while (getchar() != '\n');
			printf("Invalid Input. Please enter a number between 1 and 8:\n");

		}
		else if (MenuInput < 1 || MenuInput > 8) {
			printf("Invalid Input. Please enter a number between 1 and 8: \n");
		}
		switch (MenuInput)
		{
		case 1:
			AddTask(tasks, &taskCount);
			break;
		case 2:
			DeleteTask(tasks, &taskCount);
			break;
		case 3:
			UpdateTask(tasks, taskCount);
			break;
		case 4:
			//display a single task:
			break;
		case 5:
			//display a range of tasks;
			break;
		case 6:
			//display a range of tasks;
			break;
		case 7:
			//search for a task;
			break;
		case 8:
			printf("Quitting the program");
			for (int i = 0; i < taskCount; i++) {
				free(tasks[i]);
			}
			break;
		default:
			printf("Invalid input please try again");
			break;
		}
	} while (MenuInput != 8);

	return 0;

}