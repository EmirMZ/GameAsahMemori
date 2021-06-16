#include <stdio.h>
#include <strings.h>
#include <windows.h>
#include "menu.h"
#include "enableVT.c"

int main(){
	enableVT();
	menu();
}
