#include<GL/glut.h>
#include "callback.h"
#include "init.h"
#include "image.h"

void load_texture()
{
  	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  
  	char *file[2];
  
  	file[0] = "pozadina.bmp";
	file[1] = "rock.bmp";

 	Image *image = image_init(0, 0);

	glGenTextures(2, texture);
	int i;

	for(i = 0;i<2;i++){
		image_read(image, file[i]);

		glBindTexture(GL_TEXTURE_2D, texture[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
					image->width, image->height, 0,
					GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	}

	image_done(image);
}


int main(int argc,char** argv){
	/*inicijalizujemo sve na pocetku , sandardno sve */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(1240,800);
	glutInitWindowPosition(100,100);
	glutCreateWindow("War Plane");

	glutKeyboardFunc(onKeyboard);

	glutReshapeFunc(onReshape);
	glutDisplayFunc(onDisplay);
	glutMouseFunc(onMouseClick);
	glutPassiveMotionFunc(onMouseMove);

	glutSetCursor(GLUT_CURSOR_NONE);

	glEnable(GL_TEXTURE_2D);
	load_texture();

	glClearColor(0.5,0.5,0.5,0);
	glEnable(GL_DEPTH_TEST);

	startGame();  

	glutMainLoop();

	return 0;
}
