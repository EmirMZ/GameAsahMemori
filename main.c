#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include "menu.h"
#include "game.h"
#include "enableVT.h"

int main(){
	enableVT();
	menu();
	//game();
}
