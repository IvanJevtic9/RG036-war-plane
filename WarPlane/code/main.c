#include<GL/glut.h>
#include "callback.h"
#include "init.h"
#include "image.h"

void ucitaj_teksture()
{
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  
  char *file;
  
  file = "pozadina.bmp";

  Image *image = image_init(0, 0);

	glGenTextures(2, texture);

    image_read(image, file);

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
  

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
	ucitaj_teksture();

	glClearColor(0.5,0.5,0.5,0);
	glEnable(GL_DEPTH_TEST);

	startGame();  

	glutMainLoop();

	return 0;
}
