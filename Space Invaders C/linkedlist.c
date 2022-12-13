/*Linked list library. Prepared by:  Nicholas Trambitas*/
#include<stdio.h>
#include<stdlib.h>
#include "linkedlist.h"
#include "altmem.h"

/*Declare node struct*/
 typedef struct Node{
	struct Node *next;
	void *data;
	}Node;



/*function to take static struct and reallocate to dynamic memory*/
static Node* allocNode(FILE *fPtr) {
	static int count; Node *dynm;
	dynm =  alternative_malloc(sizeof(Node));
		if (dynm != NULL){
			count++;
		if (fPtr)fprintf(fPtr,"DIAGNOSTIC: %d nodes allocated.\n", count);
					} else{
				if(fPtr)fprintf(fPtr,"ERROR: linkedlist.c: Failed to malloc a Node\n");
				}
	 return dynm; 
	}

/*function that will free dynamic pointer*/
static void freeNode(Node *ptr, FILE *fPtr) {
	static int count;
	alternative_free(ptr);
	count++;
		if (fPtr)fprintf(fPtr,"DIAGNOSTIC: %d nodes freed.\n", count);

	}



/*Iterate Function*/
void iterate(void *head, ActionFunction act) {
	Node *currentPtr = head;

		while(currentPtr != NULL) {
			act(currentPtr->data);
			currentPtr = currentPtr->next; 
		}

	}

/*Any function*/
int any(void *head, CriteriaFunction Criteria , void *helper) {
	int ret = 0; Node *currentPtr = head;

		while(currentPtr != NULL && ret == 0) {
			ret = Criteria(currentPtr->data, helper);
			currentPtr = currentPtr->next; 
		}

		if(ret != 0) ret = 1;
	
	return ret;

}



/*Terse insert: linked list*/

int insert(void *p2head, void *data, int (*Comparison) (void *data1, void *data2), FILE *fPtr) {
	int found = 0; Node **head = p2head; Node *addNode; int allocated = 0;

	/*Allocate a new node from malloc*/
	addNode = allocNode(fPtr);

	/*Make sure malloc didnt fail to allocate*/
		if (addNode != NULL) {
			allocated++;

			/*Add the data to the new node*/
			addNode->data = data;

			/*Skip nodes with bigger data than data to insert*/
				while(*head != NULL && (Comparison((*head)->data, data))){
						head = &((*head)->next);}

		/*Do the insert*/
		addNode->next = *head;
		*head = addNode;	}

	return allocated;
	}


/*Terse delete*/
/*deletesome*/
int deleteSome(void *p2head, CriteriaFunction mustGo , void *helper, ActionFunction Action, FILE *fPtr){
	int count = 0; Node *holder; Node **head = p2head;

		while(*head != NULL) {

		/*determine if we need to delete this pointer*/
			if(mustGo((*head)->data, helper) != 0) {
				/*delete the node*/
				holder = *head;
				*head = (*head)->next;
				Action(holder->data);
				freeNode(holder,fPtr); 
				count++;
					} else {
			
					/*Move p2head to the next thing it points to*/
					head = &((*head)->next);
						}}
	return count;
}


