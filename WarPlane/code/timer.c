#include "timer.h"
#include "draw.h"
#include<GL/glut.h>
#include "init.h"
#include "callback.h"


/*Pozivamo tajmere koji se uvek izvrsavaju za svo vreme trajanja igre*/
void startTimers(){
	
		glutTimerFunc(TIMER_INTERVAL,rotatePlane,TIMER_ID);
	
}
/*rotacija aviona  , ogranicavamo max ugao */
void rotatePlane(int timer_id){

	if(timer_id != 1)
		return;

	if(plane->z_rotate>6.2832)
		plane->z_rotate = 0;
	if(plane->z_rotate<0)
		plane->z_rotate = 6.2832;


	plane->z_rotate += 0.1;


	glutPostRedisplay();
	
	glutTimerFunc(TIMER_INTERVAL,rotatePlane,TIMER_ID);

}


/*Tajmer za pokretanje prepreke , inicijalizujemo poziciju do koje moze da ide po z osi , cim stigne dotle 
ponovo ga vracamo na pocetak , za sad su ove prepreke ovake , kasnije cu doraditi da ih ima vise na sceni*/
void moveImpediments(int timer_id){

	if(timer_id != 1){
		return;
	}
	int i;

	for(i=0;i<2;i++){
		if(impediments[i]->z_pos > 1.25){
	
			impediments[i]->z_pos = -5;
			impediments[i]->x_pos = random_float(-0.9,0.9);
			impediments[i]->dim = random_float(0.04,0.27);
			impediments[i]->brzina = random_float(0.05,0.15);
		}
	
	
		impediments[i]->z_pos += impediments[i]->brzina;
		glutPostRedisplay();	
	}
	
	glutTimerFunc(TIMER_INTERVAL2-level_pom,moveImpediments,TIMER_ID);
	
}
/*pokretanje metkova , krecu se od samog aviona pa se udaljavaju po z osi , kad predje zadnju ravan isecanja scene 
oznacimo da je pucanje zavrseno , metak vise nije u zivotu*/
void moveBullets(int timer_id){

	
	if(timer_id != 1 ){
		return;
	}

	int i;	
	for(i=0;i<=4;i++){
		if(bullets[i]->in_live){
			if(bullets[i]->z_pos <= -5){
				bullets[i]->in_live = 0;
			}

			bullets[i]->z_pos -= 0.1;

			glutPostRedisplay();
		}
	}
	if(bullets[0]->in_live == 0 && bullets[1]->in_live == 0 && bullets[2]->in_live == 0 &&
		bullets[3]->in_live == 0 && bullets[4]->in_live == 0){
			timer_active = 0;
			return;
	}

	glutTimerFunc(TIMER_INTERVAL2,moveBullets,TIMER_ID);	
}
void moveImpediments2(int timer_id){
	if(timer_id != 1)
		return;

	if(impediments2->z_pos > 1.25){	
			impediments2->z_pos = -5;
			impediments2->x_pos = random_float(-0.9,0.9);
			impediments2->dim = random_float(0.05,0.25);
			impediments2->speed = random_float(0.05,0.15);
			impediments2->health = 2;
		}
	
	
		impediments2->z_pos += impediments2->speed;
		glutPostRedisplay();	
	
	
	glutTimerFunc(TIMER_INTERVAL3-level_pom,moveImpediments2,TIMER_ID);
}
void Revive(int timer_id){

	if(timer_id != 1)
		return;

	plane->in_live = 1;
	life--;
	revive_active = 0;

	return;
}
