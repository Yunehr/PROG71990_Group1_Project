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
void AddTask(TASK* tasks, int* taskCount) {
    if (*taskCount >= MAX_TASKS) { //checks we did not create too many tasks
        printf("Task list is full, cannot add more tasks \n");
        return;
    }
    TASK* newTask = (TASK*)malloc(sizeof(TASK));
    if (!newTask) {
        printf("memory Allocation failed");
        return;
    }
    //taskCount begins from 0. so Task id begins from 1.
    newTask->id = *taskCount + 1;
    //newTask.data[i].name is the same as the original newTask[i].name  
    printf("Please enter task name: \n");
    fgets(newTask->data[*taskCount].name, sizeof(newTask->data[*taskCount].name), stdin);
    newTask->data[*taskCount].name[strcspn(newTask->data[*taskCount].name, "\n")] = '\0';

    printf("Please enter the task description: \n");
    fgets(newTask->data[*taskCount].description, sizeof(newTask->data[*taskCount].description), stdin);
    newTask->data[*taskCount].description[strcspn(newTask->data[*taskCount].description, "\n")] = '\0';

    tasks = newTask;
    (*taskCount)++;

    //Need Save Function

    printf("Task Added Successfully!\n");

}
void DeleteTask(TASK* tasks, int* taskCount) {
    if (*taskCount == 0) {
        printf("There are no tasks to delete.\n");
        return;
    }
    int id;
    printf("Please enter the task ID to delete:\n");
    scanf_s("%d", &id);
    int found = 0;
    //No need of this first loop,just find tasks->id == id is OK.If found,found = 1.
    //for (int i = 0; i < *taskCount; ++i) {
        if (tasks->id == id) {
            //id of tasks[0] = 1, so tasks + id -1 point to the address of id.
            free(tasks + id - 1);
            //Like delete id = 5,we need to delete task[4],then we put task[4] = empty. copy task[5] as task[4]
            //so we begin from id - 1,finished in front of *taskCount - 1 is good,because there's not copy for the last one.
            for (int j = id - 1; j < *taskCount - 1; ++j) {
                tasks->data[j] = tasks->data[j + 1];
            }
            &tasks->data[*taskCount - 1] == NULL;
            (*taskCount)--;
            found = 1;
            printf("Task Deleted Successfully!\n");
        /*    break;*/
        }
    
    if (!found) {
        printf("Task not found.\n");
    }
} // Needs a save function add
void UpdateTask(TASK* tasks, int taskCount) {
    if (taskCount == 0) {
        printf("There are no tasks to update.\n");
        return;
    }
    int id;
    printf("Please enter the task ID to update:\n");
    scanf_s("%d", &id);
    int found = 0;
    for (int i = 0; i < taskCount; i++) {
        if (tasks->id == id) {
            //newTask.data[i].name is the same as the original newTask[i].name .Same as the description.
            printf("Enter new task name:\n");
            fgets(tasks->data[i].name, sizeof(tasks->data[i].name), stdin);
            tasks->data[i].name[strcspn(tasks->data[i].name, "\n")] = '\0';

            printf("Enter new task description:\n");
            fgets(tasks->data[i].description, sizeof(tasks->data[i].description), stdin);
            tasks->data[i].description[strcspn(tasks->data[i].description, "\n")] = '\0';

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
