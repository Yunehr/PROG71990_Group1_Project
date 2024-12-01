#include "header.h"


void DisplayMenu(void) {

    printf("_________________________________________________________\n");
    printf("|To choose a function, enter its number:                |\n");
    printf("|1) Add a new task                                      |\n");
    printf("|2) Delete an existing task                             |\n");
    printf("|3) Update an exsisting task                            |\n");
    printf("|4) Display a single task                               |\n");
    printf("|5) Display a range of tasks                            |\n");
    printf("|6) Search for a task                                   |\n");
    printf("|7) Quit                                                |\n");
    printf("_________________________________________________________\n");
}
void AddTask(PTTASK tasks[], int* taskCount) {
    if (*taskCount >= MAX_TASKS) { //checks we did not create too many tasks
        printf("Task list is full, cannot add more tasks \n");
        return;
    }
    PTTASK newTask = (PTTASK)malloc(sizeof(TASK));
    if (!newTask) {
        printf("memory Allocation failed");
        return;
    }
    newTask->id = *taskCount + 1;

    printf("Please enter task name: \n");
    fgets(newTask->name, sizeof(newTask->name), stdin);
    newTask->name[strcspn(newTask->name, "\n")] = '\0';

    printf("Please enter the task description: \n");
    fgets(newTask->description, sizeof(newTask->description), stdin);
    newTask->description[strcspn(newTask->description, "\n")] = '\0';

    tasks[*taskCount] = newTask;
    (*taskCount)++;

    //Need Save Function

    printf("Task Added Successfully!\n");

}
void DeleteTask(PTTASK tasks[], int* taskCount) {
    if (*taskCount == 0) {
        printf("There are no tasks to delete.\n");
        return;
    }
    int id;
    printf("Please enter the task ID to delete:\n");
    scanf_s("%d", &id);
    int found = 0;
    for (int i = 0; i < *taskCount; ++i) {
        if (tasks[i]->id == id) {
            free(tasks[i]);
            for (int j = i; j < *taskCount - 1; ++j) {
                tasks[j] = tasks[j + 1];
            }
            tasks[*taskCount - 1] = NULL;
            (*taskCount)--;
            found = 1;
            printf("Task Deleted Successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Task not found.\n");
    }
} // Needs a save function add
void UpdateTask(PTTASK tasks[], int taskCount) {
    if (taskCount == 0) {
        printf("There are no tasks to update.\n");
        return;
    }
    int id;
    printf("Please enter the task ID to update:\n");
    scanf_s("%d", &id);
    int found = 0;
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i]->id == id) {
            printf("Enter new task name:\n");
            fgets(tasks[i]->name, sizeof(tasks[i]->name), stdin);
            tasks[i]->name[strcspn(tasks[i]->name, "\n")] = '\0';

            printf("Enter new task description:\n");
            fgets(tasks[i]->description, sizeof(tasks[i]->description), stdin);
            tasks[i]->description[strcspn(tasks[i]->description, "\n")] = '\0';

            printf("Tasks updated successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Task ID not found.\n");
    }

}

//Use char name[] to compare with tasks->data[i].name through strcmp.
//If found, return int i.
int FindByName(TASK* tasks, char name[]) {
    int i = 0;
    for (i = 0; i < tasks->id; i++) {
        if (strcmp(tasks->data[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void DisplaySingle(const TASK* tasks) {
    //Set a char to search
    char name[NAME_LENGTH] = { 0 };
    printf("Pleast input the name of task you want to search:");
    scanf("%s", name);
    //Use temp to get int i, then print the tasks->data[temp].name and description.
    int temp = FindByName(tasks, name);
    if (temp == EOF) {
        printf("The task doesn't exist.\n");
        return;
    }
    printf("%-20s\t%-100s\n", "name", "description");
    printf("%-20s\t%-100s\n",
        tasks->data[temp].name,
        tasks->data[temp].description);
}

void DisplayRange(const TASK* tasks) {

}

void DisplayAll(const TASK* tasks) {
    // \t means one press of Tab.
    printf("%-20s\t%-100s\n", "name", "description");
    int i = 0;
    for (i = 0; i < tasks->id; i++) {
        printf("%-20s\t%-100s\n",
            tasks->data[i].name,
            tasks->data[i].description);
    }
}

