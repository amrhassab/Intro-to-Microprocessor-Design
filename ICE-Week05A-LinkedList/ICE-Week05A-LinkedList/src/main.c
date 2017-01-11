//*****************************************************************************
// main.c
// Author: jkrachey@wisc.edu
//*****************************************************************************
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "TM4C123.h"

// ** ADD CODE ** 
// Include the linkedList header file found in the src directory

#include "./linkedList.h"



 extern void serialDebugInit(void);

// ** ADD CODE ** 
// Create a MACRO called NUM_NODES and give it a value of 5

#define NUM_NODES 5


// ** ADD CODE ** 
// Create a global variable of type LinkedList with the name Packets

LinkedList Packets;


//*****************************************************************************
// Uses numNodes to add nodes to the linked list.
//*****************************************************************************
void addNodes( uint32_t numNodes)
{
  // ** ADD CODE ** 
  // Create a LinkedNode pointer named newNode

	LinkedNode* newNode;
  uint32_t i;
  
  printf("Adding nodes\n\r\n\r");
  
  for(i=0; i< numNodes; i++)
  {
    // ** ADD CODE ** 
    // Dynamically allocate enough space for a LinkedNode structure.  
    // Assign the data from the heap to newNode;
    

		newNode = malloc(sizeof(LinkedNode));

    newNode->id = i;
    newNode->next = NULL;
    newNode->size=10;
    

    // ** ADD CODE ** 
    // Allocate 10 bytes for the LinkedNode
    // payload
    
		newNode->payload = malloc(10);
    
    
    // ** ADD CODE ** 
    // Add the new packet to the linked list
    // (See LinkedList.h for list of available functions)
		
		linkedListAddAtStart(&Packets, newNode);


  }
  
  // Print out all of the IDs from 
  // most recently added to the oldest
  printf("Current IDs\n\r");
  linkedListPrintIds(&Packets);
}

//*****************************************************************************
//*****************************************************************************
void removeNodesFromStart(void)
{
  // ** ADD CODE ** 
  // Create a LinkedNode pointer named newNode
	
	LinkedNode* newNode;
  
  printf("\n\r");
  printf("Removing Nodes from the start\n\r");
  // Remove one node at a time
  while( Packets.numNodes > 0)
  {
    // ** ADD CODE ** 
    // Get the LinkedNode from the start of the linked list and assign it to newNode.
    //(See LinkedList.h for list of available functions)

    newNode = linkedListRemoveFromStart(&Packets);

    
    if( newNode == NULL)
    {
       printf("ERROR1, this should never happen\n\r");
       while(1){};
    }
    
    printf("\n\r");
    printf("**************************\n\r");
    printf(" Removed node %d\n\r", newNode->id);
    printf("**************************\n\r");
    

    // ** ADD CODE ** 
    // Deallocate the payload
 free(newNode->payload);
    

    // ** ADD CODE ** 
    // Deallocate the node
	free(newNode);

    

    printf("Remaining IDs\n\r");
    linkedListPrintIds(&Packets);
    printf("**************************\n\r");
  }
}


//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
  serialDebugInit();
  printf("\n\r");
  printf("**************************\n\r");
  printf(" ECE353 - Linked List     \n\r");
  printf(" In class exercise        \n\r");
  printf("**************************\n\r");
  
  if( linkedListInit(&Packets) != 0)
  {
    printf("Error initializing linked list\n\r");
  }
  
  addNodes(NUM_NODES);
  
  removeNodesFromStart();
  
  
  printf("\n\r\n\rDone... entering infinite loop\n\r");

  // Reach infinite loop
  while(1){};
}
