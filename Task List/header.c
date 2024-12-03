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
void AddTask(TASK* tasks) {
    if (tasks->id >=MAX_TASKS)     { //checks we did not create too many tasks
        printf("Task list is full, cannot add more tasks \n");
        return;
    }

    INFO newTask = { 0 };
    newTask.id = tasks->id + 1;
    printf("Enter Task name:\n");
    scanf(" %[^\n]", newTask.name);

    printf("Enter task description: ");
    scanf(" %[^\n]", newTask.description);

    printf("Enter task tag (1-12 for months): ");
    
    int tagNum;
    scanf("%d", &tagNum);
    newTask.tag = (TAG)tagNum;

    tasks->data[tasks->id] = newTask;
    tasks->id++;

    //save to file
    char filename[20];
    sprintf(filename, "task_%d.txt", newTask.id);
    if (!WriteTaskToFile(newTask, filename)) {
        printf("Error saving task\n");
    }

    printf("Task Added Successfully!\n");

}
void DeleteTask(TASK* tasks, int* taskCount) {    
    if (tasks->id == 0) {
        printf("No tasks to delete\n");
        return;
    }
    int id;
    printf("Enter task ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < tasks->id; i++) {
        if (tasks->data[i].id == id) {
            // Remove file
            char filename[20];
            sprintf(filename, "task_%d.txt", id);
            remove(filename);

            // Shift remaining tasks
            for (int j = i; j < tasks->id - 1; j++) {
                tasks->data[j] = tasks->data[j + 1];
            }
            tasks->id--;
            printf("Task deleted\n");
            return;
        }
    }
    printf("Task not found\n");
}

void UpdateTask(TASK* tasks, int taskCount) {
    if (tasks->id == 0) {
        printf("No tasks to update\n");
        return;
    }
    int id;
    printf("Enter task ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < tasks->id; i++) {
        if (tasks->data[i].id == id) {
            printf("Enter new name: ");
            scanf(" %[^\n]", tasks->data[i].name);

            printf("Enter new description: ");
            scanf(" %[^\n]", tasks->data[i].description);

            printf("Enter new tag (1-12 for months): ");
            int tagNum;
            scanf("%d", &tagNum);
            tasks->data[i].tag = (TAG)tagNum;

            // Update file
            char filename[20];
            sprintf(filename, "task_%d.txt", id);
            if (!WriteTaskToFile(tasks->data[i], filename)) {
                printf("Error saving updated task\n");
            }

            printf("Task updated\n");
            return;
        }
    }
    printf("Task not found\n");
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

bool WriteTaskToFile(INFO t, char* filename) {
    FILE* fp = fopen(filename, "w"); //writing to file
    if (fp == NULL) {
        fprintf(stderr, "error, not able to open file for writing\n");
        return false;
    }
    fprintf(fp, "%d\n", t.id);  //id#

    //TODO: make WriteTagToFile()/ReadTagFromFile()
    switch (t.tag) {        // tag        
    case Dec:   fprintf(fp, "Dec\n");    // placeholders untill Types of tags are defined
                break;
    case Jan:   fprintf(fp, "Jan\n");
                break;
    default:    fprintf(stderr, "unknown Tag\n");
                break; // return false
    }
    
   
    fprintf(fp, "%s\n", t.name);     // name
    fprintf(fp, "%s\n", t.description);     // description

    fclose(fp);
    return true;
}


bool ReadTaskFromFile(INFO* t, char* filename) {
    FILE* fp = fopen(filename, "r");    // read from file
    if (fp == NULL) {
        fprintf(stderr, "error, not able to open file for writing\n");
        return false;
    }
    
    // id#
    int id = 0; // initialize to 0 to be safe
    int numResult = fscanf(fp, "%d", &id);
    if (numResult != 1) {
        fprintf(stderr, "error, not able to read task id# from file\n");
        exit(EXIT_FAILURE);
    }

    // TAG
    // ReadTagFromFile()

    // name
    char tmpName[NAME_LENGTH] = { 0 };
    char* nameResult = fgets(tmpName, NAME_LENGTH, fp);
    if (nameResult == NULL) {
        fprintf(stderr, "error, not able to read name from file\n");
        exit(EXIT_FAILURE);
    }
    CleanNewLineFromString(tmpName);
    strncpy(t->name, tmpName, NAME_LENGTH);
    

    // description
    char tmpDesc[NAME_LENGTH] = { 0 };
    char* descResult = fgets(tmpDesc, NAME_LENGTH, fp);
    if (descResult == NULL) {
        fprintf(stderr, "error, not able to read name from file\n");
        exit(EXIT_FAILURE);
    }
    CleanNewLineFromString(tmpDesc);
    strncpy(t->name, tmpDesc, NAME_LENGTH);

    fclose(fp);
    return true;
}
