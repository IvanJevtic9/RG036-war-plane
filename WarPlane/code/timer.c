#include "timer.h"
#include "draw.h"
#include<GL/glut.h>
#include "init.h"
#include "callback.h"

void startTimers(){

	glutTimerFunc(10,rotatePlane,1);
	
	

}

void rotatePlane(int timer_id){

	if(timer_id != 1)
		return;

	if(plane->z_rotate <= 360 )	
		plane->z_rotate += 0.1;
	else
		plane->z_rotate = 0;

	glutTimerFunc(100,rotatePlane,1);

}




