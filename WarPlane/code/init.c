#include "init.h"
#include "draw.h"
#include "GL/glut.h"
#include "timer.h"
#include "callback.h"
#include "allocation.h"

int init_done = 0;
int imp_active = 0;
int imp2_active = 0;

/*identifikatori broja metkova i tajmera koji ih pokrece*/
int timer_active = 0;
int revive_active = 0;
int end_animation =0;

float z_c = -0.8;
int start_active = 0;

int level = 0;
int level_pom;

int score = 0;
int number = 0;
int life = 3;

Bullet* bullets[5];
Impediment* impediments[2];
Plane* plane = NULL;
Impediment2* impediments2 = NULL;

//inicijalizacija objekata , igre 

void initGame(){
	
	int i;
	
	/*inicijalizacija prepreka u nekoj slucajnoj odabranoj tacki */
	
	for(i=0;i<2;i++){
		impediments[i] = NULL;
		impediments[i] = newImpediment( random_float(-0.9,0.9) , 0 , -5, random_float(0.04,0.27) , 0,random_float(0.05,0.15));
	}
	
	/*avion na njegovu pocetnu poziciju*/
	plane = newPlane( 0 , 0 , 1 , 0 , 1);

	/*inicijalizujemo metak samo , cije cemo kordinate zadati kad ispalimo metak*/
	
	for(i=0;i<5;i++){
		bullets[i] = NULL;
		bullets[i] = newBullet(0,0,0,0);
	}
	impediments2 = newImpediment2(random_float(-0.9,0.9) , 0 , -5, random_float(0.05,0.25) ,0,random_float(0.05,0.15),2);

	init_done = 1;

}


/*nakon inicijalizacije pokrecemo tajmere*/
void startGame(){

	initGame();
	startTimers();
	
}
