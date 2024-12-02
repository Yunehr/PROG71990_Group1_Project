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
    printf("|0) Quit                                                |\n");
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

//Use char name[] to compare with tasks->data[i].name through strcmp,if found, return int i.
//First I used this function in order to display single task.
//But I found if we add dates of the calender,using date is much more make sense.
//Finally this function would be used on search function by names.
int FindByName(TASK* tasks, char name[]) {
    int i = 0;
    for (i = 0; i < tasks->id; i++) {
        if (strcmp(tasks->data[i].name,name) == 0) {
            return i;
        }
    }
    //If didn't find, return EOF as -1.
    return EOF;
}

void DisplaySingle(const TASK* tasks) {
    //Set two ints to search
    int month = 0;
    int day = 0;
    printf("Pleast input the date of the task you want to search(Use format like 12.12):\n");
    scanf("%d.%d", &month,&day);
    //search the data to find the task in the same date.
    int i = 0;
    int found = 0;
    for (i = 0; i < tasks->id; i++) {
        //Check if a task exists for a specified date
        if (tasks->data[i].month == month &&
            tasks->data[i].day == day) {
            found = 1;
            //If found one,break and go to the next step.
            break;
        }
        //If not found,the value of found is the initial 0,so use the !found to print and return.
        if (!found) {
            printf("The task doesn't exist.\n");
            return;
        }
    }
    //If tasks exist,print the title "Month", "Day", "Name", "Description" first.
    //\t means one press of Tab.
    printf("%-2s\t%-2s\t%-20s\t%-100s\n", "Month", "Day", "Name", "Description");
    //Then use loop to print every task in the specific date, because there maybe not only one task in single date.
    for (i = 0; i < tasks->id; i++) {
        if (tasks->data[i].month == month &&
            tasks->data[i].day == day) {
            printf("%-2d\t%-2d\t%-20s\t%-100s\n",
                tasks->data[i].month,
                tasks->data[i].day,
                tasks->data[i].name,
                tasks->data[i].description);
        }
    }
}

void DisplayByRange(const TASK* tasks) {
    //Set four ints to search
    int monthone = 0;
    int dayone = 0;
    int monthtwo = 0;
    int daytwo = 0;
    printf("Pleast input the start date you want to search(Use format like 12.12):\n");
    scanf("%d.%d", &monthone,&dayone);
    printf("Pleast input the end date you want to search(Use format like 12.12):\n");
    scanf("%d.%d", &monthtwo, &daytwo);
    int i = 0;
    int found = 0;
    for (i = 0; i < tasks->id; i++) {
        //Check if a task exists in the range of two dates.
        if ((tasks->data[i].month > monthone ||
            (tasks->data[i].month == monthone && tasks->data[i].day >= dayone)) &&
            (tasks->data[i].month < monthtwo ||
            (tasks->data[i].month == monthtwo && tasks->data[i].day <= daytwo))){
            found = 1;
            //If found one,break and go to the next step.
            break;
        }
        //If not found,the value of found is the initial 0,so use the !found to print and return.
        if (!found) {
            printf("The task doesn't exist.\n");
            return;
        }
        //If tasks exist,print the title "Month", "Day", "Name", "Description" first.
        printf("%-2s\t%-2s\t%-20s\t%-100s\n", "Month", "Day", "Name", "Description");
        //Then use loop to print every task between the two dates,just like the single one.
        for (i = 0; i < tasks->id; i++) {
            if ((tasks->data[i].month > monthone ||
                (tasks->data[i].month == monthone && tasks->data[i].day >= dayone)) &&
                (tasks->data[i].month < monthtwo ||
                (tasks->data[i].month == monthtwo && tasks->data[i].day <= daytwo))) {
                printf("%-2d\t%-2d\t%-20s\t%-100s\n",
                    tasks->data[i].month,
                    tasks->data[i].day,
                    tasks->data[i].name,
                    tasks->data[i].description);
            }
        }
    }
}

void DisplayAll(const TASK* tasks) {
    printf("%-2s\t%-2s\t%-20s\t%-100s\n", "Month","Day","Name", "Description");
    int i = 0;
    for (i = 0; i < tasks->id; i++) {
        printf("%-2d\t%-2d\t%-20s\t%-100s\n",
            tasks->data[i].month,
            tasks->data[i].day,
            tasks->data[i].name,
            tasks->data[i].description);
    }
}

void SearchTask(const TASK* tasks) {
    char name[NAME_LENGTH] = { 0 };
    printf("Pleast input the task name you want to search:\n");
    scanf("%s", name);
    //Use the function FindByName to compare names in the data,put the int of return in the parameter temp.
    int temp = FindByName(&tasks, name);
    if (temp == EOF) {
        printf("This task doesn't exist.\n");
        return;
    }
    //Print the title and the data found by FindByName.
    printf("%-2s\t%-2s\t%-20s\t%-100s\n", "Month", "Day", "Name", "Description");
    printf("%-2d\t%-2d\t%-20s\t%-100s\n",
        tasks->data[temp].month,
        tasks->data[temp].day,
        tasks->data[temp].name,
        tasks->data[temp].description);
}

bool WriteTaskListToFile(TASK t, char* filename) {
    FILE* fp = fopen(filename, "w"); //writing to file
    if (fp == NULL) {
        fprintf(stderr, "error, not able to open file for writing\n");
        return false;
    }
    // what do we want to write as identifiers/how are they stored

    fclose(fp);
    return true;
}


bool ReadTaskListFromFile(TASK* t, char* filename) {
    FILE* fp = fopen(filename, "r");    // read from file
    if (fp == NULL) {
        fprintf(stderr, "error, not able to open file for writing\n");
        return false;
    }

    //need to finish write file before continuing

    fclose(fp);
    return true;
}
