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

void menuMain (int selected,int menu_select, int menu_total_string,char menu [9][5][64]){
	int i;
	char coloringtext[5][12] ={"\033[1;7;34m","\033[1;7;32m","\033[1;7;36m","\033[1;7;31m","\033[1;7;45m"};
	char resetcolor[8]= {"\033[0m"};
	
	if(menu_select == 0||menu_select == 1){
		for(i = 0; i < menu_total_string; i++){
		if (selected == i)
		{
			red();
		}
		printf("%s\n", menu[menu_select][i]);
		reset();
	}
		
	}else if(menu_select == 2){
		for (i = 0; i < menu_total_string; i++){
		
		printf("%s%s%s",coloringtext[i], menu[menu_select][i],resetcolor);
		if (selected == i)
		{
			printf(" <<");
		}
		
			printf("\n");
			reset();
		}
	}

	
}


int menu(int menu_select){//menu apa yang ingin ditampilkan

    int selection = 0, i = 1, selected_menu = -2;//yang dipilih sekarang, i, yang terpilih menunya
    
    int menu_limit[9];// total baris setiap menu
	
	menu_limit[0] = 4; //limit option main menu
	menu_limit[1] = 4; // limit option game difficulty
	menu_limit[2] = 5; // limit option answer input
	
	char menu [9][5][64];// bracket pertama adalah menu window, bracket kedua adalah menu string, bracket ketiga character limit


	strcpy (menu[0][0], "Play");
	strcpy (menu[0][1], "Help");
	strcpy (menu[0][2], "High Score");
	strcpy (menu[0][3], "Exit");
	
	
	strcpy (menu[1][0], "1. EASY - 1.24s Reaction Time w/ 3 Colors");
	strcpy (menu[1][1], "2. NORMAL - 0.98s Reaction Time w/ 4 Colors");
	strcpy (menu[1][2], "3. HARD - 0.68s Reaction Time w/ 4 Colors");
	strcpy (menu[1][3], "4. INSANE - 0.40s Reaction Time w/ 5 Colors");
	
	strcpy (menu[2][0], "BLUE");
	strcpy (menu[2][1], "GREEN");
	strcpy (menu[2][2], "AQUA");
	strcpy (menu[2][3], "RED");
	strcpy (menu[2][4], "PURPLE");


	while(selected_menu == -2){
		system("cls");
		header();
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
