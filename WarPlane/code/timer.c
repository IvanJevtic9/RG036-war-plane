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

	if(plane->z_rotate <= 360 )	
		plane->z_rotate += 0.1;
	else
		plane->z_rotate = 0;

	glutTimerFunc(TIMER_INTERVAL,rotatePlane,TIMER_ID);

}

/*Tajmer za pokretanje prepreke , inicijalizujemo poziciju do koje moze da ide po z osi , cim stigne dotle 
ponovo ga vracamo na pocetak , za sad su ove prepreke ovake , kasnije cu doraditi da ih ima vise na sceni*/
void moveImpediments(int timer_id){

	if(timer_id != 1){
		return;
	}
	

	if(imp_active ){
		if(impediments->z_pos > 1.25){
	
			impediments->z_pos = -5;
			impediments->x_pos = random_float(-1,1);
			impediments->dim = random_float(0.02,0.3);
			impediments->brzina = random_float(0.05,0.15);
			/*imp_active = 0;
			impediments->in_live = 0;			
			return ;*/
		}
	
	
		impediments->z_pos += impediments->brzina;
		glutPostRedisplay();	
	}
	
	glutTimerFunc(TIMER_INTERVAL2,moveImpediments,TIMER_ID);
	
}
/*pokretanje metkova , krecu se od samog aviona pa se udaljavaju po z osi , kad predje zadnju ravan isecanja scene 
oznacimo da je pucanje zavrseno , metak vise nije u zivotu*/
void moveBullets(int timer_id){

	if(timer_id != 1 ){
		return;

		}
	
	if(fire_active ){
		if(bullets->z_pos <= -5){
			fire_active = 0;
			bullets->in_live = 0;
			return;
		}

		bullets->z_pos -= 0.1;

		glutPostRedisplay();
	}

	if(iskljuci_timerB){
		iskljuci_timerB = 0;
		return;
	}

	glutTimerFunc(TIMER_INTERVAL2,moveBullets,TIMER_ID);	
}



