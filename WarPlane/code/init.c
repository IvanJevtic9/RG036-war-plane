#include "init.h"
#include "draw.h"
#include "GL/glut.h"
#include "timer.h"
#include "callback.h"
#include "allocation.h"


int fire_active = 0;
int init_done = 0;

Bullet* bullets = NULL;
Plane* plane = NULL;

//inicijalizacija objekata , igre

void initGame(){
	plane = newPlane( 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1);
	bullets = newBullet( 0 , 0 , 1 , 1 );
	
	init_done = 1;

}



void startGame(){

	initGame();
	startTimers();
	
}
