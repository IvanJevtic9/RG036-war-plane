#include <stdlib.h>
#include <stdio.h>
#include<math.h>

#include "init.h"
#include "GL/glut.h"
#include "draw.h"
#include "timer.h"
#include "callback.h"


/*funkcija koja iscrtava sve objekte , sva iscrtavanja u programu se nalaze ovde*/
void drawAll(){

	if(init_done && life>0){
		if(number == 25 )
			level = 1;	
		if(number==50)
			level = 2;
		if(number == 75)
			level = 3;

		level_pom = 10*level;

		basicDraw();	

		if(imp_active)
			draw_imp();	

		if(score>1000){	
			impediments2->in_live = 1;
			draw_imp2();
			if(!imp2_active){
				imp2_active = 1;
				glutTimerFunc(TIMER_INTERVAL3-level_pom,moveImpediments2,TIMER_ID);	
			}
		}
		fire();	

		printf("%d,%d,%d,ugao %f\n",score,number,life,plane->z_rotate);
	}
}
/*Odredjujemo koliziju izmedju prepreke i aviona kad im se poklopi opseg x-ose njihove sirine 
i kad im se prednja strana poklopi po z osi*/

int  coalision_plane_imp(int index){
	
	if( ((((impediments[index]->x_pos + impediments[index]->dim/2) - (plane->x_pos-0.125)) > 0 &&
		((impediments[index]->x_pos + impediments[index]->dim/2) - (plane->x_pos-0.125)) < (impediments[index]->dim + 0.25))
										|| 
		(((plane->x_pos+0.125)-(impediments[index]->x_pos - impediments[index]->dim/2)) > 0 &&
		((plane->x_pos+0.125)-(impediments[index]->x_pos - impediments[index]->dim/2))< (impediments[index]->dim + 0.25))) 
						&& 
	    plane->y_pos == impediments[index]->y_pos 
						&& 
	 	((impediments[index]->z_pos-impediments[index]->dim/2) >= 0.875 && 
		  (impediments[index]->z_pos+impediments[index]->dim/2) <= 1.225))		
	
		return 1;
	
	else 
		return 0;
}
/*kolizija izmedju metka i prepreke , moraja da im se opseg sirine(kad posmatramo u odnosu na prozor) poklopi negde na x osi da bi doslo do kolizije 
, i da im se opseg dubine poklopi */
int coalsion_bullet_imp(int index){

	int i;

	for(i=0;i<=4;i++){
		if(((((impediments[index]->x_pos + impediments[index]->dim/2) - (bullets[i]->x_pos-0.01)) > 0 &&
		((impediments[index]->x_pos + impediments[index]->dim/2) - (bullets[i]->x_pos-0.01)) < (impediments[index]->dim + 0.02))
											|| 
		(((bullets[i]->x_pos+0.01)-(impediments[index]->x_pos - impediments[index]->dim/2)) > 0 &&
		((bullets[i]->x_pos+0.01)-(impediments[index]->x_pos - impediments[index]->dim/2))< (impediments[index]->dim + 0.02))) 
							&& 
		bullets[i]->y_pos == impediments[index]->y_pos 
							&& 
		((impediments[index]->z_pos+impediments[index]->dim/2) >= (bullets[i]->z_pos ) &&
		((impediments[index]->z_pos-impediments[index]->dim/2) < (bullets[i]->z_pos + 0.2 )))
							&& 
		bullets[i]->in_live == 1)	
			
			return (i+1);
	}

	return 0;
}	
int  coalision_plane_imp2(){
	
	if( ((((impediments2->x_pos + impediments2->dim/2) - (plane->x_pos-0.125)) > 0 &&
		((impediments2->x_pos + impediments2->dim/2) - (plane->x_pos-0.125)) < (impediments2->dim + 0.25))
										|| 
		(((plane->x_pos+0.125)-(impediments2->x_pos - impediments2->dim/2)) > 0 &&
		((plane->x_pos+0.125)-(impediments2->x_pos - impediments2->dim/2))< (impediments2->dim + 0.25))) 
						&& 
	    plane->y_pos == impediments2->y_pos 
						&& 
	 	((impediments2->z_pos-impediments2->dim/2) >= 0.875 && 
		  (impediments2->z_pos+impediments2->dim/2) <= 1.225))		
	
		return 1;
	
	else 
		return 0;
}


int coalsion_bullet_imp2(){
	int i;

	for(i=0;i<=4;i++){
		if(((((impediments2->x_pos + impediments2->dim/2) - (bullets[i]->x_pos-0.01)) > 0 &&
		((impediments2->x_pos + impediments2->dim/2) - (bullets[i]->x_pos-0.01)) < (impediments2->dim + 0.02))
											|| 
		(((bullets[i]->x_pos+0.01)-(impediments2->x_pos - impediments2->dim/2)) > 0 &&
		((bullets[i]->x_pos+0.01)-(impediments2->x_pos - impediments2->dim/2))< (impediments2->dim + 0.02))) 
							&& 
		bullets[i]->y_pos == impediments2->y_pos 
							&& 
		((impediments2->z_pos+impediments2->dim/2) >= (bullets[i]->z_pos ) &&
		((impediments2->z_pos-impediments2->dim/2) < (bullets[i]->z_pos + 0.2 )))
							&& 
		bullets[i]->in_live == 1)	
			
			return (i+1);
	}

	return 0;
}	

