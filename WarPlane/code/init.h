#ifndef _INIT_H_
#define _INIT_H_
#include "objects.h"

	extern int init_done;
	extern Plane* plane;
	extern Bullet* bullets;
	extern Impediment* impediments;


	void initGame();
	void startGame();
	
	extern int fire_active;
	extern int imp_active;

	


#endif
