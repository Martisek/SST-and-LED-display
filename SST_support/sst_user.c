#include "sst.h"
#include <stdio.h>
#include <stdlib.h>

int idle_counter = 0;
/*The use of this function is optional*/
/*It's implementation is required     */

void SST_init(void) {
	//before doing any OS realted stuff
	//you may need to cofigure you system
	//that kind of general configuration
	//goes here
	//I.E.  processor clock setup
  
}

/*The implempletation of the following functions is required*/
void SST_start(void) {
	//enable some sepecific interrupts
	//start some periperial ,timers ..
	//your tasks are about to start
	//do they need somthing
	//that haven't been done before?


}
/*....................................*/
void SST_onIdle(void) {
    
	//spare time
	//do anithing you want
	//but do not loop
	//you may want to post some events anyway
	//no time critical operations
    
    
	idle_counter ++;


}
/*....................................*/
void SST_exit(void) {
	//shutdown some peripherials and stuff
 	return;
}



