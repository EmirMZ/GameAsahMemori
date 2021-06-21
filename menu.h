#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include <omp.h>
#include "banner.h"

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

void menuMain (int selected,int menu_select, int menu_total_string,char menu [9][5][32]){
	int i;
	
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


int menu(int menu_select){
    int selection = 1, i = 1, selected_menu = -2;
    
    int menu_limit[9];
	
	menu_limit[0] = 4; //limit option main menu
	
	char menu [9][5][32];// bracket pertama adalah menu window, bracket kedua adalah menu string, bracket ketiga character limit


	strcpy (menu[0][0], "Play");
	strcpy (menu[0][1], "Help");
	strcpy (menu[0][2], "High Score");
	strcpy (menu[0][3], "Exit");
	
	
	strcpy (menu[1][0], "1. EASY - 1.24s Reaction Time w/ 3 Colors");
	strcpy (menu[1][1], "2. NORMAL - 0.98s Reaction Time w/ 4 Colors");
	strcpy (menu[1][2], "3. HARD - 0.68s Reaction Time w/ 4 Colors");
	strcpy (menu[1][3], "4. INSANE - 0.40s Reaction Time w/ 5 Colors");	
	


	while(selected_menu == -2){
		system("cls");
		menuMain(selection,menu_select,menu_limit[menu_select],menu);

    	switch(getch()){
			case 224: // anon
				switch(getch()){
					case 72: // Up Arrow
						selection --;
						break;
					case 80: // Up Arrow
						selection ++;
						break;
				}
				break;
			case 13:
				selected_menu = selection;
		}
		
		if (selection < 0){
			selection = menu_limit[menu_select]-1;
		}
		else if (selection+1 > menu_limit[menu_select]){
			selection = 0;
		}
	}
	return selected_menu;    
	}
