#include "header.h"
#define _CRT_SECURE_NO_WARNINGS

void DisplayMenu(void) {
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
        printf("memory Allocation failed");
        exit(EXIT_FAILURE);
    }
    tasks->id = 0;
    tasks->capacity = DEFAULT_TASKS;
    LoadTask(tasks);
}
    fgets(newTask->data[*taskCount].name, sizeof(newTask->data[*taskCount].name), stdin);
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
    fgets(newTask->data[*taskCount].description, sizeof(newTask->data[*taskCount].description), stdin);
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
            fprintf(stderr, "Error, not able to allocate memory.");
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
    int id;
    //Need Save Function(Save function could be used at the exit time.)
    printf("Task Added Successfully!\n");
}
    for (int i = 0; i < taskCount; i++) {
void DeleteTask(TASK* tasks) {
    if (tasks->id == 0) {
        printf("There are no tasks to delete.\n");
        return;
    }
    char name[NAME_LENGTH] = { 0 };
    printf("Please enter the task name to delete:\n");
    scanf("%s", name);
    //If FindByName didn't find the task name,return EOF as -1.so when EOF,return.
    int pos = FindByName(tasks, name);
    if (pos = EOF) {
        printf("The person doesn't exist.\n");
        return;
    }
    int i = 0;
    for (i = pos; i < tasks->id - 1; i++) {
        tasks->data[i] = tasks->data[i + 1];
            tasks->data[i].name[strcspn(tasks->data[i].name, "\n")] = '\0';
    tasks->id--;
    printf("Task Deleted Successfully!\n");
} 
            tasks->data[i].description[strcspn(tasks->data[i].description, "\n")] = '\0';
    for (int i = 0; i < taskCount; i++) {
            printf("Tasks updated successfully!\n");
            found = 1;
            break;
        }
            tasks->data[i].name[strcspn(tasks->data[i].name, "\n")] = '\0';
    if (!found) {
        printf("Task ID not found.\n");
    }
            tasks->data[i].description[strcspn(tasks->data[i].description, "\n")] = '\0';

            printf("Tasks updated successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Task ID not found.\n");
    }

void UpdateTask(TASK* tasks) {
    char name[NAME_LENGTH] = { 0 };
    printf("Please enter the task name to update:\n");
    scanf("%s", name);
    int pos = FindByName(tasks, name);
    //If not found,print and return.
    if (pos = EOF) {
        printf("The person doesn't exist.\n");
        return;
    }
    //If found,ask user input to update all of the information like in the ADD function.
    //Because found pos,so change the data[id] to data[pos].
    printf("Please enter task month: \n");
    scanf("%d", &(tasks->data[pos].month));
    printf("Please enter task day: \n");
    scanf("%d", &(tasks->data[pos].day));
    printf("Please enter task name: \n");
    scanf("%s", tasks->data[pos].name);
    printf("Please enter the task description: \n");
    scanf("%s", tasks->data[pos].description);

void UpdateTask(TASK* tasks) {
    if (!tasks->data) {
        printf("No tasks exist\n");
        return;
    }

    int id;
    printf("Enter task ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < MAX_TASKS; i++) {
        if (tasks->data[i].id == id) {
            printf("Enter new name: ");
            scanf(" %[^\n]", tasks->data[i].name);

            printf("Enter new description: ");
            scanf(" %[^\n]", tasks->data[i].description);

            printf("Enter new tag (1-12 for months): ");
            int tagNum;
            scanf("%d", &tagNum);
            if (tagNum < 1 || tagNum > 12) {
                printf("Invalid month number\n");
                return;
            }
            tasks->data[i].tag = (TAG)tagNum;

            //WriteTaskListToFile(*tasks, "tasks.txt");
            printf("Task updated\n");
            return;
        }
    }
    printf("Task not found\n");
}

//Initializes a fake task
INFO CreateVoidTask(INFO t) {
    //INFO tempTask = { 0 }; 
    //tempTask.id = 0; 
    //tempTask.tag = Jan; 
    //strncpy(tempTask.name, "Task Name", NAME_LENGTH);;
    //strncpy(tempTask.description, "Task description", MAX_LENGTH);
    t.id = 0;
    t.tag = Jan;
    strncpy(t.name, "Task Name", NAME_LENGTH);;
    strncpy(t.description, "Task description", MAX_LENGTH);
    return t;
}

//Use char name[] to compare with tasks->data[i].name through strcmp,if found, return int i.
//First I used this function in order to display single task.
//But I found if we add dates of the calender,using date is much more make sense.
//Finally this function would be used on search function by names.
int FindByName(TASK* tasks, char name[]) {
    int i = 0;
    for (i = 0; i < tasks->data->id; i++) {
        if (strcmp(tasks->data[i].name,name) == 0) {
            return i;
        }
    }
    //If didn't find, return EOF as -1.
    return EOF;
}

void DisplaySingle(const TASK* tasks) {
    //Set two ints to search
    int id = 0;
    printf("Pleast input the id of the task you want to search:\n");
    scanf("%d", &id);
    for (i = 0; i < tasks->id; i++) {
        if (tasks->data[i].month == month &&
            tasks->data[i].day == day) {
            printf("%-2d\t%-2d\t%-20s\t%-100s\n",
                &(tasks->data[i].month),
                &(tasks->data[i].day),
            found = 1;
            //If found one,break and go to the next step.
            break;
        }
    for (i = 0; i < tasks->id; i++) {
        if (tasks->data[i].month == month &&
            tasks->data[i].day == day) {
            printf("%-2d\t%-2d\t%-20s\t%-100s\n",
                tasks->data[i].month,
                tasks->data[i].day,
    int daytwo = 0;
    printf("Pleast input the started month of the date you want to search:\n");
    scanf("%d", &monthone);
    printf("Pleast input the day of the started month you want to search:\n");
    scanf("%d", &dayone);
    printf("Pleast input the ended month of the date you want to search:\n");
    scanf("%d", &monthtwo);
    printf("Pleast input the day of the ended month you want to search:\n");
    scanf("%d", &daytwo);
        if (tasks->data[i].month == month &&
            tasks->data[i].day == day) {
            printf("%-2d\t%-2d\t%-20s\t%-100s\n",
                tasks->data[i].month,
                tasks->data[i].day,
    int daytwo = 0;
    printf("Pleast input the start date you want to search(Use format like 12.12):\n");
    scanf("%d.%d", &monthone,&dayone);
    printf("Pleast input the end date you want to search(Use format like 12.12):\n");
    scanf("%d.%d", &monthtwo, &daytwo);

void DisplayByRange(const TASK* tasks) {
    //Set four ints to search
    int monthone = 0;
    int monthtwo = 0;
    int daytwo = 0;
    printf("Pleast input the start date you want to search(Use format like 12.12):\n");
        for (i = 0; i < tasks->id; i++) {
            if ((tasks->data[i].month > monthone ||
                (tasks->data[i].month == monthone && tasks->data[i].day >= dayone)) &&
                (tasks->data[i].month < monthtwo ||
                (tasks->data[i].month == monthtwo && tasks->data[i].day <= daytwo))) {
                printf("%-2d\t%-2d\t%-20s\t%-100s\n",
                    &(tasks->data[i].month),
                    &(tasks->data[i].day),
            tasks->data[i].tag <= monthtwo){
            found = 1;
        for (i = 0; i < tasks->id; i++) {
            if ((tasks->data[i].month > monthone ||
                (tasks->data[i].month == monthone && tasks->data[i].day >= dayone)) &&
                (tasks->data[i].month < monthtwo ||
                (tasks->data[i].month == monthtwo && tasks->data[i].day <= daytwo))) {
                printf("%-2d\t%-2d\t%-20s\t%-100s\n",
                    tasks->data[i].month,
                    tasks->data[i].day,
        printf("%-4d\t%-4s\t%-20s\t%-100s\n", "ID", "Tag", "Name", "Description");
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
    printf("%-4d\t%-4s\t%-20s\t%-100s\n", "ID", "Tag", "Name", "Description");
    int i = 0;
    for (i = 0; i < tasks->data->id; i++) {
    printf("%-2s\t%-2s\t%-20s\t%-100s\n", "Month", "Day", "Name", "Description");
    printf("%-2d\t%-2d\t%-20s\t%-100s\n",
        &(tasks->data[temp].month),
        &(tasks->data[temp].day),
            tasks->data[i].name,
            tasks->data[i].description);
    }
}

void SearchTask(const TASK* tasks) {
    printf("%-2s\t%-2s\t%-20s\t%-100s\n", "Month", "Day", "Name", "Description");
    printf("%-2d\t%-2d\t%-20s\t%-100s\n",
        tasks->data[temp].month,
        tasks->data[temp].day,
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


bool WriteTagToFile(INFO t, FILE* fp) {
    switch (t.tag) {        // tag        
    case Jan:   fprintf(fp, "Jan\n");
        break;
    case Feb:   fprintf(fp, "Feb\n");
        break;
    case Mar:   fprintf(fp, "Mar\n");
        break;
    case Apr:   fprintf(fp, "Apr\n");
        break;
    case May:   fprintf(fp, "May\n");
        break;
    case Jun:   fprintf(fp, "Jun\n");
        break;
    case Jul:   fprintf(fp, "Jul\n");
        break;
    case Aug:   fprintf(fp, "Aug\n");
        break;
    case Sep:   fprintf(fp, "Sep\n"); 
        break;
    case Oct:   fprintf(fp, "Oct\n"); 
        break;
    case Nov:   fprintf(fp, "Nov\n"); 
        break;
    case Dec:   fprintf(fp, "Dec\n"); 
        break;
    default:    fprintf(stderr, "unknown Tag\n");
        break; return false;
    }
    return true;
}

int ReadTagFromFile(FILE* fp) {
    char type[MAX_TAG_LENGTH] = { "" };
    char* result = fgets(type, MAX_TAG_LENGTH, fp);
    if (result == NULL) {  // bad things happened
        fprintf(stderr, "error, not able to read type from file\n");
        exit(EXIT_FAILURE);
    }
    CleanNewLineFromString(type);
    if (strncmp(type, "Jan", strlen("Jan")) == 0) {
        return Jan;
    }
    else if (strncmp(type, "Feb", strlen("Feb")) == 0) {
        return Feb;
    }
    else if (strncmp(type, "Mar", strlen("Mar")) == 0) {
        return Mar;
    }
    else if (strncmp(type, "Apr", strlen("Apr")) == 0) {
        return Apr;
    }
    else if (strncmp(type, "May", strlen("May")) == 0) {
        return May;
    }
    else if (strncmp(type, "Jun", strlen("Jun")) == 0) {
        return Jun;
    }
    else if (strncmp(type, "Jul", strlen("Jul")) == 0) {
        return Jul;
    }
    else if (strncmp(type, "Aug", strlen("Aug")) == 0) {
void SaveTask(TASK* tasks) {
    //Just the same like LoadTask,so first copy the code.Change "r" to "w".
    FILE* fp = fopen("tasks.dat", "w");
    else if (strncmp(type, "Sep", strlen("Sep")) == 0) {
        return Sep;
    }
    else if (strncmp(type, "Oct", strlen("Oct")) == 0) {
        return Oct;
    }
    else if (strncmp(type, "Nov", strlen("Nov")) == 0) {
        return Nov;
bool WriteTaskListToFile(TASK t, char* filename) {
    FILE* fp = fopen(filename, "w"); //writing to file
        return Dec;
    //when closed file to put fp = NULL to avoid Dangling/Wild Pointer.
        fprintf(stderr, "disaster!  exiting...\n");
        exit(EXIT_FAILURE);
    }
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
    if (fp == NULL) {
        fprintf(stderr, "error, not able to open file for writing\n");
        return false;
    }

    //need to finish write file before continuing

    fclose(fp);
    return true;
}
    if (fp == NULL) {
        fprintf(stderr, "error, not able to open file for writing\n");
        return false;
    }

    //need to finish write file before continuing

    fclose(fp);
    return true;
}
