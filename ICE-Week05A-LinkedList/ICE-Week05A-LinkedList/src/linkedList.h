#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define NULL  0


typedef struct LinkedNode LinkedNode;

// ** ADD CODE ** 
// Create a struct called LinkedNode
// that has the following fields
//
//  FIELD NAME    DATA TYPE
//  id            signed 32-bit integer
//  size          signed 32-bit integer
//  payload       pointer to char
//  next          pointer to LinkedNode

struct LinkedNode {
	int32_t id;
	int32_t size;
	char* payload;
	LinkedNode* next;
};

// ** ADD CODE ** 
// Create a struct called LinkedList
// that has the following fields
//
//  FIELD NAME    DATA TYPE
//  numNodes      signed 32-bit integer
//  start         pointer to LinkedNode
typedef struct {
	int32_t numNodes;
	LinkedNode* start;
} LinkedList;



//*********************************************************
// Initializes the linked list to be empty
// 
// Returns 0 on success
// Returns a negative number on failure
//*********************************************************
int32_t linkedListInit(LinkedList *list);

//*********************************************************
// Adds a a new node to the start of the linked list
// 
// Returns 0 on success
// Returns a negative number on failure
//*********************************************************
int32_t linkedListAddAtStart(LinkedList *list, LinkedNode *newNode);

//*********************************************************
// Adds a new node to the end of the linked list
// 
// Returns 0 on success
// Returns a negative number on failure
//*********************************************************
int32_t linkedListAddAtEnd(LinkedList *list, LinkedNode *newNode);

//*********************************************************
// Removes the first node from the linked list and returns
// the address of that node. 
//
// If the linked list is empty or an invalid paramter is 
// passed, NULL is returned.
//*********************************************************
LinkedNode* linkedListRemoveFromStart(LinkedList *list);


//*********************************************************
// Adds a value to the end of the linked list
//
// Returns 0 on success
// Returns a negative number on failure
//*********************************************************
int32_t linkedListPrintIds(LinkedList *list);



#endif
