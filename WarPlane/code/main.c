#include<GL/glut.h>
#include "callback.h"
#include "init.h"

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

	glClearColor(0.5,0.5,0.5,0);
	glEnable(GL_DEPTH_TEST);

	startGame();  

	glutMainLoop();

	return 0;
}
