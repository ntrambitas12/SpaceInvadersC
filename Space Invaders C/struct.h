/*File to hold structures, Prepared by: Nicholas Trambitas*/
#include <stdio.h>
 typedef struct {
     double ET;
     void *listPtr;
     int xCordBase;
     int score;
     double deltaT;
     FILE *fIn;
     FILE *fOut;
	 int input;
} sim;

typedef struct {
     unsigned int code;
     double x;
     double y;
     double vx;
     double vy;
     int type;
     int color;
     int point;
     sim *simPtr;
   } alien;

