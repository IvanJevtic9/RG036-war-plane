#include "init.h"
#include "GL/glut.h"
#include<math.h>
#include "draw.h"
#include "timer.h"
#include <stdlib.h>

/*funkcija koja iscrtava sve objekte , sva iscrtavanja u programu se nalaze ovde*/
void drawAll(){

	if(init_done){
		basicDraw();	
		
		if(fire_active)
				fire();	

		if(imp_active)
				draw_imp();		
	}

}

/* crtanje aviona , krajnji izgled aviona cu izmeniti do zavrsetka projekta */
void basicDraw(){
	
	glColor3f(plane->red, plane->green, plane->blue);
	glPushMatrix();
		/*pozicioniramo se u kordinate sredista aviona i rotiramo avion*/
		glTranslatef(plane->x_pos,plane->y_pos,plane->z_pos);
		glRotatef(sin(plane->z_rotate)*30,0,0,1);

		/*telo aviona*/
		glPushMatrix();
			glTranslatef(0, 0, 1);
			glScalef(0.3, 0.3, 1);
			glutWireCube(0.25);
		glPopMatrix();
		/*krila aviona*/	
		glPushMatrix();
			glTranslatef(0, 0.0375, 0.9);			
			glScalef(1, 0.2, 0.1);
			glutWireCube(0.25);
		glPopMatrix();
			
		glPushMatrix();
			glTranslatef(0, 0.0375, 1);			
			glScalef(1, 0.2, 0.1);
			glutWireCube(0.25);
		glPopMatrix();

	glPopMatrix();

	glutPostRedisplay();
}
/* crtanje metkova , na osnovu kordinata koje joj prosledjujemo*/
void fire(){
	if(bullets->in_live){

		


		glPushMatrix();
					glColor3f(1,0,0);
					glTranslatef(plane->x_pos, plane->y_pos, bullets->z_pos);
					glutSolidSphere(0.02,50,20);
		glPopMatrix();


		glutPostRedisplay();
			

	}

}
/*crtanje prepreka u kordinatama koje joj prosledimo*/
void draw_imp(){

	if(impediments->in_live){		
		
			glPushMatrix();
					glColor3f(0,0,1);
					glTranslatef(impediments->x_pos,impediments->y_pos,impediments->z_pos);
					glutSolidCube(impediments->dim);
			glPopMatrix();


	
			glutPostRedisplay();

		}
}



