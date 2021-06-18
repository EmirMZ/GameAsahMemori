#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>

void red () {
  printf("\033[1;31m");
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

void menuMain (int selected){
	int i;
	char menu [9][5][32];
	strcpy (menu[0][0], "Play");
	strcpy (menu[0][1], "Help");
	strcpy (menu[0][2], "Score");
	strcpy (menu[0][3], "Exit");
	strcpy (menu[1][0], "Play");
	strcpy (menu[1][0], "Play");
	strcpy (menu[1][0], "Play");
	strcpy (menu[0][0], "Play");
	
	for (i = 0; i < 5; i++)
	{
		if (selected == i)
		{
			red();
			printf("%s\n", menu[0][i]);
			reset();
		}
		else
		{
			printf("%s\n", menu[0][i]);
		}
	}
}


int menu(){
	system("cls");
	red ();
    printf("test");
    reset ();
    int selection, i = 1;

	while(1){
		if (selection == 5){
			selection = 1;
		}
		else if (selection < 1){
			selection = 5;
		}
		if (getch() == 224){ //224 is Escape
    	switch(getch()) {
    		case 72:
    			system("cls");
    			selection --;
				break;
			case 80:
				system("cls");
				selection ++;
				break;
			default :
				break;
		}
		
		menuMain(selection);
	}    
    

	}
}
