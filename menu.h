#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>

void red () {
  printf("\033[1;7;31m");
}

void green () {
  printf("\033[0;32m");
}

void yellow () {
  printf("\033[0;35m");
}

void reset () {
  printf("\033[0m");
}

void menuMain (int selected,int menu_select, int menu_total_string){
	int i;
	char menu [9][5][32];// bracket pertama adalah menu window, bracket kedua adalah menu string, bracket ketiga character limit

	
	strcpy (menu[0][0], "Play");
	strcpy (menu[0][1], "Help");
	strcpy (menu[0][2], "Score");
	strcpy (menu[0][3], "Exit");
	strcpy (menu[1][0], "Play");
	strcpy (menu[1][1], "Play");
	strcpy (menu[1][2], "Play");
	strcpy (menu[0][3], "Play");
	
	for (i = 0; i < menu_total_string; i++)
	{
		if (selected == i)
		{
			red();
		}
		printf("%s\n", menu[menu_select][i]);
		reset();
	}
}


int menu(){
    int selection = 1, i = 1;
    int menu_select = 0;
    
    
    int menu_limit[9];
	
	menu_limit[0] = 4; //limit option main menu

	while(1){
		system("cls");
		menuMain(selection,menu_select,menu_limit[menu_select]);
		
		if (getch() == 224){ //224 is Escape
    	switch(getch()) {
    		case 72:
    			selection --;
				break;
			case 80:
				selection ++;
				break;
		}
		
		if (selection < 0){
			selection = menu_limit[menu_select]-1;
		}
		else if (selection+1 > menu_limit[menu_select]){
			selection = 0;
		}
		
		
	}    
    

	}
}
