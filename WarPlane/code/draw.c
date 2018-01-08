#include "init.h"
#include "GL/glut.h"
#include<math.h>
#include "draw.h"
#include "timer.h"
#include <stdlib.h>
#include <stdio.h>
#include "callback.h"

/*funkcija koja iscrtava sve objekte , sva iscrtavanja u programu se nalaze ovde*/
void drawAll(){

	if(init_done){
		basicDraw();	

		if(imp_active)
			draw_imp();	

		fire();	
	}
}
/*Odredjujemo koliziju izmedju prepreke i aviona kad im se poklopi opseg x-ose njihove sirine 
i kad im se prednja strana poklopi po z osi*/

int  coalision_plane_imp(){
	
	if( ((((impediments->x_pos + impediments->dim/2) - (plane->x_pos-0.125)) > 0 &&
		((impediments->x_pos + impediments->dim/2) - (plane->x_pos-0.125)) < (impediments->dim + 0.25))
										|| 
		(((plane->x_pos+0.125)-(impediments->x_pos - impediments->dim/2)) > 0 &&
		((plane->x_pos+0.125)-(impediments->x_pos - impediments->dim/2))< (impediments->dim + 0.25))) 
						&& 
	    plane->y_pos == impediments->y_pos 
						&& 
	 	((impediments->z_pos-impediments->dim/2) >= 0.875 && 
		  (impediments->z_pos+impediments->dim/2) <= 1.225))		
	
		return 1;
	
	else 
		return 0;
}
/*kolizija izmedju metka i prepreke , moraja da im se opseg sirine(kad posmatramo u odnosu na prozor) poklopi negde na x osi da bi doslo do kolizije 
, i da im se opseg dubine poklopi */
int coalsion_bullet_imp(){

	int i;

	for(i=0;i<=4;i++){
		if(((((impediments->x_pos + impediments->dim/2) - (bullets[i]->x_pos-0.01)) > 0 &&
		((impediments->x_pos + impediments->dim/2) - (bullets[i]->x_pos-0.01)) < (impediments->dim + 0.02))
											|| 
		(((bullets[i]->x_pos+0.01)-(impediments->x_pos - impediments->dim/2)) > 0 &&
		((bullets[i]->x_pos+0.01)-(impediments->x_pos - impediments->dim/2))< (impediments->dim + 0.02))) 
							&& 
		bullets[i]->y_pos == impediments->y_pos 
							&& 
		((impediments->z_pos+impediments->dim/2) >= (bullets[i]->z_pos ) &&
		((impediments->z_pos-impediments->dim/2) < (bullets[i]->z_pos + 0.2 )))
							&& 
		bullets[i]->in_live == 1)	
			
			return (i+1);
	}

	return 0;
}	

/* crtanje aviona , krajnji izgled aviona cu izmeniti do zavrsetka projekta */
void basicDraw(){
	
	if(!coalision_plane_imp() && plane->in_live){
	
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
	/*ako je prepreka u zivotu i ako nije doslo do kolizije izmedju nje i metka , crtaj prepreku*/
	if(impediments->in_live && !coalsion_bullet_imp() && !coalision_plane_imp()){		
		
			glPushMatrix();
				glColor3f(0,0,1);
				glTranslatef(impediments->x_pos,impediments->y_pos,impediments->z_pos);
				glutSolidCube(impediments->dim);
			glPopMatrix();

			glutPostRedisplay();

		}
	else{
		/* u suprotnom doslo je do kolizije flag=1 oznaacavamo da je doslo do sudara izmedju metka i prepreke
		 , kako bi znali da unistimo i metak jer funkcija coalision nece raditi jer je prepreka unistena */

		int flag = coalsion_bullet_imp();
		if(flag > 0)
			bullets[flag-1]->in_live = 0;
		
		impediments->z_pos = -5;
		impediments->x_pos = random_float(-1,1);
		impediments->dim = random_float(0.02,0.3);
		impediments->brzina = random_float(0.05,0.15);

		glutPostRedisplay(); 
	}
}



