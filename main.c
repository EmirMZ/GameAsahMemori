#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include "menu.h"
#include "game.h"

struct high_score{
	char nama[32];
	int score;
}high_score[32];


int store_highscore(int score,FILE *fp, char nama[32]){
	
	
	
	while (fgetc(fp) != EOF){
		fscanf(fp,"%[^\t]s%d",high_score_temp[i].nama,high_score_temp[i].score);
		i++;
	}
	size = i - 1;
	
	for(i = 1;i < size;++i){
		for(j = 0;j < size - i;j++){
			if(high_score[j+1].score < high_score[j].score)
			high_score_temp = high_score[j];
			high_score[j] = high_score[j + 1];
			high_score[j + 1] = high_score_temp;
		}
	}
	
	fseek( fp, 0, SEEK_SET );

	for(i = 0;i < size;++i){
		fprintf(fp,"%s\t%d\n",high_score_temp[i].nama,high_score_temp[i].score);
	}
}


int main(){
	char *filename = "program.txt";
	char nama[32];
    int i,j,size,score,selected_menu,exit_status = -1;
	FILE *fp;
	struct high_score high_score_temp;
	
	char str[60];
	
	char *filename = "program.txt";
    FILE *fp;
	fp = fopen(filename, "r+");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    while(exit_status == -1){
    	selected_menu = 
    	switch(menu(0)){
    		case 0:
    			
		}
    	
	}
	store_highscore(score,fp,nama[32]);

	

    fclose(fp);

}

