/*Lab 4, Code.c file. Prepared by: Nicholas Trambitas
 * This file holds the code that manipulates and stores
 * the read in bits of data. */
#define ONE 1
#define TWO 2
#define FOUR 4
#define EIGHT 8
#define	SIXTEEN 16
#define THIRTYTWO 32
#define SIXTYFOUR 64
#define ONETWOEIGHT 128
#define TWOFIVESIX 256
#define TYPEBIT 12
#define COLORBIT 4
#define POINTBIT 20

#include "struct.h"
#include "debug.h"
#include "framerate.h"
#include "linkedlist.h"
#include "invaders.h"

#include "memory.h"
#include "code.h"
#include "output.h"
#include "lab4.h"
#include "motion.h"
#include "functions.h"

/*function that gets type of alien*/
int getType (unsigned int code) {
int type;
	/*try to shift 12 bits */
	 code = code >> TYPEBIT;
	 /*get the 3 type bits and return as int*/
	 type = (code & FOUR) + (code & TWO) + (code & ONE);
	return type;
	}

/*function that gets the color of alien*/
int getColor (unsigned int code) {
int color;
	/*try to shift 4 bits */
	code = code >> COLORBIT;
	/*get the 3 color bits and return as int */
	color = (code & FOUR) + (code & TWO) + (code & ONE);	
	return color;
	
}

/*function that gets point value of alien*/
int getPoint (unsigned int code) {
int point;
	/*try to shift 20 bits */
	code = code >> POINTBIT;
	/* get the 9 point bits and return as an int */
	point = (code&TWOFIVESIX)+(code&ONETWOEIGHT)+(code&SIXTYFOUR)+(code&THIRTYTWO)+(code&SIXTEEN)+
	(code&EIGHT)+(code&FOUR)+(code&TWO)+(code&ONE);
	return point;
}




