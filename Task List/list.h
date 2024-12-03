#pragma once
#include "header.h"
#include <stdbool.h>


// prog71990-f24 - steveh - week10
// linked list interface
typedef struct listnode {
	INFO data;
	struct listnode* next;
} LISTNODE, * PLISTNODE;


bool Add(PLISTNODE* list, INFO t);


bool Remove(PLISTNODE* list, INFO t);


void Display(PLISTNODE list);
bool WriteListToStream(PLISTNODE list, FILE* fp);

int GetCountOfParticipants(PLISTNODE list);
bool Empty(PLISTNODE* list);

/// <summary>/// /// </summary>/// <param name="list"></param>
void DestroyList(PLISTNODE* list);