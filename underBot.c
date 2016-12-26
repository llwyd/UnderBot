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
#include <string.h>
#include <unistd.h>

int main(void){
	printf("Undertale Genocide Bot Active!\n");
	Display *d=XOpenDisplay(0);
//	Window r=XDefaultRootWindow(d);
//	Window r=0;
	Window * w;
	Window rr;
	Window pr;
	int nc;
	int error;
//	error=XQueryTree(d,r,&rr,&pr,&w,&nc);
//	printf("QueryTree stats=%d\n",error);
//	printf("Number of windows=%d\n",nc);
//	char* name;
	XTextProperty t;
	int k=0;
	int test=0;
	int flag=0;
	int keyflag=0;
	char ckey=0;
	XEvent e;
	while(1){	
	Window c;
	XGetInputFocus(d,&c,&k);
	error=XGetWMName(d,c,&t);
	//memcpy(cp,t.value,9);
	//test=strcmp(meow,t.value);
	//printf("Test=%d\n",test);
	if((error!=0)){
		//test=strcmp("UNDERTALE",t.value);
		test=strcmp("Steam",t.value);
		if((test==0)&&(flag==0)){
			printf("%s\n",t.value);
			flag=1;
			XSelectInput(d,c,KeyPressMask |KeyReleaseMask);
		}
		else if((test!=0)&&(flag==1)){
			flag=0;
			printf("Window No Longer in Focus\n");
		}
		else if((test==0)&&(flag==1)){
		//	printf(".");
		//window active loop;
			while(XPending(d)){
			XNextEvent(d,&e);
			}
			//if((e.type==KeyPress)&&(e.xkey.keycode!=ckey)){
			if((e.type==KeyPress)&&(e.xkey.keycode==9)){
				//printf(".");
				//ckey=e.xkey.keycode;
				//printf("Key=%x,",e.xkey.keycode);
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
	error=XQueryTree(d,c,&rr,&pr,&w,&nc);
//	printf("Number of windows=%d\n",nc);
	}
/*
	for(int i=0;i<nc;i++){
		//XGetInputFocus(d,&w[nc-1],&k);
		//printf("k=%d\n",k);
		error=XGetWMName(d,w[nc-1],&t);
		if(error!=0){
		//	printf("%s\n",t.value);
		}
	}
	//int success=XFetchName(d,w[1],&name);
	//printf("Success=%d\n",error);
	//printf("%s\n",t.value);
	XFree(w);*/
	return 0;
}
