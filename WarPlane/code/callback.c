#include "callback.h"	
#include "init.h"
#include "draw.h"		
#include "timer.h"
#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>



int window_width = 0;
int window_height = 0;

/*funkcija gde atributi min i max oznacava interval, u kojem funkcija vraca jedan broj iz tog intervala 
	po slucajnom izboru*/

float random_float(const float min, const float max)
{
    if (min < max) return (max - min) * ((float)rand() / RAND_MAX) + min;
      
    return 0;
}

void onDisplay(){
	/*cistimo ono sto se trenutno nalazi u prozoru programa*/
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	/*postavljanje vizira*/
	glViewport(0, 0, window_width, window_height);

	/*Podesavamo scenu to jest ugao ,odnos sirine i visine , prvu i zadnju ravan isecanja  */
 	 glMatrixMode(GL_PROJECTION);
 	 glLoadIdentity();
 	 gluPerspective(50, window_width/(float)window_height, 1, 20);

	/*podesavanje kamere , to jesto pozicioniramo gde se oko nalazi prve 3 kordinate , i u koju tacku gleda */
 	 glMatrixMode(GL_MODELVIEW);
 	 glLoadIdentity();
	 gluLookAt(0, 0.65 ,2, 0, 0, 0, 0, 1, 0);

	/*pozivamo crtanje objekata*/	
	drawAll();

	glutSwapBuffers();	

}


void onKeyboard(unsigned char c , int x, int y){
	
	switch(c){
		/*pomeranje aviona desno , levo*/
		case 'd' : 
				if(plane->x_pos < 0.6)
					plane->x_pos += 0.01;break;
		case 'a' : 
				if(plane->x_pos > -0.6 )
					plane->x_pos -= 0.01;break;
	
		/*izlaz iz programa*/
		case 'q' : exit(0);break;
		
		/*na komandu p ubacujemo prepreke i pokrecemo ih, za sad je moguce samo jedna prepreka da bude vidljiva na scecni
		  kasnije cu uvesti da ih bude vise */
		case 'p' : {	
			   if(!imp_active){	

					impediments->in_live = 1;		
					imp_active = 1;			
					glutTimerFunc(100,moveImpediments,1);
			 	}
			 };break;

		default : {}
	}
}

/*cuvamo visinu i sirinu prozora*/

void onReshape(int w_width, int w_height){

	window_width = w_width;
	window_height = w_height;

}


void onMouseClick(int button, int state, int x, int y){
	// levim klikom zapocinjemo pucanje , za sad je moguce samo jedan metak , dok se on ne zavrsi necemo moci da ispalimo drugi 
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		if(!fire_active){
				bullets->in_live = 1;
				fire_active = 1 ;
				glutTimerFunc(100,moveBullets,1);
			}
}

void onMouseMove(int x,int y){

	
}

