#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#include<string.h>

#include "init.h"
#include "GL/glut.h"
#include "draw.h"
#include "timer.h"
#include "callback.h"


/*funkcija koja iscrtava sve objekte , sva iscrtavanja u programu se nalaze ovde*/
void drawAll(){

	/*ako je inicijalizacija zavrsena i ako imamo bar 1 zivot crtamo scene*/
	if(init_done && life>0 ){
		/*deo za iscrtavanja pocetnog stringa*/
		if(!start_active)	
			draw_start();
		
		z_c = -0.8;
		/*Nakon unistavanja odredjenih prepreka dodajemo level(ubrzavamo igru)*/
		if(number == 25 ){
			level = 1;	
			level_up=1;
		}
		if(number==50){
			level = 2;
			level_up=1;
		}
		if(number == 75){
			level = 3;
			level_up=1;
		}

		if(level_up)
			draw_level_up();

		level_pom = 10*level;
		/*crtanje aviona*/
		basicDraw();	
		/*crtanje prepreka*/
		if(imp_active)
			draw_imp();	
		/*nakon ovog skora dodajemo tezu prepreku */
		if(score>1000){	
			impediments2->in_live = 1;
			draw_imp2();
			if(!imp2_active){
				imp2_active = 1;
				glutTimerFunc(TIMER_INTERVAL3-level_pom,moveImpediments2,TIMER_ID);	
			}
		}
		/*iscrtavamo metkove i indikacuju u igri*/
		fire();	
		draw_bullets_bar();
		draw_score_bar();
		draw_life_bar();

		//printf("%d,%d,%d,level %d,number %d\n",score,number,life,level,number);
	}
	else{
		/*ako imamo 0 zivota ulazimo u zavrsni deo za kraj igre*/
		draw_end();

	}



}
/*Odredjujemo koliziju izmedju prepreke i aviona kad im se poklopi opseg x-ose njihove sirine 
i kad im se prednja strana poklopi po z osi*/

int  coalision_plane_imp(int index){
	
	if( ((((impediments[index]->x_pos + impediments[index]->dim/2) - (plane->x_pos-0.125)) > 0 &&
		((impediments[index]->x_pos + impediments[index]->dim/2) - (plane->x_pos-0.125)) < (impediments[index]->dim + 0.25))
										|| 
		(((plane->x_pos+0.125)-(impediments[index]->x_pos - impediments[index]->dim/2)) > 0 &&
		((plane->x_pos+0.125)-(impediments[index]->x_pos - impediments[index]->dim/2))< (impediments[index]->dim + 0.25))) 
						&& 
	    plane->y_pos == impediments[index]->y_pos 
						&& 
	 	((impediments[index]->z_pos-impediments[index]->dim/2) >= 0.875 && 
		  (impediments[index]->z_pos+impediments[index]->dim/2) <= 1.225))		
	
		return 1;
	
	else 
		return 0;
}
/*kolizija metka i prepreke, vraca indeks metka koji se sudario sa preprekom*/
int coalsion_bullet_imp(int index){

	int i;

	for(i=0;i<=4;i++){
		if(((((impediments[index]->x_pos + impediments[index]->dim/2) - (bullets[i]->x_pos-0.01)) > 0 &&
		((impediments[index]->x_pos + impediments[index]->dim/2) - (bullets[i]->x_pos-0.01)) < (impediments[index]->dim + 0.02))
											|| 
		(((bullets[i]->x_pos+0.01)-(impediments[index]->x_pos - impediments[index]->dim/2)) > 0 &&
		((bullets[i]->x_pos+0.01)-(impediments[index]->x_pos - impediments[index]->dim/2))< (impediments[index]->dim + 0.02))) 
							&& 
		bullets[i]->y_pos == impediments[index]->y_pos 
							&& 
		((impediments[index]->z_pos+impediments[index]->dim/2) >= (bullets[i]->z_pos ) &&
		((impediments[index]->z_pos-impediments[index]->dim/2) < (bullets[i]->z_pos + 0.2 )))
							&& 
		bullets[i]->in_live == 1)	
			
			return (i+1);
	}

	return 0;
}	
/*kolizija aviona i druge prepreke*/
int  coalision_plane_imp2(){
	
	if( ((((impediments2->x_pos + impediments2->dim/2) - (plane->x_pos-0.125)) > 0 &&
		((impediments2->x_pos + impediments2->dim/2) - (plane->x_pos-0.125)) < (impediments2->dim + 0.25))
										|| 
		(((plane->x_pos+0.125)-(impediments2->x_pos - impediments2->dim/2)) > 0 &&
		((plane->x_pos+0.125)-(impediments2->x_pos - impediments2->dim/2))< (impediments2->dim + 0.25))) 
						&& 
	    plane->y_pos == impediments2->y_pos 
						&& 
	 	((impediments2->z_pos-impediments2->dim/2) >= 0.875 && 
		  (impediments2->z_pos+impediments2->dim/2) <= 1.225)
		  && impediments2->in_live)		
	
		return 1;
	
	else 
		return 0;
}

