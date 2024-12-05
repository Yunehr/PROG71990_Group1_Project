#include "header.h"
#define _CRT_SECURE_NO_WARNINGS

void DisplayMenu(void) {
    printf("\n");
    printf("To choose a function, enter its number:                \n");
    printf("1) Add a new task                                      \n");
    printf("2) Delete an existing task                             \n");
    printf("3) Update an exsisting task                            \n");
    printf("4) Display a single task                               \n");
    printf("5) Display a range of tasks                            \n");
    printf("6) Display all tasks                                   \n");
    printf("7) Search for a task                                   \n");
    printf("0) Quit                                                \n\n");

}

void InitiateTask(TASK* tasks) {
    //void *malloc(size_t size);
    (INFO*)tasks->data = (INFO*)malloc(DEFAULT_TASKS * sizeof(INFO));
    if (tasks->data == NULL) {
        printf("memory Allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    tasks->id = 0;
    tasks->capacity = DEFAULT_TASKS;
    LoadTask(tasks);
}

void LoadTask(TASK* tasks) {
    FILE* fp = fopen("tasks.dat", "r");
    if (fp == NULL) {
        fprintf(stderr, "error, not able to open file for reading.\n");
        exit(EXIT_FAILURE);
    }
    //set a temporary tmp to get content from file.
    INFO tmp = { 0 };
    //fread(void *buffer,size_t size,size_t count,FILE* stream);
    //so destination is tmp,size is the size of struct,use loop to get 1 every time,from fp.
    while (fread(&tmp, sizeof(INFO), 1, fp)) {
        //Every time read one task from file,to check if capacity increasing is required.
        CheckCapacity(tasks);
        tasks->data[tasks->id] = tmp;
        tasks->id++;
    }
    //when closed file to put fp = NULL to avoid Dangling/Wild Pointer.
    fclose(fp);
    fp = NULL;
}

void CheckCapacity(TASK* tasks) {
    if (tasks->id == tasks->capacity) {
        //void *realloc(void* memblock,size_t size);
        //when num of id reach the capacity
        INFO* ptr = (INFO*)realloc(tasks->data,(tasks->capacity + INC_TASKS) * sizeof(INFO));
        if (ptr != NULL) {
            //point date to ptr,then at last just free data.
            tasks->data = ptr;
            //capacity increased.
            tasks->capacity += INC_TASKS;
            printf("Add memory success.\n");
        }
        else {
            fprintf(stderr, "Error, not able to allocate memory.\n");
            return;
        }
    }
}

void AddTask(TASK* tasks) {
    if (tasks->id == tasks->capacity) {
        //void *realloc(void* memblock,size_t size);
        //when num of id reach the capacity
        INFO* ptr = (INFO*)realloc(tasks->data, (tasks->capacity + INC_TASKS) * sizeof(INFO));
        if (ptr != NULL) {
            tasks->data = ptr;
            tasks->capacity += INC_TASKS;
            printf("Add memory success.\n");
        }
        }
    //get the user input to the data
    printf("Please enter task month: \n");
    scanf("%d", &(tasks->data[tasks->id].month));
    printf("Please enter task day: \n");
    scanf("%d", &(tasks->data[tasks->id].day));
    printf("Please enter task name: \n");
    scanf("%s", tasks->data[tasks->id].name);
    printf("Please enter the task description: \n");
    scanf("%s", tasks->data[tasks->id].description);
    //when get all informations, id++.
    tasks->id++;
    //Need Save Function(Save function could be used at the exit time.)
    printf("Task Added Successfully!\n\n");
}

void DeleteTask(TASK* tasks) {
    char name[NAME_LENGTH] = { 0 };
    if (tasks->id == 0) {
        printf("There are no tasks to delete.\n");
        return;
    }
    printf("Please enter the task name to delete:\n");
    scanf("%s", name);
    //If FindByName didn't find the task name,return EOF as -1.so when EOF,return.
    int temp = FindByName(tasks, name);
    if (temp == -1) {
        printf("The task doesn't exist.\n");
        return;
    }
    int i = 0;
    for (i = temp; i < tasks->id - 1; i++) {
        tasks->data[i] = tasks->data[i + 1];
    }
    tasks->id--;
    printf("Task Deleted Successfully!\n");
}

void UpdateTask(TASK* tasks) {
    char name[NAME_LENGTH] = { 0 };
    printf("Please enter the task name to update:\n");
    scanf("%s", name);
    int temp = FindByName(tasks, name);
    //If not found,print and return.
    if (temp == EOF) {
        printf("The person doesn't exist.\n");
        return;
    }
    //If found,ask user input to update all of the information like in the ADD function.
    //Because found pos,so change the data[id] to data[pos].
    printf("Please enter task month: \n");
    scanf("%d", &(tasks->data[temp].month));
    printf("Please enter task day: \n");
    scanf("%d", &(tasks->data[temp].day));
    printf("Please enter task name: \n");
    scanf("%s", tasks->data[temp].name);
    printf("Please enter the task description: \n");
    scanf("%s", tasks->data[temp].description);
}

//Use char name[] to compare with tasks->data[i].name through strcmp,if found, return int i.
//First I used this function in order to display single task.
//But I found if we add dates of the calender,using date is much more make sense.
//Finally this function would be used on search function by names.
int FindByName(TASK* tasks, char name[]) {
    int i = 0;
    for (i = 0; i < tasks->id; i++) {
        if (strcmp(tasks->data[i].name, name) == 0) {
            return i;
        }
    }
    //If didn't find, return EOF as -1.
    return -1;
}

void DisplaySingle(const TASK* tasks) {
    if (tasks->id == 0) {
        printf("There are no tasks to print.\n");
        return;
    }
    //Set two ints to search
    int month = 0;
    int day = 0;
    printf("Please enter task month: \n");
    scanf("%d", &month);
    printf("Please enter task day: \n");
    scanf("%d", &day);
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
        if (found = 0) {
            printf("The task doesn't exist.\n");
            return;
        }
    }
    //If tasks exist,print the title "Month", "Day", "Name", "Description" first.
    //\t means one press of Tab.
    printf("%-3s\t%-3s\t%-20s\t%-30s\n", "Month", "Day", "Name", "Description");
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
    printf("\n");
}

void DisplayByRange(const TASK* tasks) {
    if (tasks->id == 0) {
        printf("There are no tasks to print.\n");
        return;
    }
    //Set four ints to search
    int monthone = 0;
    int dayone = 0;
    int monthtwo = 0;
    int daytwo = 0;
    printf("Pleast input the started month of the date you want to search:\n");
    scanf("%d", &monthone);
    printf("Pleast input the day of the started month you want to search:\n");
    scanf("%d", &dayone);
    printf("Pleast input the ended month of the date you want to search:\n");
    scanf("%d", &monthtwo);
    printf("Pleast input the day of the ended month you want to search:\n");
    scanf("%d", &daytwo);
    int i = 0;
    int found = 0;
    for (i = 0; i < tasks->id; i++) {
        //Check if a task exists in the range of two dates.
        if ((tasks->data[i].month > monthone ||
            (tasks->data[i].month == monthone && tasks->data[i].day >= dayone)) &&
            (tasks->data[i].month < monthtwo ||
                (tasks->data[i].month == monthtwo && tasks->data[i].day <= daytwo))) {
            found = 1;
            //If found one,break and go to the next step.
            break;
        }
        //If not found,the value of found is the initial 0,so use the !found to print and return.
        if (found = 0) {
            printf("The task doesn't exist.\n");
            return;
        }
        //If tasks exist,print the title "Month", "Day", "Name", "Description" first.
        printf("%-3s\t%-3s\t%-20s\t%-30s\n", "Month", "Day", "Name", "Description");
        //Then use loop to print every task between the two dates,just like the single one.
        for (i = 0; i < tasks->id; i++) {
            if ((tasks->data[i].month > monthone ||
                (tasks->data[i].month == monthone && tasks->data[i].day >= dayone)) &&
                (tasks->data[i].month < monthtwo ||
                    (tasks->data[i].month == monthtwo && tasks->data[i].day <= daytwo))) {
                printf("%-3d\t%-3d\t%-20s\t%-30s\n",
                    tasks->data[i].month,
                    tasks->data[i].day,
                    tasks->data[i].name,
                    tasks->data[i].description);
            }
        }
    }
    printf("\n");
}

void DisplayAll(const TASK* tasks) {
    if (tasks->id == 0) {
        printf("There are no tasks to print.\n");
        return;
    }
    printf("%-3s\t%-3s\t%-20s\t%-30s\n", "Month", "Day", "Name", "Description");
    int i = 0;
    for (i = 0; i < tasks->id; i++) {
        printf("%-3d\t%-3d\t%-20s\t%-30s\n",
            tasks->data[i].month,
            tasks->data[i].day,
            tasks->data[i].name,
            tasks->data[i].description);
    }
    printf("\n");
}

void SearchTask(const TASK* tasks) {
    char name[NAME_LENGTH] = { 0 };
    printf("Pleast input the task name you want to search:\n");
    scanf("%s", name);
    //Use the function FindByName to compare names in the data,put the int of return in the parameter temp.
    int temp = FindByName(tasks, name);
    if (temp == -1) {
        printf("This task doesn't exist.\n");
        return;
    }
    //Print the title and the data found by FindByName.
    printf("%-3s\t%-3s\t%-20s\t%-30s\n", "Month", "Day", "Name", "Description");
    printf("%-3d\t%-3d\t%-20s\t%-30s\n",
        tasks->data[temp].month,
        tasks->data[temp].day,
        tasks->data[temp].name,
        tasks->data[temp].description);
}

void SaveTask(TASK* tasks) {
    //Just the same like LoadTask,so first copy the code.Change "r" to "w".
    FILE* fp = fopen("tasks.dat", "w");
    if (fp == NULL) {
        fprintf(stderr, "error, not able to open file for writting.\n");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    //fwrite(const void* buffer,size_t size,size_t count,FILE* stream);
    //so destination is tmp,size is the size of struct,use loop to get 1 every time,from fp.
    for (i = 0; i < tasks->id; i++) {
        //i from 0 to tasks->id - 1,put every size of informations to file.
        fwrite(tasks->data + i, sizeof(INFO), 1, fp);
    }
    //when closed file to put fp = NULL to avoid Dangling/Wild Pointer.
    fclose(fp);
    fp = NULL;
}

void DestroyTask(TASK* tasks) {
    free(tasks->data);
    //Same as open and close,put tasks->data = NULL to avoid Dangling/Wild Pointer.
    tasks->data = NULL;
    tasks->id = 0;
    tasks->capacity = 0;
}
//bool WriteTaskListToFile(TASK t, char* filename) {
//    FILE* fp = fopen(filename, "w"); //writing to file
//    if (fp == NULL) {
//        fprintf(stderr, "error, not able to open file for writing\n");
//        return false;
//    }
//    // what do we want to write as identifiers/how are they stored
//
//    fclose(fp);
//    return true;
//}
//
//
//bool ReadTaskListFromFile(TASK* t, char* filename) {
//    FILE* fp = fopen(filename, "r");    // read from file
//    if (fp == NULL) {
//        fprintf(stderr, "error, not able to open file for writing\n");
//        return false;
//    }
//
//    //need to finish write file before continuing
//
//    fclose(fp);
//    return true;
//}
//    if (fp == NULL) {
//        fprintf(stderr, "error, not able to open file for writing\n");
//        return false;
//    }
//
//    //need to finish write file before continuing
//
//    fclose(fp);
//    return true;
//}
//    if (fp == NULL) {
//        fprintf(stderr, "error, not able to open file for writing\n");
//        return false;
//    }
//
//    //need to finish write file before continuing
//
//    fclose(fp);
//    return true;
//}
