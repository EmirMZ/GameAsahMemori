#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include "menu.h"
#include "game.h"
#include "help.h"
#include <time.h>
#define MAX_LEN 100 // Length of each line in input file.

// prototype
int store_highscore(int score, char nama[32]);
void sort_score(); // in a decreasing order
void print_highscore();// print score

int main(){
	char nama[32];
    int i,j,size,score,exit_status = -1;
	char str[60];
	
	srand(time(NULL));// set seed untuk randomize game
    
	while(exit_status == -1){// exit flag
    	switch(menu(0)){
    		case 0:// play
    			system("cls");// start game banner
    			printf ("---------------------------------------------------------------------------------------------------\n");
    			printf("\n\t\t\t              Enter your name : ");
    			fflush(stdin);
    			scanf("%s", nama);
    			printf ("\n---------------------------------------------------------------------------------------------------\n");
    			score =rand() % 1000; // game();	// play the game	
    			store_highscore(score,nama); // store highscore
    			sort_score();
    			break;
    		
    		case 1:// help
    			help();
    			break;
    		
    		case 2:// show highscore
    			system("cls");
    			print_highscore();
    			getchar();
    			break;
    		
    		case 3:// exit
    			exitBanner();
    			exit_status = 1;
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
	scoreBanner();// tampilkan banner
	footer();
	prompt();
}

void sort_score(){
    const char *file_name = "program.txt";// nama file program
    const char *file_summary = "sorted.txt";// nama file sorted
    char temp_data[MAX_LEN];
    char **data = NULL; // String List
    int i, j;
    int num_of_lines = 0;
	
    FILE * p_file_log = NULL;
    FILE * p_Summary = NULL;

    if ( (p_file_log = fopen(file_name, "r")) == NULL ) {
        fprintf(stderr, "Error: Could not open %s\n", file_name);
    }
    if ( (p_Summary = fopen(file_summary, "w")) == NULL ) {
        fprintf(stderr, "Error: Could not open %s\n", file_summary);
    }

    // Read and store in a string list.
    while(fgets(temp_data, MAX_LEN, p_file_log) != NULL) {
        // Remove the trailing newline character
        
		if(strchr(temp_data,'\n'))
            temp_data[strlen(temp_data) - 1] = '\0';
            
        data = (char**)realloc(data, sizeof(char**) * (num_of_lines + 1));
        data[num_of_lines] = (char*)calloc(MAX_LEN, sizeof(char));
        strcpy(data[num_of_lines], temp_data);
        num_of_lines++;
    }
    // Sort the array decreasingly.
    for(i= 0; i < (num_of_lines - 1); ++i) {
        for(j = 0; j < ( num_of_lines - i - 1); ++j) {
            if(atoi(data[j]) < atoi(data[j + 1])){
                strcpy(temp_data, data[j]);
                strcpy(data[j], data[j + 1]);
                strcpy(data[j + 1], temp_data);
            }
        }
    }
    // Write it to outfile. file.
    for(i = 0; i < num_of_lines; i++)
        fprintf(p_Summary,"%s\n",data[i]);
    // free each string
    for(i = 0; i < num_of_lines; i++)
        free(data[i]);
    // free string list.
    free(data);
    fclose(p_file_log);
    fclose(p_Summary);
}

void print_highscore(){
    char c;
    int i = 0;
    FILE *fp = fopen("sorted.txt", "r");
    if (fp == NULL)
    {
		printf("Cannot open file \n");
		exit(0);
    }
  
    // Read contents from file
    c = fgetc(fp);
    while (c != EOF)
    {
    	
    	printf ("%c", c);
		c = fgetc(fp);
		
		if(c == '\n'){
			i++;
		}
		if(i == 10){
			c = EOF;
		}

    }
  
    fclose(fp);
}
