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
#include <pthread.h>


typedef struct{
	Display *d; //x11 display
	Window c; //Current Window
	int keyflag;//enables/disables loop
	useconds_t delay;
	int count;
}game;

pthread_mutex_t lock;

static void * moveLoop(void *arg){
	game * gw =(game*)arg;
	while(1){
		for(int j=0;j<2;j++){
		if(gw->keyflag==1){
			switch(j){
				case 0:
					if(!pthread_mutex_lock(&lock)){
					XLockDisplay(gw->d);
					XTestFakeKeyEvent(gw->d,113,True,0);
					XFlush(gw->d);
					usleep(gw->delay);
					XTestFakeKeyEvent(gw->d,113,False,0);
					XFlush(gw->d);
					XUnlockDisplay(gw->d);
					pthread_mutex_unlock(&lock);
					usleep(gw->delay);
					}
					break;
				case 1:
					if(!pthread_mutex_lock(&lock)){
					XLockDisplay(gw->d);
					XTestFakeKeyEvent(gw->d,114,True,0);
					XFlush(gw->d);
					usleep(gw->delay);
					XTestFakeKeyEvent(gw->d,114,False,0);
					XFlush(gw->d);
					XUnlockDisplay(gw->d);
					pthread_mutex_unlock(&lock);
					usleep(gw->delay);
					}

				}
		}
	}	
}
}


int main(void){
	printf("Undertale Genocide Bot!\n");
	printf("T.Lloyd 2016\n");
	//Display *d=XOpenDisplay(0);
	XInitThreads();
	game u;
	u.d=XOpenDisplay(0);
	u.keyflag=0;
	u.delay =10000;
	u.count=0;
	useconds_t db=100000;
	int k=0;
	XGetInputFocus(u.d,&u.c,&k);
	int error;
	

	pthread_t thread;
	pthread_mutex_init(&lock,NULL);
	pthread_create(&thread,NULL,moveLoop,&u);

	XTextProperty t;
	int test=0;
	int flag=0;
	int keyflag=0;
	char ckey=0;
	KeyCode keyc;
	XEvent e;
	while(1){	
		//Window c;
		if(!pthread_mutex_trylock(&lock)){
			XLockDisplay(u.d);
			XGetInputFocus(u.d,&u.c,&k);
			error=XGetWMName(u.d,u.c,&t);
			XUnlockDisplay(u.d);
			pthread_mutex_unlock(&lock);
		}
		int prevkey=1;
		//useconds_t delay =10000;
		if((error!=0)){
			test=strcmp("UNDERTALE",t.value);
			if((test==0)&&(flag==0)){
				printf("%s\n",t.value);
				flag=1;
				XSelectInput(u.d,u.c,KeyPressMask |KeyReleaseMask);
			}
			else if((test!=0)&&(flag==1)){
				flag=0;
				u.keyflag=0;
				printf("Window No Longer in Focus\n");
			}
			else if((test==0)&&(flag==1)){
				while(XPending(u.d)){
					if(!pthread_mutex_trylock(&lock)){
						XLockDisplay(u.d);
						XNextEvent(u.d,&e);
						XUnlockDisplay(u.d);
						pthread_mutex_unlock(&lock);
					}
				}
				if((e.type==KeyPress)&&(e.xkey.keycode==74)){
					if(u.keyflag==0){
						printf("UnderBot Active!\n");
						u.keyflag=1;
					}
					else{
						printf("UnderBot InActive!\n");
						u.keyflag=0;
					}
					usleep(db);
				}
			}
		}
		else{
		}
	}
	return 0;
}
