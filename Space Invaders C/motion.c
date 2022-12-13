/*Motion.c file, Prepared by: Nicholas Trambitas*/
/*This file is responsible for motion related calculations*/

#include "struct.h"
#include "invaders.h"
#include "framerate.h"
#include "debug.h"
#include "linkedlist.h"

#include "memory.h"
#include "code.h"
#include "output.h"
#include "lab4.h"
#include "functions.h"
#include "motion.h"

#define one 1.0
#define three 3.0
#define xEdge 39.0
#define saucer 3

/*Function to update x*/
void updateX(alien *alnPtr) {

	alnPtr -> x = alnPtr -> x + alnPtr -> vx * alnPtr->simPtr->deltaT;

}

/*Function to update y*/
void updateY(alien *alnPtr) {
	alnPtr -> y = alnPtr->y + alnPtr->vy * alnPtr->simPtr->deltaT;
	if(alnPtr -> y <= 0){
	if (TEXT) printTdown(alnPtr);
	alnPtr->y = 0.0;
	 }
 }


/*Function to negate vx*/
void negVX(alien *alnPtr) {
	int type = alnPtr->type;
	if(type != saucer){
	if ((alnPtr->x >= xEdge) || (alnPtr->x <= -xEdge)) {
	alnPtr->vx = alnPtr->vx * -one;
	if(TEXT) printRev(alnPtr);
	drop3(alnPtr);
}}}

/*Function to drop 3*/
void drop3 (alien *alnPtr) {
	alnPtr->y = alnPtr->y - three;
	if (TEXT) printDrop(alnPtr);
	if(alnPtr->y <= 0) {
	if (TEXT) printTdown(alnPtr);
	alnPtr->y = 0.0;
	}}

/*Function to move the base to the right*/
void moveRight (alien *alnPtr) {
	/*Make sure base doesn't exceed the boundary*/
	if(alnPtr->simPtr->xCordBase < xEdge){
		alnPtr->simPtr->xCordBase = alnPtr->simPtr->xCordBase + 1;
	}
}

/*Function to move the base to the left*/
void moveLeft (alien *alnPtr) {
	/*Make sure base doesn't exceed the boundary*/
	if(alnPtr->simPtr->xCordBase > -xEdge){
		alnPtr->simPtr->xCordBase = alnPtr->simPtr->xCordBase - 1;
	}
}

