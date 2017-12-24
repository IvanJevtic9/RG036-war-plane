#ifndef _OBJECTS_H_
#define _OBJECTS_H_

/*struktura objekata , avion ima 3 atributa za poziciju , boju , rotaciju i da li je avion u zivotu */

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
/*metak ima 3 atributa za poziciju i da li je metak u zivotu*/

struct _Bullet{
	double x_pos;
	double y_pos;
	double z_pos;

	int in_live;
	
};
/*prepreke imaju 3 za poziciju , dimenziju i da li je u zivotu prepreka*/
struct _Impediment{
	double x_pos;
	double y_pos;
	double z_pos;
	
	double dim;
	int in_live ;
};

/*Uvodim skracenice za poziv strukture*/

typedef struct _Plane Plane;
typedef struct _Bullet Bullet;
typedef struct _Impediment Impediment;

void rotatePlane();


#endif
