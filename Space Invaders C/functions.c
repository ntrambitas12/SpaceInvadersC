/*Functions.c, This file holds all the required callback functions. 
 * Prepared by: Nicholas Trambitas*/

 #include <stdio.h>
 #include <stdlib.h>

 #include "linkedlist.h"
 #include "debug.h"
 #include "framerate.h"
 #include "struct.h"

 #include "functions.h"
 #include "memory.h"
 #include "code.h"
 #include "output.h"
 #include "lab4.h"
 #include "motion.h"
 #include "invaders.h"

 #define SAUCER 3
 #define xEdge 39.0
 #define ONE 1

/*Function to fight back*/
void fightBack(alien *ptr) {
	typedef int (*criteriaFunc) (void*, void*);
	typedef void (*actionFunc) (void*);
	criteriaFunc base = &overBase;
	actionFunc score = &fought;
	if(GRAPHICS)sa_bolt(ptr->simPtr->xCordBase);

	deleteSome(&(ptr->simPtr->listPtr), base, NULL, score, ptr->simPtr->fOut);

}

/*Criteria function to determine if alien is over base*/
int overBase (void *data, void *helper) {
	alien *ptr = data;
	return (((int)(ptr->x)) == ptr->simPtr->xCordBase);
}

/*Action function to print fight back and assign scores*/
void fought (void *data) {
	alien *ptr = data;
	/*update score*/
	ptr->simPtr->score = ptr->simPtr->score + ptr->point;
	/*print message*/
	if(TEXT)fprintf(ptr->simPtr->fOut, "\nBolt hits alien at (%.5f, %.5f), worth %d points!\n",ptr->x, ptr->y, ptr->point);
	if(GRAPHICS)sa_status("Bolt hits an alien!");
	/*Free the alien*/
	freeAlien(ptr);
}
/*Function to remove flying saucers*/
void deleteSaucer(alien *ptr) {
	typedef int (*criteriaFunc) (void*, void*);
	typedef void (*actionFunc) (void*);
	criteriaFunc toRemove = &toRemoveSaucer;
	actionFunc print = &printSaucer;
	deleteSome(&(ptr->simPtr->listPtr), toRemove, NULL, print, ptr->simPtr->fOut);
}

/*Function to determine if saucer should be removed*/
int toRemoveSaucer (void *data, void *helper) {
	alien *ptr = data;
	return((ptr -> type == SAUCER) && ((ptr -> x > xEdge) || (ptr->x < -xEdge))); 
}

/*Action function that prints out message that flying saucer was removed*/
void printSaucer (void *data) {
	alien *ptr = data;
	if (TEXT)fprintf(ptr->simPtr->fOut, "\nFlying saucer worth %d points escapes at ET = %.5f!\n", ptr->point, ptr->simPtr->ET);
	if (GRAPHICS)sa_status("Flying saucer escapes!");
	/*Free the alien*/
	freeAlien(ptr);

}



/*Function to clear list*/
void clearList(alien *ptr) {
	typedef int (*criteriaFunc) (void*, void*);
	typedef void (*actionFunc) (void*);
	int del;
	criteriaFunc toRemove = &toClearList;
	actionFunc print = &printClear;
	if(TEXT)fprintf(ptr->simPtr->fOut, "\nClearing the attacking list\n");
	del = deleteSome(&(ptr->simPtr->listPtr), toRemove, NULL, print, ptr->simPtr->fOut);
	if(TEXT)fprintf(ptr->simPtr->fOut, "... %d cleared", del);
}

/*Function to determine if list should be cleared*/
int toClearList (void *data, void *helper) {
	alien *ptr = data;
	return ONE; 
}

/*Action function that frees the remaining aliens on the list*/
void printClear (void *data) {
	alien *ptr = data;
	freeAlien(ptr);
}

/*function to determine if any alien on the ground*/
int isLanded (alien *ptr) {
	typedef int (*criteriaFunc) (void*, void*);
	criteriaFunc landed = &onGround;
	return any(ptr->simPtr->listPtr,landed, NULL);
}

/*criteria func to actually verify if alien on the ground*/
int onGround (void *data, void *helper) {
	alien *ap1 = data;
	return ap1->y == 0.0;
}
/*function to update alien motion*/
void moveAlien(void *data){
 	alien *alnPtr = data;
	 updateX(alnPtr);
  	updateY(alnPtr);
  	negVX(alnPtr);

}

/*function to iterate the list and move the alien*/
void moveAlienPos (alien *alnPtr) {
	typedef void (* ActionFunc) (void*);
	ActionFunc move = &moveAlien;
	iterate(alnPtr->simPtr->listPtr,move);
}

/*function that will add alien to linked list*/
int addAlien (alien *ptr) {
	/*set the comparsion func to compareAltitude */
	int ret;
	typedef int (*compareFunc) (void*, void*);
	compareFunc altitude = &compareAltitude;
	ret = insert(&(ptr->simPtr->listPtr) , ptr, altitude, ptr->simPtr->fOut);
	return ret;
}


/*function that compares altitude of alien*/
int compareAltitude (void *data1, void *data2) {
	double alt1, alt2;
	alien *ap1 = data1;
	alien *ap2 = data2;
	alt1 = ap1->y;
	alt2 = ap2->y;
	return (alt1 < alt2);
}

/*function that prints all  aliens from the listn to write to file*/
void printAlien (alien *ptr) {
	typedef void (*action) (void*);
	action printOut = &printData;
	iterate((ptr->simPtr->listPtr), printOut);
	if(TEXT) fprintf(ptr->simPtr->fOut, "\n");
}

/*helper function to actually print the alien*/
void printData (void *data) {
	alien *ap1 = data;
	if(TEXT) printInvader(ap1); 
}

/*function that prints all  aliens from the list to the screen during graphics mode*/
void putAlien (alien *ptr) {
	typedef void (*action) (void*);
	action printOut1 = &putData;
	iterate((ptr->simPtr->listPtr), printOut1);
}

/*helper function to actually print the alien*/
void putData (void *data) {
	alien *ap1 = data;
    sa_alien(ap1->type, ap1->color, ap1->x, ap1->y);
}


