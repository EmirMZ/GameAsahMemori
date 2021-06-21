#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include "menu.h"
#include "game.h"
#include "help.h"



int store_highscore(int score, char nama[32]){
	char *filename = "program.txt";
	
	char nama_database[10][32];
	char nama_database_temp[32];
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
	

	
	
	while (fgetc(fp) != EOF){
		fscanf(fp,"%s%d",nama_database[i],&score_database[i]);
		i++;
	}
	//fseek( fp, 0, SEEK_SET );

	
	size = i - 1;

	for(i = 0;i < (size + 1);i++){
		if(strcmp(nama_database[i],nama) == 0){
			strcpy(nama_database[i],nama);
			score_database[i] = score;
			overwrite_status = 1;
		}
	}
	
	if(overwrite_status == 0){
		size++;
		strcpy(nama_database[i],nama);
		score_database[i] = score;	
	}

	
	for(i = 1;i < size;++i){
		for(j = 0;j < size - i;j++){
			if(score_database[j+1] < score_database[j])
			strcpy(nama_database[i],nama);
			score_database_temp = score_database[j];
			score_database[j] = score_database[j + 1];
			score_database[j + 1] = score_database_temp;
		}
	}
	

	


	fp = fopen(filename, "w");
	for(i = 0;i <= size;i++){
		
		printf("%s %d\n",nama_database[i],score_database[i]);
		fprintf(fp,"%s %d\n",nama_database[i],score_database[i]);
	}
	
	fclose(fp);	

	getch();
	
	//memset(high_score, 0, sizeof(high_score));
}


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
    			score = 1000; // score = game(); <-- is now applicable
    			game();
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
	return 0;
}

