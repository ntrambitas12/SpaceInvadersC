/* Nicholas Trambitas */

void afterRead(alien **dynPtr, int itmRd) ;
void determineEnding (alien *ptr) ;
void fileClose(alien *ptr) ;
int fileOpen(char *fName, char *oName, sim *ptr);
int main(int argc, char *argv[]) ;
void readFile (double time, char *fName, char *oName) ;
void runGame(alien *alnPtr, int count) ;
void simLoop (alien *alnPtr) ;
void writeAlien (alien **alienPtr, sim **simPtr, double x, double y, double vx, double vy, unsigned int code) ;
