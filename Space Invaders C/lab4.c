/*lab4.c: Nicholas Trambitas*/

 
 #include <stdio.h>
 #include <stdlib.h>

 #include "linkedlist.h"
 #include "debug.h"
 #include "struct.h"
 #include "framerate.h"

 #include "functions.h"
 #include "memory.h"
 #include "code.h"
 #include "output.h"
 #include "lab4.h"
 #include "motion.h"
 #include "invaders.h"

 #define EXIT 0;
 #define FIVE 5
 #define ONE 1

/*Read loop*/

void readFile (double time, char *fName, char *oName) {
unsigned int code; double x, y, vx, vy; int itmRd, fileStatus;  alien *alienPtr, *dynPtr, alien1; sim sim1, *simPtr;
	
	/*Intialize sim struct ptr and open file*/
	simPtr = &sim1;	alienPtr = &alien1; initSim(simPtr, time); fileStatus = fileOpen (fName, oName, simPtr);

		if (fileStatus == 0){
		/*Only store in struct  if 5 lines of data was read*/
   			while(FIVE == (itmRd = fscanf(simPtr->fIn, "%x %lf %lf %lf %lf", &code, &x, &y, &vx, &vy))) {
   				 /*write alien struct*/
 				 writeAlien((&alienPtr), &simPtr,x, y, vx, vy, code);
     			 /*function call here to store static alien struct to a dynamic one*/
			      dynPtr = allocAlien(alienPtr); 
    			 /*only copy static struct to dynamic if pointer is not null */
  			     if (dynPtr != NULL){
    				   *dynPtr = *alienPtr;
      					/*add alien to the list*/
  					    addAlien(dynPtr);
    		  	} else allocFailPrint(alienPtr);	 }
		  afterRead(&alienPtr, itmRd); } }


/*Function that will open files*/
int fileOpen(char *fName, char *oName, sim *ptr){
	/* 0: no error, 1: open error*/
	int ret = 0;
	ptr->fIn = fopen(fName, "r");
	ptr->fOut = fopen(oName, "w");
    
	/*Error opening input file*/
		if(ptr->fIn == NULL){
			ret = 1; }

	/*Input file opened but output didn't*/
		else if(ptr->fIn != NULL && ptr->fOut == NULL){
			ret = 1;
			fclose(ptr->fIn);}

	return ret;
   }


/*Function to close the files at the end of the game*/
void fileClose(alien *ptr) {
	fclose(ptr->simPtr->fIn);
	fclose(ptr->simPtr->fOut);
}


	

/*function that will store the alienPtr*/
void writeAlien (alien **alienPtr, sim **simPtr, double x, double y, double vx, double vy, unsigned int code) {
  	(*alienPtr) -> simPtr = &(**simPtr);
  	(*alienPtr) -> code = code;
  	(*alienPtr) -> x = x;
   	(*alienPtr) -> y = y;
  	(*alienPtr) -> vx = vx;
   	(*alienPtr) -> vy = vy;
  	(*alienPtr) -> type = getType(code);
   	(*alienPtr) -> color = getColor(code);
  	(*alienPtr) -> point = getPoint(code);

}


/*function that will execiute after reading the aliens*/
void afterRead(alien **dynPtr, int itmRd) {
  /*print number of lines read when input terminates*/
	if(TEXT)printTerm(itmRd, *dynPtr);
    if(itmRd == -ONE){
	 simLoop(*dynPtr);
/*determine the ending*/
 	determineEnding(*dynPtr);	 
/*clear the list at the end*/
	clearList(*dynPtr);}	
/*close the file*/
	fileClose(*dynPtr);

}


/*function that determins how the game ended*/
void determineEnding (alien *ptr) {
		/*game won:*/
	if(ptr->simPtr->listPtr == NULL) {
		if (TEXT) printWin(ptr);
	} else {
		if(TEXT && !DEBUG){
			printHeader(ptr);
			printAlien(ptr); }
		 printLose(ptr); }
	}


/*Simulation loop: Moves alien around until it hits bottom of screen*/
void simLoop (alien *alnPtr) {
	static int count = ONE;  int finished = 0;
		while (!isLanded(alnPtr) && alnPtr->simPtr->listPtr!= NULL) {
			runGame(alnPtr, count);
			if(GRAPHICS) drawFrame(alnPtr, finished, count);	
			if(DEBUG || wholeSecond(count, alnPtr)){
				printHeader(alnPtr);
				printAlien(alnPtr);
			}count++;}
	finished = ONE;
	if(GRAPHICS) drawFrame(alnPtr, finished, count); }


/*helper function to condense simLoop to run game*/
void runGame(alien *alnPtr, int count) {
	/*Define array of function pointers*/
	 void (*jumpTable[256])(alien *) = {NULL};
	 jumpTable[32] = &fightBack;
	 jumpTable[52] = &moveLeft;
 	 jumpTable[54] = &moveRight;

	/*read in key stroke from user*/
	alnPtr->simPtr->input = sa_getch();
	/*update elasped time*/
	alnPtr -> simPtr-> ET = alnPtr ->simPtr->deltaT * count;
	/*move the alien*/
	moveAlienPos(alnPtr);
	/*fight back*/
	if(!GRAPHICS && !wholeSecond(count, alnPtr) == 0) fightBack(alnPtr);
	if(GRAPHICS && alnPtr->simPtr->input != -1 && ((jumpTable[alnPtr->simPtr->input]) != NULL))jumpTable[alnPtr->simPtr->input](alnPtr);
	/*delete saucers*/
	deleteSaucer(alnPtr);}


/*main loop. Sets up, starts, and tears down simulation*/
 int main(int argc, char *argv[]) {	
  if(argc != 2){ 
    /*Read in Alien File and Output to Screen*/
	double time, timeEnd;  int gStart = 0;
	time = now();
	/*Set up graphics engine*/
      if(GRAPHICS && sa_initialize())gStart = ONE;
      readFile(time, argv[1], argv[2]);
	 if(gStart != 0)sa_teardown();
	/*print out final running time*/
	timeEnd = now();
	finalRT(timeEnd-time);
	} 
	return EXIT;	}





