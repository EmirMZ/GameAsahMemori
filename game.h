#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>
#include "queue.h"
#include "soundtracks.h"
#include "colors.h"

#define MAX_LEN 100 // Length of each line in input file.

typedef struct score_tracking{
	int *current_score;
	int highest_score;
} st;

void score_tracker(st record);
void play(int difficulty, int num_of_colors, int reaction_time, int *score, int *score_multiplier, st record);
void input_and_check_answer(char input_answer[60], char answer[60], int *status,int round_flashes);
void game_difficulty(int difficulty, int *num_of_colors, int *reaction_time, int *score_multiplier);
void color_flash(int round_flashes, int num_of_colors, int reaction_time);
void concatenate(char answer[60]);
void display_score(int *score);
int print_answer_guide();
void prompt();

int game(){
    /*
    	SYSTEM("COLOR XX") FORMAT:
    	- FIRST DIGIT = BACKGROUND COLOR
    	- SECOND DIGIT = FOREGROUND COLOR
    	ex:
    		system("color 10") = BLUE BACKGROUND AND BLACK FOREGROUND
    	
    	COLORS TO BE USED:
    	- BLACK 0
    	- BLUE 1
    	- GREEN 2
    	- AQUA 3
    	- RED 4
    	- PURPLE 5
    	
    	REACTION TIMES (in microseconds) AND COLORS:
    	- EASY 900000 + BASE_REACTION_TIME & 3
    	- NORMAL 750000 + BASE_REACTION_TIME & 4
    	- HARD 550000 + BASE_REACTION_TIME & 4
    	- INSANE 400000 + BASE_REACTION_TIME & 5
    */
    
    srand(time(NULL));
	int score = 0, highscore, score_multiplier, difficulty, num_of_colors, reaction_time;
	
	FILE *fp;
	const char *filename = "program.txt"; 
	char highest_score_in_file[30];
	fp = fopen(filename, "r");
	fgets(highest_score_in_file, 30, fp);
	fclose(fp);
	
	struct score_tracking record;
	record.current_score = &score;
	record.highest_score = atoi(highest_score_in_file);
	// record.highest_score = 
	
	
	/*
	printf("\n\t\t\t                Choose the Difficulty \n");
    printf("\t\t\t     1. EASY - 1.24s Reaction Time w/ 3 Colors\n");
    printf("\t\t\t     2. NORMAL - 0.98s Reaction Time w/ 4 Colors\n");
    printf("\t\t\t     3. HARD - 0.68s Reaction Time w/ 4 Colors\n");
    printf("\t\t\t     4. INSANE - 0.40s Reaction Time w/ 5 Colors");
	
    // ERROR HANDLING
	do{
		printf("\n\t\t\t                 Submit here : ");
	    scanf("%d", &difficulty);
	}while(difficulty < 1 || difficulty > 4);
	*/
	
	difficulty = menu(1) + 1;

	printf ("\n---------------------------------------------------------------------------------------------------\n");
	system("cls");
	
    // SETTING UP GAME BY THE SELECTED DIFFICULTY
    game_difficulty(difficulty, &num_of_colors, &reaction_time, &score_multiplier);
	
    // COMMENCING GAME
    play(difficulty, num_of_colors, reaction_time, &score, &score_multiplier, record);
    
    return score;
}

void game_difficulty(int difficulty, int *num_of_colors, int *reaction_time, int *score_multiplier){
	switch(difficulty){
    	case 1:
    		*num_of_colors = 3;
    		*reaction_time = 620000;
    		*score_multiplier = 20;
    		break;
    	case 2:
    		*num_of_colors = 4;
    		*reaction_time = 490000;
    		*score_multiplier = 40;
    		break;
    	case 3:
    		*num_of_colors = 4;
    		*reaction_time = 340000;
    		*score_multiplier = 70;
    		break;
    	case 4:
    		*num_of_colors = 5;
    		*reaction_time = 200000;
    		*score_multiplier = 100;
    		break;
	}
}

