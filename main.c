#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include "menu.h"
#include "game.h"
#include "help.h"

int store_highscore(int score, char nama[32]);
void sort_score(); // in a decreasing order

int main(){
	char nama[32];
    int i,j,size,score,exit_status = -1;

	char str[60];

    while(exit_status == -1){
    	switch(menu(0)){
    		case 0:
    			system("cls");
    			printf ("---------------------------------------------------------------------------------------------------\n");
    			printf("\n\t\t\t              Enter your name : ");
    			fflush(stdin);
    			scanf("%s", nama);
    			printf ("\n---------------------------------------------------------------------------------------------------\n");
    			score = game(); // rand() % 24000; 
    			// printf("\nYour score is %d", score);
    			store_highscore(score,nama);
    			// sleep(3);
    			
    			sort_score();
    			break;
    		
    		case 1:
    			help();
    			break;
    		
    		case 2:
    			
    			break;
    		
    		case 3:
    			exit_status = 1;
    			break;
    			
		}
	}


	

    

}

int store_highscore(int score, char nama[32]){
	
	char *filename = "program.txt"; 
	char nama_database[10][32]; 	
	char nama_database_temp[32];	
	char ch; 						
	int score_database[10]; 		
	int score_database_temp;		
	
	FILE *fp;	

	int overwrite_status = 0; 
	int i = 0,j,size; 
	
	fp = fopen(filename, "r");  
    if (fp == NULL) 
    {
    	fp = fopen(filename, "w+");
    	if(fp == NULL){
    	printf("Error: could not open file %s", filename);
        getch();
        return 1;
		}
        
    }
	//fseek( fp, 0, SEEK_SET );
	
	while (ch != EOF){ 
		fscanf(fp,"%d%s", &score_database[i], nama_database[i]);
		ch = fgetc(fp); 
		i++;
	}
	
	size = i - 1 ;
	for(i = 0;i < size;i++){
		if(strcmp(nama_database[i],nama) == 0){
			strcpy(nama_database[i],nama);
			score_database[i] = score;
			overwrite_status = 1;
			size--;	
		}
	}
	
	if(overwrite_status == 0){
		strcpy(nama_database[size],nama);
		score_database[size] = score;	
	}
	
	for (i = 0; i < size ; ++i) 
        {
            for (j = i + 1; j < size - i ; ++j) 
            {
                if (score_database[i] < score_database[i + 1]) 
                {
                	strcpy (nama_database[i], nama_database[i + 1]);
                    score_database_temp = score_database[i];
                    score_database[i] = score_database[i+1];
                    score_database[i+1] = score_database_temp;
                }
            }
        }

	fp = fopen(filename, "w");
	for(i = 0;i <= size ;++i){
		
		fprintf(fp,"%d %s\n", score_database[i], nama_database[i]);
	}
	
	fclose(fp);	

	// getch();
	
	//memset(high_score, 0, sizeof(high_score));
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
