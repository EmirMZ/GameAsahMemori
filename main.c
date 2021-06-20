#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include "menu.h"
#include "game.h"


int main(){
	//enableVT();
	game();
	int uyey = menu(0);
	
	char str[60];
	
	char *filename = "program.txt";
    FILE *fp;
	fp = fopen(filename, "r+");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    // read one character at a time and
    // display it to the output
    
	
	
	
	fprintf(fp,"%d",uyey);
    
   		 fseek( fp, 0, SEEK_SET );
       if(fgets(str, 32, fp) != NULL ) {
      /* writing content to stdout */
       puts(str);
   }

	
    // close the file
    fclose(fp);
}

