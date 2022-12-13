/*Memory.c, Prepared by: Nicholas Trambitas*/
#include <stdio.h>
#include <stdlib.h>
#include "altmem.h"

 #include "linkedlist.h"
 #include "debug.h"
 #include "framerate.h"
 #include "struct.h"
 #include "invaders.h"

 #include "functions.h"
 #include "memory.h"
 #include "code.h"
 #include "output.h"
 #include "lab4.h"
 #include "motion.h"
 

/*function to take static struct and reallocate to dynamic memory*/
 alien* allocAlien(alien *ptr) {
	 static int count; alien *dynm;
	dynm =  alternative_malloc(sizeof(*ptr));
	if (dynm != NULL){
		count++;
		if (TEXT)allocPrint(count, ptr);
		}
	 return dynm; 
}

/*function that will free dynamic pointer*/
void freeAlien(alien *ptr) {
	static int count;
	count++;
	if (TEXT)freePrint(count, ptr);
	alternative_free(ptr);

}

/*Function to intialize sim struct */
void initSim (sim *ptr, double time) {
	ptr -> ET = time;
	ptr -> xCordBase = 0;
	ptr -> score = 0;
	ptr -> listPtr = NULL;
	ptr -> deltaT = DELTA;
	ptr -> fIn = NULL;
	ptr -> fOut = NULL;
	ptr -> input = 0;
}




