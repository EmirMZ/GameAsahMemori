#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>
#include "queue.h"
#include "soundtracks.h"
#include "colors.h"

// A struct to keep track of the player score
typedef struct score_tracking{
	int *current_score;
	int highest_score;
} st;

void play(int difficulty, int num_of_colors, int reaction_time, int *score, int *score_multiplier, st record); // The gameplay resides here
void input_and_check_answer(char input_answer[60], char answer[60], int *status,int round_flashes); // Check player's answer to the game's answer
void game_difficulty(int difficulty, int *num_of_colors, int *reaction_time, int *score_multiplier); // Set up game based on the selected difficulty
void color_flash(int round_flashes, int num_of_colors, int reaction_time); // Color flashing function to.., well.., flash colors
void concatenate(char answer[60]); // Concatenate answers stored in queue to a string
void display_score(int *score); // Display the player's current score
void score_tracker(st record); // A score tracking function to.., well.., track the player's score
void prompt(); // A prompt to the user to press the required key to continue

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
	
	char highest_score_in_file[30];
	FILE *fp = fopen("sorted.txt", "r");
	if (fp == NULL)
    {
		printf("Cannot open sorted.txt \n");
		exit(0);
    }
	fgets(highest_score_in_file, 30, fp);
	fclose(fp);
	
	struct score_tracking record;
	record.current_score = &score;
	record.highest_score = atoi(highest_score_in_file);
	
	// Call menu to display the difficulties and ask the player to select it
	difficulty = menu(1) + 1;

	printf ("\n---------------------------------------------------------------------------------------------------\n");
	system("cls");
	
    // Setting up game by the selected difficulty
    game_difficulty(difficulty, &num_of_colors, &reaction_time, &score_multiplier);
	
    // Commencing game
    play(difficulty, num_of_colors, reaction_time, &score, &score_multiplier, record);
    
    return score;
}

void game_difficulty(int difficulty, int *num_of_colors, int *reaction_time, int *score_multiplier){
	// Number of colors, reaction time, and score multiplier vary depending on the difficulty
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
	
	do{
		// Do not have a repeated color flashing
		while(prev_color == current_color)
			current_color = rand() % num_of_colors;
		
		prev_color = current_color;
		add_answer(current_color); // Add the current color to the answer queue
		
		// COLOR FLASH TIME !!
		switch(current_color){
			case 0: // Blue
				blue_flash(reaction_time);
				break;
			case 1: // Green
				green_flash(reaction_time);
				break;
			case 2: // Aqua
				aqua_flash(reaction_time);
				break;
			case 3: // Red
				red_flash(reaction_time);
				break;
			case 4: // Purple
				purple_flash(reaction_time);
				break;	
		}
		round_flashes--;
	}while(round_flashes != 0);
}

void play(int difficulty, int num_of_colors, int reaction_time, int *score, int *score_multiplier, st record){
	int i, round_flashes = 3, round_counter = 1, status = 1; // <- Game's status (correct guess or wrong guess)
	char diff[6], answer[60], input_answer[60];
	
	if(difficulty == 1) strcpy(diff, "EASY");
	else if(difficulty == 2) strcpy(diff, "NORMAL");
	else if(difficulty == 3) strcpy(diff, "HARD");
	else if(difficulty == 4) strcpy(diff, "INSANE");
	
	// State of play
	while(status == 1){
		system("color 06"); // Black background yellow foreground
		display_score(score);
		if(round_counter % 6 == 0){ // Every 6 rounds, player gets a congrats message from the program. How nice!
			#pragma omp parallel
			{
				printf("\n\t\t     CONGRATS ON PASSING LEVEL %d !!! - FROM THREAD %d OF %d", round_counter - 1, omp_get_thread_num(), omp_get_num_threads());
			}
			printf("\n\t\t\t            Keep up the good work !!\n");
			check_jingle();
		}
		score_tracker(record); // Tell the player how they are doing on score
		printf("\t  ------------------------------------------------------------\n");
		printf("\n\t\t\t\t     ** ROUND %d - %s **\n", round_counter, diff);
		printf("\t\t\t\t         %d Flashes\n", round_flashes);
		printf("\n\t\t  ------------------------------------------------------------");
		prompt();
		
		system("cls");
		
		color_flash(round_flashes, num_of_colors, reaction_time); // Start flashing
		display_answer(); // Display the correct answer
		concatenate(answer); // Concatenate answer in queue and store it answer array
		input_and_check_answer(input_answer, answer, &status,round_flashes); // Make the player input their answer and check it
		#pragma omp single
		*score += round_flashes * *score_multiplier * status; // A pragma omp single directive to calculate the score
		round_counter++;
		round_flashes++;
		system("cls");
	}
}

void input_and_check_answer(char input_answer[60], char answer[60], int *status,int round_flashes){
	int i;
	char character_answer; // char to store each player answer input
	
	system("color 06");
	printf("\t\t  ------------------------------------------------------------");
	// Iteration to assign character_answer to each input_answer element
	for(i = 0; i < round_flashes;i++){
		character_answer = menu(2) + '0'; // Assign char by calling menu
		input_answer[i] = character_answer; // Assign character_answer to each input_answer element
	}
	
	printf("%s\n", input_answer);
	display_answer();
	getchar();
	
	if (strcmp(input_answer, answer) == 0){ // If the player's answer is correct, then...
		printf("\n\n\t\t  ------------------------------------------------------------");
		printf("\n\t\t\t      Correct! Get ready for the next round");
		correct_jingle();
		printf("\n\t\t  ------------------------------------------------------------");
		prompt();		
	}else{ // If the player's answer is wrong, then...
		printf("\n\n\t\t  ------------------------------------------------------------");
		printf ("\n\t\t\t                    Wrong!");
		wrong_jingle();
		printf ("\n\t\t\t            Thank you for playing!");
		printf("\n\t\t  ------------------------------------------------------------");
		prompt();
		system("cls");
		*status = 0; // Change status to 0 so the program stops playing
	}
	free_answer(); // Free the program's answer for the next add_answer() call
}

void concatenate(char answer[60]){
	Node *var = rear;
	char s1[30], s2[30]; // Two arrays to store each answer and concatenate the latter to the former
	
	if(var != NULL){
		sprintf(s1, "%d", var->answer); // Change int in var->answer to string to s1
		while(var->next != NULL){
			sprintf(s2, "%d", var->next->answer); // Change int in var->next->answer to string to s2
			strcat(s1, s2); // Concatenate s2 to s1
			strcpy(answer, s1); // Copy s1 to answer
			var = var->next; // Point to the next answer in queue
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

void score_tracker(st record){
	if(*(record.current_score) >= record.highest_score){
		printf("\nCongratulations! You have achieved a new highscore.\n");
	}else{
		printf("\nYou are %d points away from the current highscore!\n", record.highest_score - *(record.current_score));
	}
}
