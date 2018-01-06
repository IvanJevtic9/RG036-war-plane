#ifndef _CALLBACK_H_			
#define _CALLBACK_H_			
	
#define TIMER_ID 1
#define TIMER_INTERVAL 100
#define TIMER_INTERVAL2 50

extern int window_width;
extern int window_height;
extern int iskljuci_timerB;


void onDisplay();
void onKeyboard(unsigned char c , int x, int y);
void onReshape(int w_width, int w_height);
void onMouseClick(int button, int state, int x, int y);
void onMouseMove(int x,int y);
float random_float(const float min, const float max);

#endif	
