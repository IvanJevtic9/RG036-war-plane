#ifndef _OBJECTS_H_
#define _OBJECTS_H_

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





typedef struct _Plane Plane;

void rotatePlane();


#endif