/* crtanje aviona , krajnji izgled aviona cu izmeniti do zavrsetka projekta */
void basicDraw(){
	
	if(!coalision_plane_imp(0) && !coalision_plane_imp(1) && !coalision_plane_imp2() && plane->in_live){
	
		glPushMatrix();
			/*pozicioniramo se u kordinate sredista aviona i rotiramo avion*/
			glTranslatef(plane->x_pos,plane->y_pos,plane->z_pos);

			glRotatef(sin(plane->z_rotate)*15,0,0,1);
			
			/*telo aviona*/
			glPushMatrix();
				glColor3f(0.7,0.7,0.7);
				glScalef(0.3, 0.2, 1);
				glutSolidCube(0.25);
			glPopMatrix();
			/*krila aviona*/	
			
			glColor3f(0,0,0);
			
			glPushMatrix();
				glTranslatef(0, 0.025, -0.1);			
				glScalef(1, 0.2, 0.1);
				glutSolidCube(0.25); 
			glPopMatrix();
				
			glPushMatrix();
				glTranslatef(0, 0.025, 0);			
				glScalef(1, 0.2, 0.1);
				glutSolidCube(0.25);
			glPopMatrix();

		glPopMatrix();

	}
	else{
		/*ako dodje do kolizije avion nije u zivotu vise*/
		plane->in_live =0;
		if(!revive_active){
			revive_active=1;
			glutTimerFunc(700,Revive,TIMER_ID);
		}
	}


	glutPostRedisplay();
}
/* crtanje metkova , na osnovu kordinata koje joj prosledjujemo*/
void fire(){
	int i;
	for(i=0;i<5;i++){
		if(bullets[i]->in_live){

			glPushMatrix();
						glColor3f(1,0,0);
						glTranslatef(bullets[i]->x_pos, bullets[i]->y_pos, bullets[i]->z_pos);
						glutSolidSphere(0.02,50,20);
			glPopMatrix();

			glutPostRedisplay();
		}
	}
}
/*crtanje prepreka u kordinatama koje joj prosledimo*/
void draw_imp(){
	int i;
	for(i=0;i<2;i++){
		/*ako je prepreka u zivotu i ako nije doslo do kolizije izmedju nje i metka , crtaj prepreku*/
		if(impediments[i]->in_live && !coalsion_bullet_imp(i) && !coalision_plane_imp(i)){		
			
				glPushMatrix();
					glColor3f(0,0,1);
					glTranslatef(impediments[i]->x_pos,impediments[i]->y_pos,impediments[i]->z_pos);
					glutSolidCube(impediments[i]->dim);
				glPopMatrix();

				glutPostRedisplay();

			}
		else{
			/* u suprotnom doslo je do kolizije flag=1 oznaacavamo da je doslo do sudara izmedju metka i prepreke
			, kako bi znali da unistimo i metak jer funkcija coalision nece raditi jer je prepreka unistena */

			int flag = coalsion_bullet_imp(i);
			if(flag > 0)
				bullets[flag-1]->in_live = 0;
			
			impediments[i]->z_pos = -5;
			impediments[i]->x_pos = random_float(-0.9,0.9);
			impediments[i]->dim = random_float(0.04,0.27);
			impediments[i]->brzina = random_float(0.05,0.15);
			score = score + (int)(300*impediments[i]->dim);
			number++;

			glutPostRedisplay(); 
		}
	}
}
void draw_imp2(){
	
		if(impediments2->in_live && !coalsion_bullet_imp2() && !coalision_plane_imp2()){		
			
				glPushMatrix();
					glColor3f(1,1,0.3);
					glTranslatef(impediments2->x_pos,impediments2->y_pos,impediments2->z_pos);
					glutSolidCube(impediments2->dim);
				glPopMatrix();

				glutPostRedisplay();

			}
		else{
			/* u suprotnom doslo je do kolizije flag=1 oznaacavamo da je doslo do sudara izmedju metka i prepreke
			, kako bi znali da unistimo i metak jer funkcija coalision nece raditi jer je prepreka unistena */

			int flag = coalsion_bullet_imp2();
			if(flag > 0)
				bullets[flag-1]->in_live = 0;
			
			if(impediments2->health-1 == 0){
				impediments2->z_pos = -5;
				impediments2->x_pos = random_float(-0.9,0.9);
				impediments2->dim = random_float(0.05,0.25);
				impediments2->speed = random_float(0.05,0.15);
				impediments2->health = 2;
				score = score + (int)(500*impediments2->dim);
				number++;
			}
			impediments2->health--;

			glutPostRedisplay(); 
		}
}




