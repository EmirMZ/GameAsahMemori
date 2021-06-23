#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include "menu.h"
#include "game.h"
#include "help.h"
#include <time.h>

// Prototypes
int store_highscore(int score, char nama[32]); // store scores
void sort_score(); // in a decreasing order
void print_highscore(); // print scores

int main(){
	char nama[32];
    int score;
	
	srand(time(NULL));// set seed untuk randomize game
    
	while(1){
    	switch(menu(0)){
    		case 0:// play
    			system("cls");// start game banner
    			printf ("---------------------------------------------------------------------------------------------------\n");
    			printf("\n\t\t\t              Enter your name : ");
    			fflush(stdin);
    			scanf("%s", nama);
    			printf ("\n---------------------------------------------------------------------------------------------------\n");
    			score = game();	// play the game	
    			store_highscore(score,nama); // store highscore
    			print_highscore();
    			break;
    		
    		case 1:// help
    			help();
    			break;
    		
    		case 2:// show highscore
    			system("cls");
    			print_highscore();
    			break;
    		
    		case 3:// exit
    			exitBanner();
    			exit(0);
    			break;	
		}
	}
}

int store_highscore(int score, char *nama){
	FILE *fp = fopen("program.txt", "a");// file open dengan appending mode
	
	if (fp == NULL)// keluar error jika file ada tapi diakses program lain
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	
	fprintf(fp, "%d %s\n", score, nama); //store value to program.txt
	fclose(fp);// close fp
	prompt();
}

void sort_score(){
    char temp_data[50]; // to store each line in a file
    char **data = NULL; // a 2 dimensional array to store lines with each various characters
    int i, j, num_of_lines = 0;
	
	// Opening files
    FILE *file_name = fopen("program.txt", "r");
    if(file_name == NULL){
    	printf("Cannot open program.txt \n");
		exit(0);
	}
	
    FILE *file_summary = fopen("sorted.txt", "w");
    if(file_summary == NULL){
    	printf("Cannot open sorted.txt \n");
		exit(0);
	}

    // Read each line in program.txt and store it in temp_data
    while(fgets(temp_data, 100, file_name) != NULL){
    	
        // Search for newline character in the line (always in the of the line) and remove it
		if(strchr(temp_data,'\n'))
            temp_data[strlen(temp_data) - 1] = '\0'; // Change the end of the line to \0 (null terminator)
        
        data = realloc(data, sizeof(char**) * (num_of_lines + 1)); // Reallocate memory for data by the number of lines
        data[num_of_lines] = calloc(50, sizeof(char)); // Each index of data gets 100 bytes of space
        strcpy(data[num_of_lines], temp_data); // Copy temp_data to that data index 
        num_of_lines++; // Update to next line
        // In the end, data have stored all of the lines in file_name in each of its index
    }
    
    // Sort data decreasingly
    for(i= 0; i < (num_of_lines - 1); ++i) {
        for(j = 0; j < (num_of_lines - i - 1); ++j) {
            if(atoi(data[j]) < atoi(data[j + 1])){ // atoi() will change each line (String) to integer
                strcpy(temp_data, data[j]);
                strcpy(data[j], data[j + 1]);
                strcpy(data[j + 1], temp_data);
            }
        }
    }
    
    // Write each data to sorted.txt
    for(i = 0; i < num_of_lines; i++)
        fprintf(file_summary, "%s\n", data[i]);
        
    // Free each string
    for(i = 0; i < num_of_lines; i++)
        free(data[i]);
    
    // Free string list.
    free(data);
    
    // Close all files used
    fclose(file_name);
    fclose(file_summary);
}

void print_highscore(){
    char ch[50];
    int linecount = 0;
    FILE *fp = fopen("sorted.txt", "r");
    if (fp == NULL)
    {
		printf("Cannot open sorted.txt \n");
		exit(0);
    }
    scoreBanner();
    printf("\n");
    // Read each line and store it in ch array
    while(fgets(ch, 50, fp) != NULL) {
	    printf("\t\t\t  %d. %s", linecount + 1, ch); // Print the sorted score
	    if (++linecount == 10) break; // Stop printing after 10 scores
	}
	footer();
    fclose(fp);
    prompt();
}
