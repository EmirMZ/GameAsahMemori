#include <stdio.h>



void game_difficulty(int difficulty, int *num_of_colors, int *reaction_time);
void color_flash(int round_flashes, int num_of_colors, int reaction_time);
void play();

int game(){    
    /*
    	SYSTEM("COLOR XX") FORMAT:
    	- FIRST DIGIT = BACKGROUND COLOR
    	- SECOND DIGIT = FOREGROUND COLOR
    	ex:
    		system("color 10") = BLUE BACKGROUND AND BLACK FOREGROUND
    	
    	COLORS TO BE USED:
    	- BLACK 0
    	- BIRU 1
    	- HIJAU 2
    	- MERAH 4
    	- UNGU 5
    	- KUNING 6
    	
    	
    	REACTION TIMES (in microseconds) AND COLORS:
    	- EASY 850000 & 3
    	- NORMAL 600000 & 4
    	- HARD 350000 & 4
    	- INSANE 200000 & 5
    */
    srand(time(NULL));
    
	int difficulty, num_of_colors, reaction_time;
	

    
    // Error handling
	do{
		printf("\n? ");
	    scanf("%d", &difficulty);
	}while(difficulty < 1 || difficulty > 4);
    
    // nentuin ...
    game_difficulty(difficulty, &num_of_colors, &reaction_time);
    
    
    // main
    play(difficulty, num_of_colors, reaction_time);
    return 0;
}

void game_difficulty(int difficulty, int *num_of_colors, int *reaction_time){
	switch(difficulty){
    	case 1:
    		*num_of_colors = 3;
    		*reaction_time = 850000;
    		break;
    	case 2:
    		*num_of_colors = 4;
    		*reaction_time = 600000;
    		break;
    	case 3:
    		*num_of_colors = 4;
    		*reaction_time = 350000;
    		break;
    	case 4:
    		*num_of_colors = 5;
    		*reaction_time = 200000;
    		break;
	}
}

void color_flash(int round_flashes, int num_of_colors, int reaction_time){
	int prevColor = -1, currentColor = -1;
	
	do{
		while(prevColor == currentColor)
			currentColor = rand() % num_of_colors;
	
		prevColor = currentColor;
		
		system("cls");
		switch(currentColor){
			case 0: // RED
				system("color 40");
				usleep(reaction_time);
				break;
			case 1: // BLUE
				system("color 10");
				usleep(reaction_time);
				break;
			case 2: // GREEN
				system("color 20");
				usleep(reaction_time);
				break;
			case 3: // YELLOW
				system("color 60");
				usleep(reaction_time);
				break;
			case 4: // PURPLE
				system("color 50");
				usleep(reaction_time);
				break;	
		}
		round_flashes--;
	}while(round_flashes != 0);
}

void play(int difficulty, int num_of_colors, int reaction_time){
	int round_flashes = 3, round_counter = 1, status = 1;
	char diff[6];
	if(difficulty == 1) strcpy(diff, "EASY");
	else if(difficulty == 2) strcpy(diff, "NORMAL");
	else if(difficulty == 3) strcpy(diff, "HARD");
	else if(difficulty == 4) strcpy(diff, "INSANE");
	
	while(status == 1){
		printf("\n\t\tROUND %d - %s\n", round_counter, diff);
		printf("\nPress any key when ready...");
		getch();
		color_flash(round_flashes, num_of_colors, reaction_time);
		round_counter++;
		round_flashes++;
	}
}
