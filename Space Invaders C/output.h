/* Nicholas Trambitas */

void allocFailPrint(alien *ptr);
void allocPrint (int amount, alien *ptr) ;
void debugColor(alien *ptr);
void debugPoint(alien *ptr);
void debugType(alien *ptr);
void drawFrame(alien *ptr, int status, int count) ;
void finalRT(double time) ;
void freePrint (int amount, alien *ptr) ;
void printDrop(alien *alienPtr) ;
void printHeader(alien *ptr) ;
void printInvader(alien *alienPtr) ;
void printLose(alien *ptr);
void printRev(alien *alienPtr) ;
void printTdown(alien *alienPtr) ;
void printTerm(int lineIn, alien *ptr) ;
void printWin(alien *ptr);
int wholeSecond (int count, alien *ptr) ;
