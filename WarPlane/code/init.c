#include "init.h"
#include "draw.h"
#include "GL/glut.h"
#include "timer.h"
#include "callback.h"
#include "allocation.h"

int init_done = 0;
int imp_active = 0;

/*identifikatori broja metkova i tajmera koji ih pokrece*/
int timer_active = 0;

Bullet* bullets[5];
Plane* plane = NULL;
Impediment* impediments = NULL;

//inicijalizacija objekata , igre 

void initGame(){
	/*inicijalizacija prepreka u nekoj slucajnoj odabranoj tacki */
	impediments = newImpediment( random_float(-1,1) , 0 , -5, random_float(0.05,0.3) , 0,random_float(0.05,0.15));
	/*avion na njegovu pocetnu poziciju*/
	plane = newPlane( 0 , 0 , 1 , 0 , 1);

	/*inicijalizujemo metak samo , cije cemo kordinate zadati kad ispalimo metak*/
	int i;
	for(i=0;i<5;i++){
		bullets[i] = NULL;
		bullets[i] = newBullet(0,0,0,0);
	}
	init_done = 1;

}


/*nakon inicijalizacije pokrecemo tajmere*/
void startGame(){

	initGame();
	startTimers();
	
}
