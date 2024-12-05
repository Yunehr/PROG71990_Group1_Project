#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define NAME_LENGTH		100
#define MAX_LENGTH		200
#define MAX_TASKS		100
#define DEFAULT_TASKS	3
#define INC_TASKS	1

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
}TAG;

//I create one struct for task informations.				
typedef struct Info {
	int month;
	int day;												
	char name[NAME_LENGTH];
	char description[MAX_LENGTH];
}INFO, * PINFO;

//And one struct for task id of the information.
typedef struct TASK {
	//Set id to locate data
	int id;
	//Set capacity for compare with id to check if the task is full.
	int capacity;
	INFO* data;
}TASK, * PTTASK;

void DisplayMenu(void);
//TaskManager need to be initiated.
void InitiateTask(TASK* tasks);
//And load informations from file.
void LoadTask(TASK* tasks);
//Check capacity to realloc memories for data.
void CheckCapacity(TASK* tasks);
void AddTask(TASK* tasks);
void DeleteTask(TASK* tasks);
void UpdateTask(TASK* tasks);

INFO CreateVoidTask(INFO t);
//I create a function to search by date.
int FindByName(TASK* tasks, char name[]);
//Because this functions are display and search only, so I use const to avoid the content to be modified.
void DisplaySingle(const TASK* tasks);
void DisplayByRange(const TASK* tasks);
void DisplayAll(const TASK* tasks);
void SearchTask(const TASK* tasks);
//Save informations to file.
void SaveTask(TASK* tasks);
//free memories.
void DestroyTask(TASK* tasks);

////Save/Read from disk
//bool WriteTaskListToFile(TASK t, char* filename);
//bool ReadTaskListFromFile(TASK* t, char* filename);

