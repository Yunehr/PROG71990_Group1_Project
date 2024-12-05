#include "header.h"
#define FILENAME "tasks.txt"

int main(void) {
    // Allocate memory for tasks dynamically
    TASK* tasks = (TASK*)malloc(sizeof(TASK));
    if (tasks == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    tasks->count = 0;

    printf("Checking file for Previous data...\n");
    bool Check = ReadTaskListFromFile(tasks, FILENAME);
    if (Check) { printf("Completed\n"); }
    if (!Check) {
        fprintf(stderr, "Initial read failed, file will be created\n");
    }

    int MenuInput = 0;
    do {
        DisplayMenu();
        int validInput = scanf("%d", &MenuInput);
        if (validInput != 1 || MenuInput < 0 || MenuInput > 7) {
            while (getchar() != '\n');
            printf("Invalid Input. Please enter a number between 0 and 7:\n");
            continue;
        }

        switch (MenuInput) {
        case 1:
            AddTask(tasks);
            break;
        case 2:
            DeleteTask(tasks);
            break;
        case 3:
            UpdateTask(tasks);
            break;
        case 4:
            DisplaySingle(tasks);
            break;
        case 5:
            DisplayByRange(tasks);
            break;
        case 6:
            DisplayAll(tasks);
            break;
        case 7:
            SearchTask(tasks);
            break;
        case 0:
            printf("Saving To File...\n");
            //WriteTaskListToFile(tasks, FILENAME);
            if (WriteTaskListToFile(tasks, FILENAME)) { printf("Completed\n"); }
            printf("Quitting the program\n");
            break;
        default:
            printf("Invalid input, please try again\n");
            break;
        }
    } while (MenuInput != 0);

    // Free dynamically allocated memory
    free(tasks);

    return 0;
}