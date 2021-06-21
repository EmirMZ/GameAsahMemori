#include <windows.h>
#include <unistd.h>

void blue_flash(int reaction_time){
	system("color 10");
	Beep(1046.50, reaction_time / 1000);
	usleep(reaction_time);
}

void green_flash(int reaction_time){
	system("color 20");
	Beep(1174.66, reaction_time / 1000);
	usleep(reaction_time);
}

void aqua_flash(int reaction_time){
	system("color 30");
	Beep(1318.51, reaction_time / 1000);
	usleep(reaction_time);
}

void red_flash(int reaction_time){
	system("color 40");
	Beep(1396.91, reaction_time / 1000);
	usleep(reaction_time);
}

void purple_flash(int reaction_time){
	system("color 50");
		Beep(1567.98, reaction_time / 1000);
		usleep(reaction_time);
}
