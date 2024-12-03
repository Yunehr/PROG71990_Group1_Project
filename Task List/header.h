#pragma once
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define NAME_LENGTH		100
#define MAX_LENGTH		200
#define MAX_TASKS		100
#define MAX_TAG_LENGTH	10

enum Options {
	EXIT,
	ADD,
	DELETE,
	UPDATE,
	DISPLAYSINGLE,
	DISPLAYRANGE,
	DISPLAYALL,
	SEARCH
};
//an enum for transit abbr. of months to int.
typedef enum Months {	// tag
	Jan = 1,
	Feb,
	Mar,
	Apr,
	May,
	Jun,
	Jul,
	Aug,
	Sep,
	Oct,
	Nov,
	Dec
}MONTHS, TAG;

//I create one struct for task informations.				// we do not need multiple task lists **yet** so no need for 2 structs, we can combine their ideas in an overall update
typedef struct Info {										// instead of searching by month or day we can search by id# and maybe display by tag type (important, not important, food, housework, school, etc...)
	TAG tag;												//				- the tag could be an enum, and used to display a range of tasks instead of months
	int id;												//				- the id# an be used for displaying a single task
	char name[NAME_LENGTH];
	char description[MAX_LENGTH];							// doing what is said above will make storing and reading the tasks easier since we can just save upon exiting the program, and load upon launching program
}INFO, * PINFO;

//And one struct for task id of the information.
typedef struct TASK {
	//int id;
	INFO* data;
}TASK, * PTTASK;

void DisplayMenu(void);
void AddTask(TASK* tasks);
void DeleteTask(TASK* tasks);
void UpdateTask(TASK* tasks);
//I create a function to search by date.
int FindByName(TASK* tasks, char name[]);
//Because this functions are display and search only, so I use const to avoid the content to be modified.
void DisplaySingle(const TASK* tasks);
void DisplayByRange(const TASK* tasks);
void DisplayAll(const TASK* tasks);
void SearchTask(const TASK* tasks);

//Save/Read from disk
bool WriteTagToFile(INFO t, FILE* fp);
int ReadTagFromFile(FILE* fp);

bool WriteTaskListToFile(PTTASK t, char* filename);
bool WriteTaskToFile(INFO t, FILE* fp);

bool ReadTaskListFromFile(TASK* t, char* filename);
INFO ReadTaskFromFile(FILE* fp);

