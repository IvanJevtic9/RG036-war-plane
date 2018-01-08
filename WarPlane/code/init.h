#ifndef _INIT_H_
#define _INIT_H_
#include "objects.h"

	extern int init_done;
	extern Plane* plane;
	extern Bullet* bullets[5];
	extern Impediment* impediments;

	void initGame();
	void startGame();
	
	extern int timer_active;
	extern int imp_active;


#endif
