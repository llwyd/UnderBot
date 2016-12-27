/*

underBot.c

T.Lloyd 2016

Grinding tool for Undertale's Genocide path

*/
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include <string.h>
#include <unistd.h>

int main(void){
	printf("Undertale Genocide Bot!\n");
	printf("T.Lloyd 2016\n");
	Display *d=XOpenDisplay(0);

	Window * w;
	Window rr;
	Window pr;
	int nc;
	int error;

	XTextProperty t;
	int k=0;
	int test=0;
	int flag=0;
	int keyflag=0;
	char ckey=0;
	KeyCode keyc;
	XEvent e;
	while(1){	
		Window c;
		XGetInputFocus(d,&c,&k);
		error=XGetWMName(d,c,&t);
		int keycount=0;
		int prevkey=1;
		useconds_t delay =10000;
		if((error!=0)){
			test=strcmp("UNDERTALE",t.value);
			if((test==0)&&(flag==0)){
				printf("%s\n",t.value);
				flag=1;
				XSelectInput(d,c,KeyPressMask |KeyReleaseMask);
			}
			else if((test!=0)&&(flag==1)){
				flag=0;
				keyflag=0;
				printf("Window No Longer in Focus\n");
			}
			else if((test==0)&&(flag==1)){
			//window active loop;
				if(keyflag==1){
					keycount=1;
					XTestFakeKeyEvent(d,113,True,0);
					XFlush(d);
					usleep(delay);
					XTestFakeKeyEvent(d,113,False,0);
					XFlush(d);
					usleep(delay);
					
					XTestFakeKeyEvent(d,114,True,0);
					XFlush(d);
					usleep(delay);
					XTestFakeKeyEvent(d,114,False,0);
					XFlush(d);
					usleep(delay);
					keycount=0;
					
				}
				while(XPending(d)){
				XNextEvent(d,&e);
				}

			//	printf("Key=%x,",e.xkey.keycode);
				//if((e.type==KeyPress)&&(e.xkey.keycode!=ckey)){
				if((e.type==KeyPress)&&(e.xkey.keycode==74)){
					if(keyflag==0){
						printf("UnderBot Active!\n");
						keyflag=1;
					}
					else{
						printf("UnderBot InActive!\n");
						keyflag=0;
					}
					usleep(((100*100)/2)*10*8);
				}
			}
		}
		else{
			//flag=0;
		}
	}
	return 0;
}
