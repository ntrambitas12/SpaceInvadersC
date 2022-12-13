/* Nicholas Trambitas */

int addAlien (alien *ptr) ;
void clearList(alien *ptr) ;
int compareAltitude (void *data1, void *data2) ;
void deleteSaucer(alien *ptr) ;
void fightBack(alien *ptr) ;
void fought (void *data) ;
int isLanded (alien *ptr) ;
void moveAlien(void *data);
void moveAlienPos (alien *alnPtr) ;
int onGround (void *data, void *helper) ;
int overBase (void *data, void *helper) ;
void printAlien (alien *ptr) ;
void printClear (void *data) ;
void printData (void *data) ;
void printSaucer (void *data) ;
void putAlien (alien *ptr) ;
void putData (void *data) ;
int toClearList (void *data, void *helper) ;
int toRemoveSaucer (void *data, void *helper) ;
