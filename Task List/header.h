#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define NAME_LENGTH		100
#define MAX_LENGTH		200
#define MAX_TASKS		100

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
enum Months {
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
};

//I create one struct for task informations.				// we do not need multiple task lists **yet** so no need for 2 structs, we can combine their ideas in an overall update
typedef struct Info {										// instead of searching by month or day we can search by id# and maybe display by tag type (important, not important, food, housework, school, etc...)
	int month;												//				- the tag could be an enum, and used to display a range of tasks instead of months
	int day;												//				- the id# an be used for displaying a single task
	char name[NAME_LENGTH];
	char description[MAX_LENGTH];							// doing what is said above will make storing and reading the tasks easier since we can just save upon exiting the program, and load upon launching program
}INFO, * PINFO;

//And one struct for task id of the information.
typedef struct TASK {
	int id;
	INFO* data;
}TASK, * PTTASK;

void DisplayMenu(void);
void AddTask(TASK* tasks);
void DeleteTask(PTTASK tasks[], int* taskCount);
void UpdateTask(PTTASK tasks[], int taskCount);

//I create a function to search by date.
int FindByName(TASK* tasks, char name[]);
//Because this functions are display and search only, so I use const to avoid the content to be modified.
void DisplaySingle(const TASK* tasks);
void DisplayByRange(const TASK* tasks);
void DisplayAll(const TASK* tasks);
void SearchTask(const TASK* tasks);

//Save/Read from disk
bool WriteTaskListToFile(TASK t, char* filename);
bool ReadTaskListFromFile(TASK* t, char* filename);

