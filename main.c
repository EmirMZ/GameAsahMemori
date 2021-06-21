#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include "menu.h"
#include "game.h"
#include "help.h"

int store_highscore(int score, char nama[32]);

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
    			score = game(); 
    			store_highscore(score,nama);
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
		fscanf(fp,"%s%d",nama_database[i],&score_database[i]);
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
		
		printf("%s %d\n",nama_database[i],score_database[i]);
		fprintf(fp,"%s %d\n",nama_database[i],score_database[i]);
	}
	
	fclose(fp);	

	getch();
	
	//memset(high_score, 0, sizeof(high_score));
	}


