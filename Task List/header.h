#pragma once
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

#define NAME_LENGTH		100
#define MAX_LENGTH		200
#define MAX_TASKS		100

typedef struct TASK {
	int id;
	char name[NAME_LENGTH];
	char description[MAX_LENGTH];
}TASK, * PTTASK;

void DisplayMenu(void);
void AddTask(PTTASK tasks[], int* taskCount);
void DeleteTask(PTTASK tasks[], int* taskCount);
void UpdateTask(PTTASK tasks[], int taskCount);