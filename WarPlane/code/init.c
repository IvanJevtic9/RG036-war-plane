#include "init.h"
#include "draw.h"
#include "GL/glut.h"
#include "timer.h"
#include "callback.h"
#include "allocation.h"



int init_done = 0;


Plane* plane = NULL;


void initGame(){

	
	plane = newPlane( 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1);
	
	init_done = 1;

}



void startGame(){

	initGame();
	startTimers();
	
}
