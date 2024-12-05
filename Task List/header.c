#include "header.h"


void DisplayMenu(void) {

    printf("_________________________________________________________\n");
    printf("|To choose a function, enter its number:                |\n");
    printf("|1) Add a new task                                      |\n");
    printf("|2) Delete an existing task                             |\n");
    printf("|3) Update an exsisting task                            |\n");
    printf("|4) Display a single task                               |\n");
    printf("|5) Display a range of tasks                            |\n");
    printf("|6) Display all tasks                                   |\n");
    printf("|7) Search for a task                                   |\n");
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
int FindByName(const TASK* tasks, char name[]) {                        // works after changes
    int i = 0;
    for (i = 0; i < tasks->count; i++) {
        if (strcmp(tasks->data[i].name,name) == 0) {
            return i;
        }
    }
    //If didn't find, return EOF as -1.
    return EOF;
}

void DisplaySingle(const TASK* tasks) { //this works after fixes
    //Set two ints to search
    int id = 0;
    printf("Pleast input the id of the task you want to search:\n");
    scanf("%d", &id);
    //search the data to find the task in the same date.
    int i = 0;
    int found = 0;
    for (i = 0; i < tasks->count; i++) {
        //Check if a task exists for a specified date
        if (tasks->data[i].id == id) {
            //found = 1;
            printf("%-4s\t%-4s\t%-20s\t%-100s\n", "ID", "Tag", "Name", "Description");
            printf("%-4d\t%-4s\t%-20s\t%-100s\n",
                tasks->data[i].id,
                //put the int of the task.data.tag into const char monthNames,like 1 is Jan,then print this monthNames[].
                monthNames[tasks->data[i].tag],
                tasks->data[i].name,
                tasks->data[i].description);
            //If found one,break and go to the next step.
            return;
        }   
    }
    printf("The task doesn't exist.\n");
    ////If not found,the value of found is the initial 0,so use the !found to print and return.
    //if (found == 0) {
    //    printf("The task doesn't exist.\n");
    //    return;
    //}

    //If tasks exist,print the title "ID", "Tag", "Name", "Description" first.
    //\t means one press of Tab.
    //printf("%-4s\t%-4s\t%-20s\t%-100s\n", "ID", "Tag", "Name", "Description");
    ////Then use loop to print every task in the specific date, because there maybe not only one task in single date.
    //for (i = 0; i < tasks->data->id; i++) {
    //    if (tasks->data[i].id == id) {
    //        printf("%-4d\t%-4s\t%-20s\t%-100s\n",
    //            tasks->data[i].id,
    //            //put the int of the task.data.tag into const char monthNames,like 1 is Jan,then print this monthNames[].
    //            monthNames[tasks->data[i].tag],
    //            tasks->data[i].name,
    //            tasks->data[i].description);
    //    }
    //}
}

void DisplayByRange(const TASK* tasks) {    // works    
    //Set four ints to search
    char* monthone[MAX_TAG_LENGTH] = { "" };
    //int monthtwo = 0;
    printf("Pleast input the month you want to search(Use format like 12 or Dec):\n");
    scanf("%s", &monthone);
    int month = atoi(monthone); 
    if (month == 0) {   // checks if user entered monthName (Jan, Feb, etc...)
        for (int i = 0; i < NUMBER_OF_TAGS; i++) {
            if (strncmp(monthone, monthNames[i], strlen(monthNames[i])) == 0) {
                month = i;
            }
        }
        if (month == 0) { 
            printf("Value 'Invalid' or does not exist\n");
            return;
        }
    }
   /* printf("Pleast input the end month you want to search(Use format like 12 or Dec):\n");
    scanf("%d", &monthtwo);*/
    int i = 0;
    int found = 0;
    for (i = 0; i < tasks->count; i++) {
        if (tasks->data[i].tag == month) {
            if (found == 0) {
                printf("%-4s\t%-4s\t%-20s\t%-100s\n", "ID", "Tag", "Name", "Description");
            }
            printf("%-4d\t%-4s\t%-20s\t%-100s\n",
                tasks->data[i].id,
                //put the int of the task.data.tag into const char monthNames,like 1 is Jan,then print this monthNames[].
                monthNames[tasks->data[i].tag],
                tasks->data[i].name,
                tasks->data[i].description);
            found++;
            //If found one,break and go to the next step.
            // break;
        }
    }
    if (found == 0) {
        printf("No tasks found under tag: '%s'\n", monthNames[month]);
    }
        //If not found,the value of found is the initial 0,so use the !found to print and return.
        /*if (!found) {
            printf("The task doesn't exist.\n");
            return;
        }*/
        ////If tasks exist,print the title first.
        //printf("%-4s\t%-4s\t%-20s\t%-100s\n", "ID", "Tag", "Name", "Description");
        ////Then use loop to print every task between the two dates,just like the single one.
        //for (i = 0; i < tasks->count; i++) {
        //    if (tasks->data[i].tag >= monthone &&
        //        tasks->data[i].tag <= monthtwo) {
        //        printf("%-4d\t%-4s\t%-20s\t%-100s\n",
        //            tasks->data[i].id,
        //            //put the int of the task.data.tag into const char monthNames,like 1 is Jan,then print this monthNames[].
        //            monthNames[tasks->data[i].tag],
        //            tasks->data[i].name,
        //            tasks->data[i].description);
        //    }
        //}
    //}
}

void DisplayAll(const TASK* tasks) {    // this works
    printf("\n%-4s\t%-4s\t%-20s\t%-100s\n", "ID", "Tag", "Name", "Description");
    int i = 0;
    for (i = 0; i < tasks->count; i++) {
        printf("%-4d\t%-4s\t%-20s\t%-100s\n",
            tasks->data[i].id,
            //put the int of the task.data.tag into const char monthNames,like 1 is Jan,then print this monthNames[].
            monthNames[tasks->data[i].tag],
            tasks->data[i].name,
            tasks->data[i].description);
    }
}

void SearchTask(const TASK* tasks) { // works after changes
    char name[NAME_LENGTH] = { 0 };
    printf("Pleast input the task name you want to search:\n");
    scanf("%s", name);
    //Use the function FindByName to compare names in the data,put the int of return in the parameter temp.
    int temp = FindByName(tasks, name);
    if (temp == EOF) {
        printf("This task doesn't exist.\n");
        return;
    }
    //Print the title and the data found by FindByName.
    printf("%-4s\t%-4s\t%-20s\t%-100s\n", "ID", "Tag", "Name", "Description");
    printf("%-4d\t%-4s\t%-20s\t%-100s\n",
        tasks->data[temp].id,
        monthNames[tasks->data[temp].tag],
        tasks->data[temp].name,
        tasks->data[temp].description);
}


// writes a tag to file
bool WriteTagToFile(INFO t, FILE* fp) {
    if (t.tag >= Jan && t.tag <= Dec) {
        fprintf(fp, "%s\n", monthNames[t.tag]);
        return true;
    }
    else {
        fprintf(stderr, "unknown Tag\n");
        return false;
    }
}

// writes a single task to file
bool WriteTaskToFile(INFO t, FILE* fp) {
    fprintf(fp, "%d\n", t.id);              // id#
    WriteTagToFile(t, fp);                  // tag
    fprintf(fp, "%s\n", t.name);            // name
    fprintf(fp, "%s\n", t.description);     // description
    return true;
}

// writes list of tasks to file
bool WriteTaskListToFile(TASK* t, char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: unable to open file for writing\n");
        return false;
    }
    for (int i = 0; i < t->count; i++) {
        WriteTaskToFile(t->data[i], fp);
    }
    fclose(fp);
    return true;
}

