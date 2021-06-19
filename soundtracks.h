#include <windows.h>

void correct_jingle(){
	Beep(1174.66, 90);
	Beep(1760.00, 250);
}

void wrong_jingle(){
	Beep(1760.00, 90);
	Beep(1174.66, 250);
}

void game_over_jingle(){
	Beep(1567.98, 200);
	Beep(1318.51, 200);
	Beep(783.99, 200);
	Beep(987.77, 200);
	Beep(1046.50, 700);
}

void new_high_score_jingle(){
	Beep(1046.50, 200);
	Beep(1567.98, 200);
	Beep(1396.91, 200);
	Beep(1318.51, 200);
	Beep(1396.91, 200);
	Beep(2093.00, 700);
}

void check_jingle(){
	Beep(1567.98, 150);
	Beep(1567.98, 150);
	Beep(1318.51, 150);
	Beep(1396.91, 150);
	Beep(1567.98, 150);
	Beep(1975.53, 150);
	Beep(2093.00, 750);
}
