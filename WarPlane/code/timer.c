#include "timer.h"
#include "draw.h"
#include<GL/glut.h>
#include "init.h"
#include "callback.h"

void startTimers(){

	glutTimerFunc(10,rotatePlane,1);
	
	

}
// rotaciaj aviona , nije najpravilnija za sada 
void rotatePlane(int timer_id){

	if(timer_id != 1)
		return;

	if(plane->z_rotate <= 360 )	
		plane->z_rotate += 0.1;
	else
		plane->z_rotate = 0;

	glutTimerFunc(100,rotatePlane,1);

}
// tajmer za animaciju kretanja metka
void moveBullets(int timer_id){

	if(timer_id != 1 ){
		return;

	}

	if(fire_active){

		if(bullets->z_pos < -5){
			bullets->z_pos =  1;
			fire_active = 0;
			bullets->in_live = 0;
			return;
		}
	
		bullets->z_pos -= 0.2;
	
		glutPostRedisplay();

	}
	
	glutTimerFunc(30,moveBullets,1);	
}