/*kolizija metka i druge prepreke*/
int coalsion_bullet_imp2(){
	int i;

	for(i=0;i<=4;i++){
		if(((((impediments2->x_pos + impediments2->dim/2) - (bullets[i]->x_pos-0.01)) > 0 &&
		((impediments2->x_pos + impediments2->dim/2) - (bullets[i]->x_pos-0.01)) < (impediments2->dim + 0.02))
											|| 
		(((bullets[i]->x_pos+0.01)-(impediments2->x_pos - impediments2->dim/2)) > 0 &&
		((bullets[i]->x_pos+0.01)-(impediments2->x_pos - impediments2->dim/2))< (impediments2->dim + 0.02))) 
							&& 
		bullets[i]->y_pos == impediments2->y_pos 
							&& 
		((impediments2->z_pos+impediments2->dim/2) >= (bullets[i]->z_pos ) &&
		((impediments2->z_pos-impediments2->dim/2) < (bullets[i]->z_pos + 0.2 )))
							&& 
		bullets[i]->in_live == 1)	
			
			return (i+1);
	}

	return 0;
}	

/* crtanje aviona  */
void basicDraw(){
	
	/*boja trupa*/
    GLfloat ambient_coeffs[] = { 0,0.4,0, 1 };

    GLfloat diffuse_coeffs[] = { 0.1,0.5,0.1, 1 };

    GLfloat specular_coeffs[] = { 0.1,1,0.1,1};

    GLfloat shininess = 0;

	/*boja krila*/
	GLfloat ambient_coeffs1[] = { 0.01,0.06,0.01, 1 };

    GLfloat diffuse_coeffs1[] = { 0.01,0.08,0.01, 1 };

    GLfloat specular_coeffs1[] = { 0.03,0.03,0.03,1};

    GLfloat shininess1 = 0;
	
	/*ostalo boja*/
    GLfloat ambient_coeffs2[] = { 0, 0, 0, 1 };

    GLfloat diffuse_coeffs2[] = { 0.01, 0.01, 0.01, 1 };

    GLfloat specular_coeffs2[] = {0.03 , 0.03 ,0.03 , 1 };

    GLfloat shininess2 = 2;

	/*otsecanje za staklo*/
	double clip_plane[] = {0,0,1,0.125};
	/*otsecanje za krila*/
	double clip_plane1[] = {-1,-1,0,0.11};
	double clip_plane2[] = {1,-1,0,0.11};

	/*ako nije doslo do kolizije aviona sa nekom od prepreka iscrtavamo ga*/
	if(!coalision_plane_imp(1) && !coalision_plane_imp(0) && !coalision_plane_imp2() && plane->in_live){
	
		glPushMatrix();
			/*pozicioniramo se u kordinate sredista aviona i rotiramo avion*/
			
			glEnable(GL_LIGHTING);
			glTranslatef(plane->x_pos,plane->y_pos,plane->z_pos);

			glRotatef(sin(plane->z_rotate)*15,0,0,1);

			/*Trup aviona*/
			glPushMatrix();
				glEnable(GL_SMOOTH);
				/* Postavljaju se svojstva materijala */
				glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
				glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
				glMaterialf(GL_FRONT, GL_SHININESS, shininess);

				glScalef(0.3, 0.2, 1);
				glutSolidCube(0.25);
			glPopMatrix();

			/*Staklo aviona*/
			glEnable(GL_CLIP_PLANE0);
			glEnable(GL_CLIP_PLANE1);
			glEnable(GL_CLIP_PLANE2);
			
			glPushMatrix();

				glClipPlane(GL_CLIP_PLANE0,clip_plane);
				glEnable(GL_SMOOTH);
				/* Postavljaju se svojstva materijala */
				glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs2);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs2);
				glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs2);
				glMaterialf(GL_FRONT, GL_SHININESS, shininess2);

				glTranslatef(0,0.022,-0.02);
				glRotatef(-190,1,0,0);		
				glScalef(0.2,0.2,1.1);
				glutSolidCone(0.15,0.8,40,40);

			glPopMatrix();
			glDisable(GL_CLIP_PLANE0);

			/*krila aviona*/
			glClipPlane(GL_CLIP_PLANE1,clip_plane1);
			glClipPlane(GL_CLIP_PLANE2,clip_plane2);			
			glPushMatrix();
				glEnable(GL_SMOOTH);
				/* Postavljaju se svojstva materijala */
				glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs1);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs1);
				glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs1);
				glMaterialf(GL_FRONT, GL_SHININESS, shininess1);

				glTranslatef(0, -0.01, -0.1);			
				glScalef(1, 0.2, 0.1);
				glutSolidCube(0.25); 
			glPopMatrix();
				
			glPushMatrix();
				glTranslatef(0, -0.01, 0);			
				glScalef(1, 0.2, 0.1);
				glutSolidCube(0.25);
			glPopMatrix();
			glDisable(GL_CLIP_PLANE1);
			glDisable(GL_CLIP_PLANE2);

			/*zadnji deo tela*/
			glPushMatrix();
				glEnable(GL_SMOOTH);
				/* Postavljaju se svojstva materijala */
				glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
				glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
				glMaterialf(GL_FRONT, GL_SHININESS, shininess);

				glTranslatef(0,0,0.13);
				glRotatef(-180,1,0,0);		
				glScalef(0.2,0.2,1.1);
				glutSolidCone(0.28,0.2,40,40);
			glPopMatrix();

			/*zadnji deo okvir*/
			glDisable(GL_LIGHTING);
			glPushMatrix();
				glColor3f(0,0,0);
				glTranslatef(0,0,0.131);
				glRotatef(-180,1,0,0);		
				glScalef(0.2,0.2,1.1);
				glutWireCone(0.28,0.01,25,25);
			glPopMatrix();
			glEnable(GL_LIGHTING);
			
			/*izlaz */
			glPushMatrix();
			glEnable(GL_SMOOTH);
				/* Postavljaju se svojstva materijala */
				glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs2);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs2);
				glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs2);
				glMaterialf(GL_FRONT, GL_SHININESS, shininess2);

				glTranslatef(0,0,0.139);
				glRotatef(-180,1,0,0);		
				glScalef(0.2,0.2,1.1);
				glutSolidCone(0.15,0.1,100,100);
			glPopMatrix();

			glDisable(GL_LIGHTING);
		glPopMatrix();	
	}
	else{
		/*ako dodje do kolizije avion nije u zivotu vise,pokrecemo tajmer za ozivljavanje*/
		plane->in_live =0;
		if(!revive_active){
			revive_active=1;
			glutTimerFunc(700,Revive,TIMER_ID);
		}
	}


	glutPostRedisplay();
}
/* crtanje metkova , na osnovu kordinata koje joj prosledjujemo*/
void fire(){
	int i;
	/* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs[] = { 0.6, 0.1, 0.1, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs[] = { 1, 0, 0, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };

    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 60;

	/*prolazimo kroz sve metkove ako su zivi iscrtavamo ih*/
	for(i=0;i<5;i++){
		if(bullets[i]->in_live){
			glEnable(GL_LIGHTING);
			glPushMatrix();
				glEnable(GL_SMOOTH);
				/* Postavljaju se svojstva materijala */
				glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
				glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
				glMaterialf(GL_FRONT, GL_SHININESS, shininess);
								
				glTranslatef(bullets[i]->x_pos, bullets[i]->y_pos, bullets[i]->z_pos);
				glutSolidSphere(0.02,50,20);
			glPopMatrix();
			glDisable(GL_LIGHTING);

			glutPostRedisplay();
		}
	}
}
/*crtanje prepreka u kordinatama koje joj prosledimo*/
void draw_imp(){
	int i;
	/* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs[] = { 0.1, 0.1, 0.7, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs[] = { 0,0,1,1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };

    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 30;


	for(i=0;i<2;i++){
		/*ako je prepreka u zivotu i ako nije doslo do kolizije izmedju nje i metka , crtaj prepreku*/
		if(impediments[i]->in_live && !coalsion_bullet_imp(i) && !coalision_plane_imp(i)){		
				glEnable(GL_LIGHTING);
				glPushMatrix();
			
					glEnable(GL_SMOOTH);
					/* Postavljaju se svojstva materijala */
					glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
					glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
					glMaterialf(GL_FRONT, GL_SHININESS, shininess);
			
					glTranslatef(impediments[i]->x_pos,impediments[i]->y_pos,impediments[i]->z_pos);
					glutSolidCube(impediments[i]->dim);
				glPopMatrix();
				glDisable(GL_LIGHTING);
				glutPostRedisplay();

			}
		else{
			/*u suprotnom doslo je do kolizije , vidimo koji indeks nam vraca funkcija i gasimo taj metak 
			dok prepreku postavljamo na pocetnu poziciju , po random vrednostima,uvecavamo number broj unistenih prepreka*/
			int flag = coalsion_bullet_imp(i);
			if(flag > 0)
				bullets[flag-1]->in_live = 0;
			
			impediments[i]->z_pos = -5;
			impediments[i]->x_pos = random_float(-0.9,0.9);
			impediments[i]->dim = random_float(0.04,0.27);
			impediments[i]->brzina = random_float(0.05,0.15);
			score = score + (int)(300*impediments[i]->dim);
			number++;

			glutPostRedisplay(); 
		}
	}
}
void draw_imp2(){

		/* Koeficijenti ambijentalne refleksije materijala. */
		GLfloat ambient_coeffs[] = { 0.7, 0.7, 0.1, 1 };

		/* Koeficijenti difuzne refleksije materijala. */
		GLfloat diffuse_coeffs[] = { 1, 1, 0, 1 };

		/* Koeficijenti spekularne refleksije materijala. */
		GLfloat specular_coeffs[] = { 1, 1, 1, 1 };

		/* Koeficijent glatkosti materijala. */
		GLfloat shininess = 30;


		/*provera za snazniju prepreku ,slicno ko prethodne prepreke*/
		if(impediments2->in_live && !coalsion_bullet_imp2() && !coalision_plane_imp2()){		
			
				glEnable(GL_LIGHTING);
				glPushMatrix();
			
					glEnable(GL_SMOOTH);
					/* Postavljaju se svojstva materijala */
					glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
					glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
					glMaterialf(GL_FRONT, GL_SHININESS, shininess);

					glTranslatef(impediments2->x_pos,impediments2->y_pos,impediments2->z_pos);
					glutSolidCube(impediments2->dim);
				glPopMatrix();
				glDisable(GL_LIGHTING);

				glutPostRedisplay();

			}
		else{
			
			int flag = coalsion_bullet_imp2();
			if(flag > 0)
				bullets[flag-1]->in_live = 0;
			
			if(impediments2->health-1 == 0){
				impediments2->z_pos = -5;
				impediments2->x_pos = random_float(-0.9,0.9);
				impediments2->dim = random_float(0.05,0.25);
				impediments2->speed = random_float(0.05,0.15);
				impediments2->health = 2;
				score = score + (int)(500*impediments2->dim);
				number++;
			}
			impediments2->health--;

			glutPostRedisplay(); 
		}
}
/*Crtanje koliko metkova nam je ostalo , imamo otsecanje u jednom pravcu.POmeramo otsecanje u zavisnosi koliko metkova imamo
na raspolaganju*/
void draw_bullets_bar(){
	double clip_plane[] = {-1,0,0,0.125};

	int b=0;
	int i;
	float boja;
	for(i=0;i<5;i++){
		if(bullets[i]->in_live==1)
			b++;
	}
	/*menjamo boju kako imamo sto manje metkova*/
	boja = (5-b)*0.2;
	clip_plane[3] = (0.125 - b*0.05); 
	
	/*iscrtavanje*/
	glPushMatrix();
	    glEnable(GL_LINE_SMOOTH);

		glTranslatef(-0.97,0.77,0.5);
		glRotatef(-40,1,0,0);

		glEnable(GL_CLIP_PLANE0);
		glPushMatrix();
			glClipPlane(GL_CLIP_PLANE0,clip_plane);
			glColor3f(0,boja,0);
			glBegin(GL_POLYGON);
				glVertex3f(-0.120,0.045,-0.0001);
				glVertex3f(0.120,0.045,-0.0001);
				glVertex3f(0.120,-0.045,-0.0001);
				glVertex3f(-0.120,-0.045,-0.0001);
			glEnd();
		glPopMatrix();
		glDisable(GL_CLIP_PLANE0);

		glColor3f(1,0,0);
		glLineWidth(3);

		glBegin(GL_LINE_LOOP);
			glVertex3f(-0.125,0.05,0);
			glVertex3f(0.125,0.05,0);
			glVertex3f(0.125,-0.05,0);
			glVertex3f(-0.125,-0.05,0);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(-0.075,0.05,0);
			glVertex3f(-0.075,-0.05,0);
			glVertex3f(-0.025,0.05,0);
			glVertex3f(-0.025,-0.05,0);
			glVertex3f( 0.025,0.05,0);
			glVertex3f( 0.025,-0.05,0);
			glVertex3f( 0.075,0.05,0);
			glVertex3f( 0.075,-0.05,0);
		glEnd();
		
	glPopMatrix();
	glDisable(GL_LINE_SMOOTH);
}
/*iscrtavanje dela za skor*/
void draw_score_bar(){
    char text1[6] = "SCORE";
	text1[5]='\0';

	char text2[5];
    sprintf(text2,"%d%d%d%d%d",(score/10000)%10,(score/1000)%10,(score/100)%10,(score/10)%10,score%10);
    text2[6]='\0';

	glEnable(GL_LINE_SMOOTH);
    glLineWidth(4.0);
    
    glPushMatrix();
		glTranslatef(0.65,0.757,0.5);
		glRotatef(-20,1,0,0);
      	glScalef(0.0005,0.0005,0.001);
      	glColor3f(1,0,0);
      	/*prolazimo kroz ceo tekst , kad dodje do terminalne nule izlazi iz petlje*/
		for(char *c=text1;*c;c++)
    	glutStrokeCharacter(GLUT_STROKE_ROMAN,*c);
    glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0.87,0.76,0.51);
		glRotatef(-20,1,0,0);
      	glScalef(0.0005,0.0004,0.001);
      	glColor3f(1,0,0);
      	for(char *c=text2;*c;c++)
    	glutStrokeCharacter(GLUT_STROKE_ROMAN,*c);
    glPopMatrix();

    glDisable(GL_LINE_SMOOTH);

}
/*graficki iscrtavanje zivota */
void draw_life_bar(){

	int i;

	int pom[]={1,1,1};

	
	if(life == 2)
		pom[0] = 0;
	else if(life == 1){
		pom[0] = 0;
		pom[1] = 0;
	}
	else{
	}
	
	glColor3f(1,0,0);

	glPushMatrix();
		glTranslatef(-0.1,0,0);	
		glPushMatrix();
			glTranslatef(-0.2,0.9,-0.7);
			glRotatef(110,1,0,0);

			if(pom[2] == 1)
				glColor3f(1,0,0);
			else
				glColor3f(0,0,0);	

			glPushMatrix();
				glScalef(0.1,1,0.1);
				glBegin(GL_POLYGON);
					for(i=0;i<=50;i++)
					{
						glVertex3f(0.5*cos(i*2*PI/50),0,0.5*sin(i*2*PI/50));
					}	
				glEnd();
			glPopMatrix();

			glPushMatrix();

				glTranslatef(0.1,0,0);
				glScalef(0.1,1,0.1);
				glBegin(GL_POLYGON);
					for(i=0;i<=50;i++)
					{
						glVertex3f(0.5*cos(i*2*PI/50),0,0.5*sin(i*2*PI/50));
					}	
				glEnd();
			glPopMatrix();
		
			glRotatef(-110,1,0,0);

			glPushMatrix();
				glBegin(GL_POLYGON);
					glVertex3f(-0.05,-0.019,0);
					glVertex3f( 0.15,-0.019,0);
					glVertex3f( 0.05,-0.1,0);
				glEnd();
				glBegin(GL_POLYGON);
					glVertex3f(-0.05,0,0);
					glVertex3f( 0.15,0,0);
					glVertex3f( 0.05,-0.02,0);
				glEnd();
				
			glPopMatrix();

		glPopMatrix();

		glPushMatrix();
			glTranslatef(0,0.9,-0.7);
			glRotatef(110,1,0,0);

			if(pom[1] == 1)
				glColor3f(1,0,0);
			else
				glColor3f(0,0,0);	


			glPushMatrix();
				glScalef(0.1,1,0.1);
				glBegin(GL_POLYGON);
					for(i=0;i<=50;i++)
					{
						glVertex3f(0.5*cos(i*2*PI/50),0,0.5*sin(i*2*PI/50));
					}	
				glEnd();
			glPopMatrix();

			glPushMatrix();

				glTranslatef(0.1,0,0);
				glScalef(0.1,1,0.1);
				glBegin(GL_POLYGON);
					for(i=0;i<=50;i++)
					{
						glVertex3f(0.5*cos(i*2*PI/50),0,0.5*sin(i*2*PI/50));
					}	
				glEnd();
			glPopMatrix();
		
			glRotatef(-110,1,0,0);

			glPushMatrix();
				glBegin(GL_POLYGON);
					glVertex3f(-0.05,-0.019,0);
					glVertex3f( 0.15,-0.019,0);
					glVertex3f( 0.05,-0.1,0);
				glEnd();
				glBegin(GL_POLYGON);
					glVertex3f(-0.05,0,0);
					glVertex3f( 0.15,0,0);
					glVertex3f( 0.05,-0.02,0);
				glEnd();
				
			glPopMatrix();

		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.2,0.9,-0.7);
			glRotatef(110,1,0,0);

			if(pom[0] == 1)
				glColor3f(1,0,0);
			else
				glColor3f(0,0,0);	


			glPushMatrix();
				glScalef(0.1,1,0.1);
				glBegin(GL_POLYGON);
					for(i=0;i<=50;i++)
					{
						glVertex3f(0.5*cos(i*2*PI/50),0,0.5*sin(i*2*PI/50));
					}	
				glEnd();
			glPopMatrix();

			glPushMatrix();

				glTranslatef(0.1,0,0);
				glScalef(0.1,1,0.1);
				glBegin(GL_POLYGON);
					for(i=0;i<=50;i++)
					{
						glVertex3f(0.5*cos(i*2*PI/50),0,0.5*sin(i*2*PI/50));
					}	
				glEnd();
			glPopMatrix();
		
			glRotatef(-110,1,0,0);

			glPushMatrix();
				glBegin(GL_POLYGON);
					glVertex3f(-0.05,-0.019,0);
					glVertex3f( 0.15,-0.019,0);
					glVertex3f( 0.05,-0.1,0);
				glEnd();
				glBegin(GL_POLYGON);
					glVertex3f(-0.05,0,0);
					glVertex3f( 0.15,0,0);
					glVertex3f( 0.05,-0.02,0);
				glEnd();
				
			glPopMatrix();

		glPopMatrix();
	glPopMatrix();
}
/*iscrtavanje dela (poligona,prozora kako god) u kome ispisujemo skor i ostale stvari*/
void draw_end(){

	char text1[] = "GAME";
	text1[5]='\0';
	char textO[] = "OVER";
	textO[5] = '\0';


	char text2[] = "SCORE";
	text2[5] = '\0';

	char text3[6] ;

	sprintf(text3,"%d%d%d%d%d",(score/10000)%10,(score/1000)%10,(score/100)%10,(score/10)%10,score%10);
	text3[5] ='\0';

	char text4[] = ">>Press r for new game<<";
	text4[24] = '\0';

	if(!end_animation){
		end_animation = 1;
		glutTimerFunc(TIMER_END,end_timer,TIMER_ID);
	}

	glPushMatrix();
		
		glTranslatef(0,0,z_c);

		glPushMatrix();
			glColor3f(0,0,0);
			glRotatef(-20,1,0,0);
			glBegin(GL_POLYGON);
				glVertex3f(-1,0.6,-0.0001);
				glVertex3f(1,0.6,-0.0001);
				glVertex3f(1,-0.6,-0.0001);
				glVertex3f(-1,-0.6,-0.0001);
			glEnd();
		glPopMatrix();

		glPushMatrix();
			glLineWidth(10);
			glRotatef(-20,1,0,0);
			glTranslatef(-0.75,0.2,0);
			
			glScalef(0.002,0.002,0.001);

			glColor3f(1,0,0);
			for(char *c=text1;*c;c++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN,*c);

		glPopMatrix();

		glPushMatrix();
			glLineWidth(10);
			glRotatef(-20,1,0,0);
			glTranslatef(0.05,0.2,0);
			
			glScalef(0.002,0.002,0.001);

			glColor3f(1,0,0);
			for(char *c=textO;*c;c++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN,*c);

		glPopMatrix();

		glPushMatrix();
			glLineWidth(3);
			glRotatef(-20,1,0,0);
			glTranslatef(-0.5,-0.1,0);
			
			glScalef(0.001,0.001,0.001);
			glColor3f(1,0,0);
			for(char *c=text2;*c;c++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN,*c);
		glPopMatrix();

		glPushMatrix();
			glLineWidth(3);
			glRotatef(-20,1,0,0);
			glTranslatef(0,-0.1,0);
			
			glScalef(0.001,0.001,0.001);
			glColor3f(1,0,0);
			for(char *c=text3;*c;c++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN,*c);
		glPopMatrix();

		glPushMatrix();
			glLineWidth(2);
			glRotatef(-20,1,0,0);
			glTranslatef(-0.5,-0.3,0);
			
			glScalef(0.0005,0.0005,0.001);
			glColor3f(0,0.6,0);
			for(char *c=text4;*c;c++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN,*c);
		glPopMatrix();


	glPopMatrix();
}
/*tekst za ispis na sstartu za pokretanje igre*/
void draw_start(){

	char text[] = "Press left click to start";
	
	text[25]='\0';

	glPushMatrix();
		glLineWidth(2);
		glColor3f(1,0,0);
		glRotatef(-20,1,0,0);

		glTranslatef(-0.4,0.1,0.2);
		glScalef(0.0005,0.0005,0.001);
		for(char *c=text;*c;c++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*c);
		

	glPopMatrix();

}
/*Deo za iscrtavanja teksta level up*/
void draw_level_up(){

	char text[] = {"LEVEL UP!"};

	text[9]='\0';


	glPushMatrix();
		glLineWidth(3);
		glColor3f(0,1,0);
		glRotatef(-20,1,0,0);

		glTranslatef(1.05,0.68,0.2);
		glScalef(0.0005,0.0005,0.001);
		for(char *c=text;*c;c++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*c);
		
	glPopMatrix();

	glutTimerFunc(2000,timer_up,TIMER_ID);
}