void color_flash(int round_flashes, int num_of_colors, int reaction_time){
	int prev_color = -1, current_color = -1;	
	
	// RANDOMIZE COLOR WITHOUT USING PARALLEL PROGRAMMING
	do{
		while(prev_color == current_color)
			current_color = rand() % num_of_colors;
	
		prev_color = current_color;
		add_answer(current_color);
		
		// COLOR FLASH TIME !!
		switch(current_color){
			case 0: //BLUE
				blue_flash(reaction_time);
				break;
			case 1: // GREEN
				green_flash(reaction_time);
				break;
			case 2: // AQUA
				aqua_flash(reaction_time);
				break;
			case 3: // RED
				red_flash(reaction_time);
				break;
			case 4: // PURPLE
				purple_flash(reaction_time);
				break;	
		}
		round_flashes--;
	}while(round_flashes != 0);
}

void play(int difficulty, int num_of_colors, int reaction_time, int *score, int *score_multiplier, st record){
	int i, round_flashes = 3, round_counter = 1, status = 1; // <- GAME'S STATUS (CORRECT GUESS OR WRONG GUESS)
	char diff[6], answer[60], input_answer[60];
	
	if(difficulty == 1) strcpy(diff, "EASY");
	else if(difficulty == 2) strcpy(diff, "NORMAL");
	else if(difficulty == 3) strcpy(diff, "HARD");
	else if(difficulty == 4) strcpy(diff, "INSANE");
	
	// STATE OF PLAY
	while(status == 1){
		system("color 06"); // BLACK BACKGROUND YELLOW FOREGROUND
		display_score(score);
		if(round_counter % 6 == 0){
			#pragma omp parallel
			{
				printf("\n\t\t     CONGRATS ON PASSING LEVEL %d !!! - FROM THREAD %d OF %d", round_counter - 1, omp_get_thread_num(), omp_get_num_threads());
			}
			printf("\n\t\t\t            Keep up the good work !!\n");
			check_jingle();
		}
		score_tracker(record);
		printf("\t  ------------------------------------------------------------\n");
		printf("\n\t\t\t\t     ** ROUND %d - %s **\n", round_counter, diff);
		printf("\t\t\t\t         %d Flashes\n", round_flashes);
		printf("\n\t\t  ------------------------------------------------------------");

		prompt();
		
		system("cls");
		color_flash(round_flashes, num_of_colors, reaction_time);
		display_answer();
		concatenate(answer);
		input_and_check_answer(input_answer, answer, &status,round_flashes);
		#pragma omp single
		*score += round_flashes * *score_multiplier * status;
		round_counter++;
		round_flashes++;
		system("cls");
	}
}

void input_and_check_answer(char input_answer[60], char answer[60], int *status,int round_flashes){
	int i;
	system("color 06");
	printf("\t\t  ------------------------------------------------------------");
	for(i = 0;i < round_flashes;i++){
		input_answer[i] = print_answer_guide();
	}
	
	
	printf ("\n\n\t\t\t          Submit your answers: ");
	scanf("%s", input_answer);
	free_answer();
	if (strcmp(input_answer, answer) == 0){
		printf("\n\n\t\t  ------------------------------------------------------------");
		printf("\n\t\t\t      Correct! Get ready for the next round");
		correct_jingle();
		printf("\n\t\t  ------------------------------------------------------------");
		prompt();		
	}else{
		printf("\n\n\t\t  ------------------------------------------------------------");
		printf ("\n\t\t\t                    Wrong!");
		wrong_jingle();
		printf ("\n\t\t\t            Thank you for playing!");
		printf("\n\t\t  ------------------------------------------------------------");
		prompt();
		system("cls");
		*status = 0;
	}
}

void concatenate(char answer[60]){
	Node *var = rear;
	char s1[30], s2[30];
	if(var != NULL){
		sprintf(s1, "%d", var->answer);
		while(var->next != NULL){
			sprintf(s2, "%d", var->next->answer);
			strcat(s1, s2);
			strcpy(answer, s1);
			var = var->next;
		}
	}	
}

void prompt(){
	printf("\n\t\t\t      Press the ENTER key to continue...");
	fflush(stdin);
	getchar();
}

void display_score(int *score){
	printf("Score: %d", *score);
}
	
int print_answer_guide(){
	
	/*
	printf("\n\n BLUE   = 0\n");
	printf("\n GREEN  = 1\n");
	printf("\n AQUA   = 2\n");
	printf("\n RED    = 3\n");
	printf("\n PURPLE = 4\n");
	*/
	return menu(2);
}

void score_tracker(st record){
	if(*(record.current_score) >= record.highest_score){
		printf("\nCongratulations! You have achieved a new highscore.\n");
	}else{
		printf("\nYou are %d points away from the current highscore!\n", record.highest_score - *(record.current_score));
	}
}
