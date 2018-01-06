#include "init.h"
#include "GL/glut.h"
#include<math.h>
#include "draw.h"
#include "timer.h"
#include <stdlib.h>
#include <stdio.h>
#include "callback.h"

/* posto koliziju za projektil i prepreku ne mozemo da koristimo kod oba objekta , jer ce se prvo unistiti jedan pa tek onaj drugi 
moramo pamtiti da li se prepreka unistila od strane projetkila da bi znali da i metak izbrisemo*/
int flag = 0;

/*funkcija koja iscrtava sve objekte , sva iscrtavanja u programu se nalaze ovde*/
void drawAll(){

	if(init_done){
		basicDraw();	
		
		if(imp_active)
				draw_imp();		
		if(fire_active)
				fire();	
	}

}
/*Odredjujemo koliziju izmedju prepreke i aviona kad im se poklopi opseg x-ose njihove sirine 
i kad im se prednja strana poklopi po z osi*/

int  coalision_plane_imp(){
	
	if( ((((impediments->x_pos + impediments->dim/2) - (plane->x_pos-0.175)) > 0 &&
		((impediments->x_pos + impediments->dim/2) - (plane->x_pos-0.175)) < (impediments->dim + 0.25))
										|| 
		(((plane->x_pos+0.175)-(impediments->x_pos - impediments->dim/2)) > 0 &&
		((plane->x_pos+0.175)-(impediments->x_pos - impediments->dim/2))< (impediments->dim + 0.25))) 
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

	if(((((impediments->x_pos + impediments->dim/2) - (bullets->x_pos-0.01)) > 0 &&
	  ((impediments->x_pos + impediments->dim/2) - (bullets->x_pos-0.01)) < (impediments->dim + 0.02))
										|| 
	  (((bullets->x_pos+0.01)-(impediments->x_pos - impediments->dim/2)) > 0 &&
	  ((bullets->x_pos+0.01)-(impediments->x_pos - impediments->dim/2))< (impediments->dim + 0.02))) 
						&& 
	  bullets->y_pos == impediments->y_pos 
						&& 
	  ((impediments->z_pos+impediments->dim/2) >= (bullets->z_pos ) &&
	  ((impediments->z_pos-impediments->dim/2) < (bullets->z_pos + 0.2 )))
						&& 
	  bullets->in_live == 1)	
		return 1;
	else 
		return 0;


}

/* crtanje aviona , krajnji izgled aviona cu izmeniti do zavrsetka projekta */
void basicDraw(){
	
	if(!coalision_plane_imp() && plane->in_live){
	
	glPushMatrix();
		/*pozicioniramo se u kordinate sredista aviona i rotiramo avion*/
		glTranslatef(plane->x_pos,plane->y_pos,plane->z_pos);
		
		/*Posto jos nisam ukljucio osvetljenje za sad cu mu staviti da bude crn*/
		glColor3f(0,0,0);

		glRotatef(sin(plane->z_rotate)*15,0,0,1);
		
		/*telo aviona*/
		glPushMatrix();
			glScalef(0.3, 0.2, 1);
			glutSolidCube(0.25);
		glPopMatrix();
		/*krila aviona*/	
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
	if(bullets->in_live && plane->in_live && !flag){

		glPushMatrix();
					glColor3f(1,0,0);
					glTranslatef(bullets->x_pos, bullets->y_pos, bullets->z_pos);
					glutSolidSphere(0.02,50,20);
		glPopMatrix();

		glutPostRedisplay();
	}
	else{		/*ako dodje do kolizije metak nije u zivotu vracamo flag na 0 i isklucujemo pucnjavu*/
		flag = 0;
		fire_active = 0;
		bullets->in_live = 0;
		glutPostRedisplay();
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
		iskljuci_timerB = 1;
		flag = 1;
		impediments->z_pos = -5;
		impediments->x_pos = random_float(-1,1);
		impediments->dim = random_float(0.02,0.3);
		impediments->brzina = random_float(0.05,0.15);

		glutPostRedisplay();
	}
}



