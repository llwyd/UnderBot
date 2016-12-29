uBot: underBot.o
	gcc -std=gnu11 underBot.o -o uBot -lX11 -lXtst -lpthread
underBot.o: underBot.c
	gcc -std=gnu11 -c underBot.c -o underBot.o -lX11 -lXtst -lpthread
clean:
	rm uBot underBot.o
