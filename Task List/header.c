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

//Set a const char for print the name of Month of the tag.
const char* monthNames[] = {
    //Set Invalid for monthNames[0], and others as 1 2 3 4.....
    "Invalid",
    "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"
};

bool AddTask(TASK* tasks) {
    if (tasks->count >= MAX_TASKS) {
        printf("Task list is full!\n");
        return false;
    }

    INFO newTask = { 0 };
    newTask.id = tasks->count + 1;  // Assign a new ID based on task count

    printf("Enter Task name:\n");
    scanf(" %[^\n]", newTask.name);

    printf("Enter task description:\n");
    scanf(" %[^\n]", newTask.description);

    printf("Enter task tag (1-12 for months):\n");
    int tagNum;
    scanf("%d", &tagNum);
    if (tagNum < 1 || tagNum > 12) {
        printf("Invalid month number\n");
        return false;
    }
    newTask.tag = (TAG)tagNum;

    tasks->data[tasks->count] = newTask;
    tasks->count++;

    FILE* fp = fopen("tasks.txt", "a");
    if (!fp) {
        printf("Error opening file\n");
        return false;
    }
    WriteTaskToFile(newTask, fp);
    fclose(fp);

    return true;
}
bool DeleteTask(TASK* tasks) {
    if (tasks->count == 0) {
        printf("No tasks to delete\n");
        return false;
    }

    int id;
    printf("Enter task ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < tasks->count; i++) {
        if (tasks->data[i].id == id) {
           
            for (int j = i; j < tasks->count - 1; j++) {
                tasks->data[j] = tasks->data[j + 1];
            }
            tasks->count--;

            
            WriteTaskListToFile(tasks, "tasks.txt");
            printf("Task deleted\n");
            return true;
        }
    }

    printf("Task not found\n");
    return false;
}

void UpdateTask(TASK* tasks) {
    if (tasks->count == 0) {
        printf("No tasks exist\n");
        return;
    }

    int id;
    printf("Enter task ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < tasks->count; i++) {
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

            WriteTaskListToFile(tasks, "tasks.txt");
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
        //If tasks exist,print the title first.
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
    if (t->data == NULL) {    //if there are no tasks, creates file with empty tasks
        //t->data[0].id = 0;      // initializing to zero, not magic number
        return true;
    }
    for (int i = 0; i < MAX_TASKS; i++) {
        if (t == NULL) {
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
        //fclose(fp);
        FILE* nfp = fopen(filename, "w"); //writing to file
        if (nfp == NULL) {
            fprintf(stderr, "error, not able to open file for writing\n");
            return false;
        }
        INFO InitialTask = { 0 };
        InitialTask = CreateVoidTask(InitialTask);
        WriteTaskToFile(InitialTask, nfp);
        fclose(nfp);
        return false;
    }
    for (int i = 0; i < MAX_TASKS; i++) {   
        t->data[i] = ReadTaskFromFile(fp);
    }
    fclose(fp);
    return true;
}

// TODO: finish this
INFO ReadTaskFromFile(FILE * fp) {
    
    
    INFO tempTask = { 0 }; 

    // id#
    int id = 0; // initialize to 0 to be safe
    int numResult = fscanf(fp, "%d\n", &id);
    if (numResult != 1) {
        fprintf(stderr, "error, not able to read task id# from file\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    tempTask.id = id;
   
    // TAG
    int tagNum = ReadTagFromFile(fp);
    (tempTask.tag) = (TAG)tagNum;

    // name
    char tmpName[NAME_LENGTH] = { 0 };
    char* nameResult = fgets(tmpName, NAME_LENGTH, fp);
    if (nameResult == NULL) {
        fprintf(stderr, "error, not able to read name from file\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    CleanNewLineFromString(tmpName);
    strncpy(tempTask.name, tmpName, NAME_LENGTH);
    

    // description
    char tmpDesc[NAME_LENGTH] = { 0 };
    char* descResult = fgets(tmpDesc, NAME_LENGTH, fp);
    if (descResult == NULL) {
        fprintf(stderr, "error, not able to read Description from file\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    CleanNewLineFromString(tmpDesc);
    strncpy(tempTask.description, tmpDesc, NAME_LENGTH);

    return tempTask;
}
