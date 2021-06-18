#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include "menu.h"
#include "game.h"


int main(){
	//enableVT();
	//menu(0);
	//game();
	
	int num;
    FILE *fptr;
    
    fptr = fopen("program.txt","w+");
	
	if(fptr == NULL)
    {
      printf("Error!");   
      exit(1);             
    }
    
     printf("Enter num: ");
   scanf("%d",&num);

   fprintf(fptr,"%d",num);
   printf("Value of n= %d", num);
   
   fclose(fptr);

}
