/*Output.c file, Prepared by: Nicholas Trambitas
 * This file is responsible for outputing data to screen*/
 #include <stdio.h>
 
 #include "struct.h"
 #include "debug.h"
 #include "invaders.h"
 #include "linkedlist.h"
 #include "framerate.h"

 #include "functions.h"
 #include "output.h"
 #include "code.h"
 #include "lab4.h"
 #include "motion.h"
 #include "memory.h"

 #define DELAY 4.0
 #define CONVER 1000000 
 /*function that prints out text for invader*/
void  printInvader(alien *alienPtr) {	
	 fprintf(alienPtr->simPtr->fOut, "%#X\t%d %d %3d\t(% 9.5f, %8.5f) (% 9.5f, % 9.5f)\n", alienPtr -> code, alienPtr ->type, alienPtr->color, alienPtr->point, alienPtr->x, alienPtr->y, alienPtr->vx,alienPtr->vy);
}

/*Function to print the header for the invader table*/
void printHeader(alien *ptr) {
 	fprintf(ptr->simPtr->fOut, "\nCode\t\tT C Pts ( __X_____, __Y_____) ( __VX____,  __VY____) ET= %.5f\n", ptr->simPtr->ET);
}

/*function to draw one frame of the alien REMOVE COUNT*/
void drawFrame(alien *ptr, int status, int count) {
	sa_clear();
	sa_base(ptr->simPtr->xCordBase);
	putAlien(ptr);
	sa_score(ptr->simPtr->score);
	if(ptr->simPtr->input == 32) sa_bolt(ptr->simPtr->xCordBase);
	sa_refresh();
	if(!status) microsleep((int) (ptr->simPtr->deltaT  * CONVER));
	if(status) microsleep((int) (DELAY * CONVER));}

/*function that prints out touchdown messasge*/
void printTdown(alien *alienPtr) {
	fprintf(alienPtr->simPtr->fOut, "\nAlien %X touches down at X= %.5f!\n", alienPtr -> code, alienPtr -> x);
}


/*function that prints reversing message*/
void printRev(alien *alienPtr) {
	fprintf(alienPtr->simPtr->fOut, "\nAlien %X at (%.5f, %.5f) changes VX to %+.5f\n", alienPtr -> code, alienPtr -> x, alienPtr -> y, alienPtr ->  vx);
}

/*function that prints drop 3 message*/
void printDrop(alien *alienPtr) {
	fprintf(alienPtr->simPtr->fOut, "\nAlien %X at drops to (%.5f, %.5f), VX to %+.5f at ET %.5f\n", alienPtr -> code, alienPtr -> x, alienPtr -> y, alienPtr ->  vx, alienPtr->simPtr->ET);
}

/*function that prints why input terminated*/
void printTerm(int lineIn, alien *ptr) {
	fprintf(ptr->simPtr->fOut, "Input terminated: scanf returned %d\n", lineIn);
}

/*function that outputs final run time*/
void finalRT(double time) {
	printf("\nTotal run time is %.9f seconds.\n", time);
}

/*function to print debug message for type*/
void debugType(alien *ptr){
	fprintf(ptr->simPtr->fOut, "\ntype_from_code: isolating 3 bits after shifting 12 on %x gives %d\n", ptr -> code, ptr -> type);
}
/*function to print debug message for color*/
void debugColor(alien *ptr){
	fprintf(ptr->simPtr->fOut, "color_from_code: isolating 3 bits after shifting 4 on %x gives %d\n", ptr -> code, ptr -> color);
}

/*function to print debug message for points*/
void debugPoint(alien *ptr){
	fprintf(ptr->simPtr->fOut, "points_from_code: isolating 9  bits after shifting 20 on %x gives %d\n", ptr->code, ptr -> point);
}

/*function that determins if time elapsed is whole second or not*/
int wholeSecond (int count, alien *ptr) {
	int fps = (int) 1 / (ptr->simPtr->deltaT);
	if(count % fps != 0) {
	/*not whole second*/
	return 0;}
/*whole second*/
	if (DEBUG){
	fprintf(ptr->simPtr->fOut, "\nwholeSecond: new second in game reached\n");}
	return 1;}

/*Function to print number of aliens allocated to list*/
void allocPrint (int amount, alien *ptr) {
	fprintf(ptr->simPtr->fOut, "allocate_alien: %d allocated\n", amount);
}

/*Function to print number of aliens deleted from list*/
void freePrint (int amount, alien *ptr) {
	fprintf(ptr->simPtr->fOut, "free_alien: %d freed\n", amount);
}

/*Function that prints error in allocating alien*/
void allocFailPrint(alien *ptr){
	fprintf(ptr->simPtr->fOut, "ERROR:allocate_alien: failed to allocate\n");
}

/*Function to print win state*/
void printWin(alien *ptr){
	fprintf(ptr->simPtr->fOut, "\nVictory! No attackers remain at ET = %.5f\n", ptr->simPtr->ET);
	fprintf(ptr->simPtr->fOut, "Total score is %d points\n", ptr->simPtr->score);
}

/*Function to print lose state*/
void printLose(alien *ptr){
	fprintf(ptr->simPtr->fOut, "\nDefeat! Aliens land at ET = %.5f\n", ptr->simPtr->ET);
	fprintf(ptr->simPtr->fOut, "Total score is %d points\n", ptr->simPtr->score);
}
