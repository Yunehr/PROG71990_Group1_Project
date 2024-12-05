#pragma once
#define _CRT_SECURE_NO_WARNINGS
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
	Feb,Mar,Apr,May,Jun,Jul,Aug,Sep,Oct,Nov,Dec
}MONTHS, TAG;

//I create one struct for task informations.				
typedef struct Info {
	int id;
	TAG tag;
	char name[NAME_LENGTH];
	char description[MAX_LENGTH];
} INFO, *PINFO;

//And one struct for task id of the information.
typedef struct Task {
	INFO data[MAX_TASKS];
	int count;
} TASK, *PTTASK;

void DisplayMenu(void);
bool AddTask(TASK* tasks);
bool DeleteTask(TASK* tasks);
void UpdateTask(TASK* tasks);

INFO CreateVoidTask(INFO t);
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

