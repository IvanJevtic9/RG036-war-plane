#ifndef _INIT_H_
#define _INIT_H_
#include "objects.h"

	extern int init_done;
	extern Plane* plane;
	extern Bullet* bullets[5];
	extern Impediment* impediments[2];
	extern Impediment2* impediments2;

	void initGame();
	void startGame();
	
	extern int revive_active;
	extern int score;
	extern int number;
	extern int life;
	extern int timer_active;
	extern int end_animation;
	extern float z_c ;
	extern int start_active;

	extern int imp_active;
	extern int imp2_active;
	extern int level ;
	extern int level_pom;

#endif
