#ifndef _OBJECTS_H_
#define _OBJECTS_H_

//struktura objekata

struct _Plane{

	double x_pos;
	double y_pos;
	double z_pos;
	
	double red;
	double green;
	double blue;

	double z_rotate;

	int in_live;
	
};
struct _Bullet{
	double x_pos;
	double y_pos;
	double z_pos;

	int in_live;
	
};




typedef struct _Plane Plane;
typedef struct _Bullet Bullet;

void rotatePlane();


#endif
