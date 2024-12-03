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
    int currentId = 0;
    // Find highest existing ID
    for (int i = 0; i < MAX_TASKS; i++) {
        if (tasks->data[i].id > currentId) {
            currentId = tasks->data[i].id;
        }
    }

    INFO newTask = { 0 };
    newTask.id = currentId + 1;

    printf("Enter Task name:\n");
    scanf(" %[^\n]", newTask.name);

    printf("Enter task description: ");
    scanf(" %[^\n]", newTask.description);

    printf("Enter task tag (1-12 for months): ");
    
    int tagNum;
    scanf("%d", &tagNum);
    if (tagNum < 1 || tagNum > 12) {
        printf("Invalid month number\n");
        return;
    }
    newTask.tag = (TAG)tagNum;
    for (int i = 0; i < MAX_TASKS; i++) {
        if (tasks->data[i].id == 0) {
            tasks->data[i] = newTask;
            break;
        }
    }

    FILE* fp = fopen("tasks.txt", "a");
    if (!fp) {
        printf("Error opening file\n");
        return;
    }
    WriteTaskToFile(newTask, fp);
    fclose(fp);
}
void DeleteTask(TASK* tasks) {    
    if (!tasks->data) {
        printf("No tasks to delete\n");
        return;
    }
    int id;
    printf("Enter task ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < MAX_TASKS; i++) {
        if (tasks->data[i].id == id) {
            tasks->data[i].id = 0;
            memset(tasks->data[i].name, 0, NAME_LENGTH);
            memset(tasks->data[i].description, 0, MAX_LENGTH);

            WriteTaskListToFile(*tasks, "tasks.txt");
            printf("Task deleted\n");
            return;
        }
    }
    printf("Task not found\n");
}


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

            WriteTaskListToFile(*tasks, "tasks.txt");
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
    //search the data to find the task in the same date.
    int i = 0;
    int found = 0;
    for (i = 0; i < tasks->data->id; i++) {
        //Check if a task exists for a specified date
        if (tasks->data[i].id == id) {
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
    //If tasks exist,print the title "ID", "Tag", "Name", "Description" first.
    //\t means one press of Tab.
    printf("%-4d\t%-4s\t%-20s\t%-100s\n", "ID", "Tag", "Name", "Description");
    //Then use loop to print every task in the specific date, because there maybe not only one task in single date.
    for (i = 0; i < tasks->data->id; i++) {
        if (tasks->data[i].id == id) {
            printf("%-4d\t%-4s\t%-20s\t%-100s\n",
                tasks->data[i].id,
                //put the int of the task.data.tag into const char monthNames,like 1 is Jan,then print this monthNames[].
                monthNames[tasks->data[i].tag],
                tasks->data[i].name,
                tasks->data[i].description);
        }
    }
}

void DisplayByRange(const TASK* tasks) {
    //Set four ints to search
    int monthone = 0;
    int monthtwo = 0;
    printf("Pleast input the start month you want to search(Use format like 12 or Dec):\n");
    scanf("%d", &monthone);
    printf("Pleast input the end month you want to search(Use format like 12 or Dec):\n");
    scanf("%d", &monthtwo);
    int i = 0;
    int found = 0;
    for (i = 0; i < tasks->data->id; i++) {
        //Check if a task exists in the range of two dates.
        if (tasks->data[i].tag >= monthone &&
            tasks->data[i].tag <= monthtwo){
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
        printf("%-4d\t%-4s\t%-20s\t%-100s\n", "ID", "Tag", "Name", "Description");
        //Then use loop to print every task between the two dates,just like the single one.
        for (i = 0; i < tasks->data->id; i++) {
            if (tasks->data[i].tag >= monthone &&
                tasks->data[i].tag <= monthtwo) {
                printf("%-4d\t%-4s\t%-20s\t%-100s\n",
                    tasks->data[i].id,
                    //put the int of the task.data.tag into const char monthNames,like 1 is Jan,then print this monthNames[].
                    monthNames[tasks->data[i].tag],
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
        printf("%-4d\t%-4s\t%-20s\t%-100s\n",
            tasks->data[i].id,
            //put the int of the task.data.tag into const char monthNames,like 1 is Jan,then print this monthNames[].
            monthNames[tasks->data[i].tag],
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
    printf("%-4d\t%-4s\t%-20s\t%-100s\n", "ID", "Tag", "Name", "Description");
    printf("%-4d\t%-4s\t%-20s\t%-100s\n",
        tasks->data[temp].id,
        tasks->data[temp].tag,
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
    char type[MAX_TAG_LENGTH] = { 0 };
    char* result = fgets(type, MAX_TAG_LENGTH, fp);
    if (result == NULL) {  // bad things happened
        fprintf(stderr, "error, not able to read type from file\n");
        exit(EXIT_FAILURE);
    }
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
        return Aug;
    }
    else if (strncmp(type, "Sep", strlen("Sep")) == 0) {
        return Sep;
    }
    else if (strncmp(type, "Oct", strlen("Oct")) == 0) {
        return Oct;
    }
    else if (strncmp(type, "Nov", strlen("Nov")) == 0) {
        return Nov;
    }
    else if (strncmp(type, "Dec", strlen("Dec")) == 0) {
        return Dec;
    }
    else {
        fprintf(stderr, "disaster!  exiting...\n");
        exit(EXIT_FAILURE);
    }
}



bool WriteTaskListToFile(PTTASK t, char* filename) {
    FILE* fp = fopen(filename, "w"); //writing to file
    if (fp == NULL) {
        fprintf(stderr, "error, not able to open file for writing\n");
        return false;
    }
    for (int i = 0; i < MAX_TASKS; i++) {
        if (t->data[i].name == NULL) {
            return true;
        }
        WriteTaskToFile(t->data[i], fp);
    }
    fclose(fp);
    return true;
}

bool WriteTaskToFile(INFO t, FILE* fp) {
    fprintf(fp, "%d\n", t.id);              //id#
    WriteTagToFile(t, fp);                  // tag
    fprintf(fp, "%s\n", t.name);            // name
    fprintf(fp, "%s\n", t.description);     // description
    return true;
}

bool ReadTaskListFromFile(TASK* t, char* filename) {
    FILE* fp = fopen(filename, "r");    // read from file
    if (fp == NULL) {
        fprintf(stderr, "error, not able to open file for writing\n");
        return false;
    }
    for (int i = 0; i < MAX_TASKS; i++) {   // TODO: check for end of file
        t->data[i] = ReadTaskFromFile(fp);
    }
    fclose(fp);
    return true;
}

// TODO: finish this
INFO ReadTaskFromFile(FILE * fp) {
    
    
    INFO newTask = { 0 }; 
    // id#
    int id = 0; // initialize to 0 to be safe
    int numResult = fscanf(fp, "%d", &id);
    if (numResult != 1) {
        fprintf(stderr, "error, not able to read task id# from file\n");
        exit(EXIT_FAILURE);
    }
    newTask.id = id;
   
    // TAG
    int tagNum = ReadTagFromFile(fp);
    (newTask.tag) = (TAG)tagNum;

    // name
    char tmpName[NAME_LENGTH] = { 0 };
    char* nameResult = fgets(tmpName, NAME_LENGTH, fp);
    if (nameResult == NULL) {
        fprintf(stderr, "error, not able to read name from file\n");
        exit(EXIT_FAILURE);
    }
    CleanNewLineFromString(tmpName);
    strncpy(newTask.name, tmpName, NAME_LENGTH);
    

    // description
    char tmpDesc[NAME_LENGTH] = { 0 };
    char* descResult = fgets(tmpDesc, NAME_LENGTH, fp);
    if (descResult == NULL) {
        fprintf(stderr, "error, not able to read name from file\n");
        exit(EXIT_FAILURE);
    }
    CleanNewLineFromString(tmpDesc);
    strncpy(newTask.description, tmpDesc, NAME_LENGTH);

    return newTask;
}
