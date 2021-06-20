#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>
#include <windows.h>
#include "soundtracks.h"

struct Node{
    int answer;
    struct Node *next;
} *front, *rear;
typedef struct Node Node;

void free_answer(){
    Node *var = rear;
    while(var!=NULL){
        struct Node* buf = var->next;
		free(var);
		var = buf;
    }
    rear = NULL;
    front = NULL;
}

void add_answer(int random_answer){
    Node *temp;
    temp = (Node*)malloc(sizeof(Node));
    temp->answer = random_answer;
    if (front == NULL){
        front = temp;
        front->next = NULL;
        rear = front;
    }else{
        front->next = temp;
        front = temp;
        front->next = NULL;
    }
}

void display_answer(){
    Node *var = rear;
    if(var != NULL){
        while(var != NULL){
            printf("%d", var->answer);
            var = var->next;
        }
    }
}

void game_difficulty(int difficulty, int *num_of_colors, int *reaction_time);
void play(int difficulty, int num_of_colors, int reaction_time);
void color_flash(int round_flashes, int num_of_colors, int reaction_time);
void concatenate(char answer[60]);
void prompt();
void input_and_check_answer(char input_answer[60], char answer[60], int *status);

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
	int score, difficulty, num_of_colors, reaction_time, random_answer;
	
	printf("\nChoose the difficulty:\n");
    printf("1. EASY - 1.24s Reaction Time w/ 3 Colors\n");
    printf("2. NORMAL - 0.98s Reaction Time w/ 4 Colors\n");
    printf("3. HARD - 0.68s Reaction Time w/ 4 Colors\n");
    printf("4. INSANE - 0.40s Reaction Time w/ 5 Colors");
	
    // ERROR HANDLING
	do{
		printf("\n? ");
	    scanf("%d", &difficulty);
	}while(difficulty < 1 || difficulty > 4);

    // SETTING UP GAME BY THE SELECTED DIFFICULTY
    game_difficulty(difficulty, &num_of_colors, &reaction_time);
	
    // COMMENCING GAME
    play(difficulty, num_of_colors, reaction_time);
    
    return score;
}

void game_difficulty(int difficulty, int *num_of_colors, int *reaction_time){
	switch(difficulty){
    	case 1:
    		*num_of_colors = 3;
    		*reaction_time = 620000;
    		break;
    	case 2:
    		*num_of_colors = 4;
    		*reaction_time = 490000;
    		break;
    	case 3:
    		*num_of_colors = 4;
    		*reaction_time = 340000;
    		break;
    	case 4:
    		*num_of_colors = 5;
    		*reaction_time = 200000;
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
				system("color 10");
				Beep(1046.50, reaction_time / 1000);
				usleep(reaction_time);
				break;
			case 1: // GREEN
				system("color 20");
				Beep(1174.66, reaction_time / 1000);
				usleep(reaction_time);
				break;
			case 2: // AQUA
				system("color 30");
				Beep(1318.51, reaction_time / 1000);
				usleep(reaction_time);
				break;
			case 3: // RED
				system("color 40");
				Beep(1396.91, reaction_time / 1000);
				usleep(reaction_time);
				break;
			case 4: // PURPLE
				system("color 50");
				Beep(1567.98, reaction_time / 1000);
				usleep(reaction_time);
				break;	
		}
		round_flashes--;
	}while(round_flashes != 0);
}

void play(int difficulty, int num_of_colors, int reaction_time){
	int i, round_flashes = 3, round_counter = 1, status = 1; // <- GAME'S STATUS (CORRECT GUESS OR WRONG GUESS)
	char diff[6], answer[60], input_answer[60];
	
	if(difficulty == 1) strcpy(diff, "EASY");
	else if(difficulty == 2) strcpy(diff, "NORMAL");
	else if(difficulty == 3) strcpy(diff, "HARD");
	else if(difficulty == 4) strcpy(diff, "INSANE");
	
	// STATE OF PLAY
	while(status == 1){
		system("color 06"); // BLACK BACKGROUND YELLOW FOREGROUND
		if(round_counter % 6 == 0){
			#pragma omp parallel
			{
				printf("\n\t\t     CONGRATS ON PASSING LEVEL %d !!! - FROM THREAD %d OF %d", round_counter - 1, omp_get_thread_num(), omp_get_num_threads());
			}
			printf("\n\t\t\t            Keep up the good work !!\n");
			check_jingle();
		}
		
		if(round_counter != 1) free_answer(); // DELETE ANSWER AFTER EACH ROUND
		printf("\n\t\t\t\t\tROUND %d - %s\n", round_counter, diff);
		printf("\t\t\t\t\t    %d Flashes\n", round_flashes);
		prompt();
		
		system("cls");
		color_flash(round_flashes, num_of_colors, reaction_time);
		round_counter++;
		round_flashes++;
		display_answer();
		concatenate(answer);
		
		// bagian input jawaban underprogress
		// masih bermasalah gabisa nyocokin jawaban, tapi kalau salah langsung back to difficulty
		input_and_check_answer(input_answer, answer, &status);
		
		system("cls");
	}
}

void input_and_check_answer(char input_answer[60], char answer[60], int *status){
	system("color 06");
	printf ("\n\t\t\t          Submit your answers: ");
	scanf("%s", input_answer);
	
	if (strcmp(input_answer, answer) == 0){
		printf("\n\t\t\t    Correct! Get ready for the next round");
		correct_jingle();
		prompt();		
	}else{
		printf ("\n\t\t\t                    Wrong!");
		wrong_jingle();
		printf ("\n\t\t\t            Thank you for playing!");
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
