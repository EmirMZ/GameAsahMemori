#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define BASE_REACTION_TIME 300000 // <-- MODIFY THIS INSTEAD IF A CHANGE OF REACTION TIME IS NEEDED (VALUE IS IN MICROSECONDS)

struct Node{
    int answer;
    struct Node* next;
} *rear, *front;
typedef struct Node Node;

void free_answer(){
    struct Node *var = rear;
    while(var!=NULL){
        struct Node* buf=var->next;
		free(var);
		var = buf;
    }
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
    struct Node *var = rear;
    if(var!=NULL){
        while(var!=NULL){
            printf("%d",var->answer);
            var=var->next;
        }
    }
}

void game_difficulty(int difficulty, int *num_of_colors, int *reaction_time);
void play(int difficulty, int num_of_colors, int reaction_time);
void color_flash(int round_flashes, int num_of_colors, int reaction_time);
void display_answer();

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
    	- RED 4
    	- PURPLE 5
    	- YELLOW 6
    	
    	
    	REACTION TIMES (in microseconds) AND COLORS:
    	- EASY 900000 + BASE_REACTION_TIME & 3
    	- NORMAL 750000 + BASE_REACTION_TIME & 4
    	- HARD 550000 + BASE_REACTION_TIME & 4
    	- INSANE 400000 + BASE_REACTION_TIME & 5
    */
    
    srand(time(NULL));
	int difficulty, num_of_colors, reaction_time;
	
	/*
	printf("\nChoose the difficulty:\n");
    printf("1. EASY - 1.25s Reaction Time w/ 3 Colors\n");
    printf("2. NORMAL - 1.00s Reaction Time w/ 4 Colors\n");
    printf("3. HARD - 0.75s Reaction Time w/ 4 Colors\n");
    printf("4. INSANE - 0.60s Reaction Time w/ 5 Colors");
	*/
	
    // ERROR HANDLING
	do{
		printf("\n? ");
	    scanf("%d", &difficulty);
	}while(difficulty < 1 || difficulty > 4);

    // SETTING UP GAME DIFFICULTY
    game_difficulty(difficulty, &num_of_colors, &reaction_time);

    // COMMENCING GAME
    play(difficulty, num_of_colors, reaction_time);
    
    return 0;
}

void game_difficulty(int difficulty, int *num_of_colors, int *reaction_time){
	switch(difficulty){
    	case 1:
    		*num_of_colors = 3;
    		*reaction_time = 900000;
    		break;
    	case 2:
    		*num_of_colors = 4;
    		*reaction_time = 750000;
    		break;
    	case 3:
    		*num_of_colors = 4;
    		*reaction_time = 550000;
    		break;
    	case 4:
    		*num_of_colors = 5;
    		*reaction_time = 400000;
    		break;
	}
}

void color_flash(int round_flashes, int num_of_colors, int reaction_time){
	int prevColor = -1, currentColor = -1;
	
	// RANDOMIZE COLOR WITHOUT USING PARALLEL PROGRAMMING
	do{
		while(prevColor == currentColor)
			currentColor = rand() % num_of_colors;
	
		prevColor = currentColor;
		add_answer(currentColor);
		
		system("cls");
		switch(currentColor){
			case 0: // RED
				system("color 40");
				usleep(BASE_REACTION_TIME);
				usleep(reaction_time);
				break;
			case 1: // BLUE
				system("color 10");
				usleep(BASE_REACTION_TIME);
				usleep(reaction_time);
				break;
			case 2: // GREEN
				system("color 20");
				usleep(BASE_REACTION_TIME);
				usleep(reaction_time);
				break;
			case 3: // YELLOW
				system("color 60");
				usleep(BASE_REACTION_TIME);
				usleep(reaction_time);
				break;
			case 4: // PURPLE
				system("color 50");
				usleep(BASE_REACTION_TIME);
				usleep(reaction_time);
				break;	
		}
		round_flashes--;
	}while(round_flashes != 0);
}

void play(int difficulty, int num_of_colors, int reaction_time){
	int round_flashes = 3, round_counter = 1, status = 1; // <- GAME'S STATUS (CORRECT GUESS OR WRONG GUESS)
	char diff[6];
	
	if(difficulty == 1) strcpy(diff, "EASY");
	else if(difficulty == 2) strcpy(diff, "NORMAL");
	else if(difficulty == 3) strcpy(diff, "HARD");
	else if(difficulty == 4) strcpy(diff, "INSANE");
	
	// STATE OF PLAY
	while(status == 1){
		if(round_counter != 1) free_answer(); // DELETE ANSWER AFTER EACH ROUND
		system("color 06"); // BLACK BACKGROUND YELLOW FOREGROUND
		printf("\n\t\t\t\t\tROUND %d - %s\n", round_counter, diff);
		printf("\t\t\t\t\t    %d Flashes\n", round_flashes);
		printf("\n\t\t\t      Press the ENTER key when ready to start...");
		
		fflush(stdin);
		getchar();
		fflush(stdin);
		
		color_flash(round_flashes, num_of_colors, reaction_time);
		round_counter++;
		round_flashes++;
		display_answer();
	}
}
