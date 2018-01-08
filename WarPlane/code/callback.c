#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include "callback.h"	
#include "init.h"
#include "draw.h"		
#include "timer.h"

int window_width = 0;
int window_height = 0;

GLuint tekstura[2];

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
	 gluLookAt(0,0.65,2, 0, 0, 0, 0, 1, 0);

	glDepthMask(GL_FALSE);
  	glDisable(GL_DEPTH_TEST);
 	glDisable(GL_LIGHTING);
  
  	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
 	glBindTexture(GL_TEXTURE_2D,tekstura[1]);
  	glBegin(GL_QUADS);
    	glNormal3f(0,0,1);
    	glTexCoord2f(0,0);
    	glVertex3f(-3,-3,-0.99);
    	glTexCoord2f(1,0);
    	glVertex3f(3,-3,-0.99);
    	glTexCoord2f(1,1);
    	glVertex3f(3,3,-0.99);
    	glTexCoord2f(0,1);
    	glVertex3f(-3,3,-0.99);
  	glEnd();
  	glBindTexture(GL_TEXTURE_2D,0);
  
  	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  	glEnable(GL_DEPTH_TEST);
  	glDepthMask(GL_TRUE);


	/*pozivamo crtanje objekata*/	
	drawAll();

	glutSwapBuffers();	

}


void onKeyboard(unsigned char c , int x, int y){
	
	switch(c){
		/*pomeranje aviona desno , levo*/
		case 'd' : 
				if(plane->x_pos < 0.8)
					plane->x_pos += 0.02;break;
		case 'a' : 
				if(plane->x_pos > -0.8 )
					plane->x_pos -= 0.02;break;
					
		case 'D' : 
				if(plane->x_pos < 0.8)
					plane->x_pos += 0.02;break;
		case 'A' : 
				if(plane->x_pos > -0.8 )
					plane->x_pos -= 0.02;break;
		

		/*izlaz iz programa*/
		case 27 : exit(0);break;
		
		/*na komandu p ubacujemo prepreke i pokrecemo ih, za sad je moguce samo jedna prepreka da bude vidljiva na scecni
		  kasnije cu uvesti da ih bude vise */
		case 'p' : {	
			   if(!imp_active){	

					impediments->in_live = 1;		
					imp_active = 1;			
					glutTimerFunc(TIMER_INTERVAL2,moveImpediments,TIMER_ID);
			 	}
			 };break;

		case 'P' : {	
			   if(!imp_active){	

					impediments->in_live = 1;		
					imp_active = 1;			
					glutTimerFunc(TIMER_INTERVAL2,moveImpediments,TIMER_ID);
			 	}
			 };break;

		/*vracanje aviona u zivot , nece biti ovako an kraju , cisto sam uveo to radi provere, da ne izlazim non stop iz programa*/
		case 'r':
			plane->in_live=1;	 
				break;

		case 'R':
			plane->in_live=1;	 
				break;

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
	
	int n;

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		/* ako je pucnjava ne aktivna i ako je avion u zivotu zapocinjemo pucnjavu  */
		if(plane->in_live == 1){
			for(n=0;n<5;n++){
				if(bullets[n]->in_live == 0){	
					bullets[n]->in_live = 1;
					
					/*pocetna kordinata projektila*/
					bullets[n]->x_pos = plane->x_pos;
					bullets[n]->y_pos = plane->y_pos;
					bullets[n]->z_pos = plane->z_pos;
					
					if(!timer_active){
						timer_active = 1;
						glutTimerFunc(TIMER_INTERVAL2,moveBullets,TIMER_ID);
					}
					break;
				}
			}
		}	
		else{
			 
		}
	}	
}


void onMouseMove(int x,int y){
	/*!fire_active
	*/
}

