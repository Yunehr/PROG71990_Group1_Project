#pragma once
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

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

//I create one struct for task informations.
typedef struct Info {
	int month;
	int day;
	char name[NAME_LENGTH];
	char description[MAX_LENGTH];
}INFO, * PINFO;

//And one struct for task id of the information.
typedef struct TASK {
	int id;
	INFO* data;
}TASK, * PTASK;

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

