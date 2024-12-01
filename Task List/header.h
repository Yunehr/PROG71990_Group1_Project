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

typedef struct Info {
	char name[NAME_LENGTH];
	char description[MAX_LENGTH];
}INFO, * PINFO;

typedef struct TASK {
	int id;
	INFO* data;
}TASK, * PTASK;

void DisplayMenu(void);
void AddTask(PTTASK tasks[], int* taskCount);
void DeleteTask(PTTASK tasks[], int* taskCount);
void UpdateTask(PTTASK tasks[], int taskCount);

//I create a function to search names.
int FindByName(TASK* tasks, char name[]);
//Because this functions are display only, so I use const to avoid the content to be modified.
void DisplaySingle(const TASK* tasks);
void DisplayRange(const TASK* tasks);
void DisplayAll(const TASK* tasks);
