#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include "menu.h"
#include "game.h"
#include "help.h"
#include <time.h>

int store_highscore(int score, char nama[32]);
void sort_score(); // in a decreasing order
void print_highscore();

int main(){
	char nama[32];
    int i,j,size,score,exit_status = -1;
	char str[60];
	srand(time(NULL));
    while(exit_status == -1){
    	switch(menu(0)){
    		case 0:
    			system("cls");
    			printf ("---------------------------------------------------------------------------------------------------\n");
    			printf("\n\t\t\t              Enter your name : ");
    			fflush(stdin);
    			scanf("%s", nama);
    			printf ("\n---------------------------------------------------------------------------------------------------\n");
    			score = rand() % 4500; // game();		
    			store_highscore(score,nama);
    			sort_score();
    			break;
    		
    		case 1:
    			help();
    			break;
    		
    		case 2:
    			system("cls");
    			print_highscore();
    			getchar();
    			break;
    		
    		case 3:
    			exitBanner();
    			exit_status = 1;
    			break;	
		}
	}
}

int store_highscore(int score, char *nama){
	FILE *fp = fopen("program.txt", "a");
	if (fp == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	fprintf(fp, "%d %s\n", score, nama);
	fclose(fp);
	scoreBanner();
	footer();
	prompt();
}

void sort_score(){
    const char *file_name = "program.txt";
    const char *file_summary = "sorted.txt";
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
    // Sort the array decrreasingly.
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
    }
  
    fclose(fp);
}