// translates a tag from a string to a Int
int ReadTagFromFile(FILE* fp) {
    char type[MAX_TAG_LENGTH] = { "" };
    char* result = fgets(type, MAX_TAG_LENGTH, fp);
    if (result == NULL) {
        fprintf(stderr, "Error, not able to read type from file\n");
        exit(EXIT_FAILURE);
    }
    CleanNewLineFromString(type);

    for (int i = 0; i < 13; i++) { // this is a magic number
        if (strncmp(type, monthNames[i], strlen(monthNames[i])) == 0) { 
            return i;
        }
    }
    fprintf(stderr, "Disaster! Exiting...\n");  // it it gets to here, something went wrong
    exit(EXIT_FAILURE);
}

// reads a single task from file
INFO ReadTaskFromFile(FILE* fp) {
    INFO tempTask = { 0 };

    // retrieving id#
    int id = 0;  // initialize to 0 to be safe
    if (fscanf(fp, "%d\n", &id) != 1) {
        fprintf(stderr, "Error, not able to read task ID from file\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    tempTask.id = id;

    //retrieving tag#
    int tagNum = ReadTagFromFile(fp);
    tempTask.tag = (TAG)tagNum;

    //retrieving task name
    char tmpName[NAME_LENGTH] = { 0 };
    if (fgets(tmpName, NAME_LENGTH, fp) == NULL) {
        fprintf(stderr, "Error, not able to read name from file\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    CleanNewLineFromString(tmpName);
    strncpy(tempTask.name, tmpName, NAME_LENGTH);

    // retrieving task description
    char tmpDesc[MAX_LENGTH] = { 0 };
    if (fgets(tmpDesc, MAX_LENGTH, fp) == NULL) {
        fprintf(stderr, "Error, not able to read description from file\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    CleanNewLineFromString(tmpDesc);
    strncpy(tempTask.description, tmpDesc, MAX_LENGTH);

    return tempTask;
}

// ReadTaskListFromFile function definition
bool ReadTaskListFromFile(TASK* t, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "File not found, creating a new one...\n");

        FILE* nfp = fopen(filename, "w");
        if (nfp == NULL) {
            fprintf(stderr, "Error: unable to create file for writing\n");
            return false;
        }

        for (int i = 0; i < MAX_TASKS; i++) {
            t->data[i] = CreateVoidTask((INFO) { 0 });  // initializes INFO to zero to save a line of code
            WriteTaskToFile(t->data[i], nfp);
        }
        fclose(nfp);
        return true;
    }

    // Reset task count
    t->count = 0;

    while (1) {
        if (feof(fp)) { //Checks for end of file
            break;
        }

        INFO tempTask = { 0 };
        
        // read task id
        int id = 0;
        if (fscanf(fp, "%d\n", &id) != 1) {
            if (feof(fp)) break; // checking for end of file to continue program without error
            fprintf(stderr, "Error, not able to read task ID from file\n");
            break;
        }
        tempTask.id = id;

        // read tag
        int tagNum = ReadTagFromFile(fp);
        tempTask.tag = (TAG)tagNum;

        //read task name
        char tmpName[NAME_LENGTH] = { 0 };
        if (fgets(tmpName, NAME_LENGTH, fp) == NULL) {
            if (feof(fp)) break;
            fprintf(stderr, "Error, not able to read name from file\n");
            break;
        }
        CleanNewLineFromString(tmpName);
        strncpy(tempTask.name, tmpName, NAME_LENGTH);

        // read task description
        char tmpDesc[MAX_LENGTH] = { 0 };
        if (fgets(tmpDesc, MAX_LENGTH, fp) == NULL) {
            if (feof(fp)) break;
            fprintf(stderr, "Error, not able to read description from file\n");
            break;
        }
        CleanNewLineFromString(tmpDesc);
        strncpy(tempTask.description, tmpDesc, MAX_LENGTH);

        // point to this task and add 1 to task count
        t->data[t->count] = tempTask;
        t->count++;
        if (t->count >= MAX_TASKS) { // maximum task ammount reached
            break;
        }
    }

    fclose(fp);
    return true;
}