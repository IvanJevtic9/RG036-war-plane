#include "init.h"
#include "GL/glut.h"
#include<math.h>
#include "draw.h"
#include "timer.h"
#include <stdlib.h>


void drawAll(){

	if(init_done){
		basicDraw();	
			
	}

}


void basicDraw(){
	
	glColor3f(plane->red, plane->green, plane->blue);
	glPushMatrix();
		glTranslatef(plane->x_pos,plane->y_pos,plane->z_pos);
		glRotatef(sin(plane->z_rotate)*30,0,0,1);

		glPushMatrix();
			glTranslatef(0, 0, 1);
			glScalef(0.3, 0.3, 1);
			glutWireCube(0.25);
		glPopMatrix();
			
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







