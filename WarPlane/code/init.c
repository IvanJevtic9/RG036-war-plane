#include "init.h"
#include "draw.h"
#include "GL/glut.h"
#include "timer.h"
#include "callback.h"
#include "allocation.h"

int init_done = 0; //obavljena inicijalizacija
int imp_active = 0; //aktivna obicna prepreka(promenljiva na osnovu koje odredjujem da li je aktivna)
int imp2_active = 0; //aktivna jaca prepreka

int timer_active = 0;

int revive_active = 0;//aktivno ozivljavljanje aviona
int end_animation =0;//deo za kraj igre

float z_c = -0.8;//pozicija prozora za kraj igre
int start_active = 0;

int level = 0;	//trenutni level
int level_pom;	//pomocna za ubrzavanje igre
int level_up=0;

int score = 0; //trenutni skor
int number = 0; //broj unistenih
int life = 3;	//broj zivota



/*Definicija promenljivih*/
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

	/*identifikacija jace prepreke*/
	impediments2 = newImpediment2(random_float(-0.9,0.9) , 0 , -5, random_float(0.05,0.25) ,0,random_float(0.05,0.15),2);

	init_done = 1;//oznacimo da smo zavrsili inicijalizaciju

}


/*nakon inicijalizacije pokrecemo tajmere*/
void startGame(){

	initGame();
	startTimers();
	
}
