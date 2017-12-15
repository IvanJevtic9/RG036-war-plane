#ifndef _CALLBACK_H_			
#define _CALLBACK_H_			
	

extern int window_width;
extern int window_height;

void onDisplay();
void onKeyboard(unsigned char c , int x, int y);
void onReshape(int w_width, int w_height);
void onMouseClick(int button, int state, int x, int y);
void onMouseMove(int x,int y);

#endif	
