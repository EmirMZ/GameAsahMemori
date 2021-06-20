#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>

int display_score()
{
	char *filename = "program.txt";
	char *file_name = "test.txt";
    FILE *fp = fopen(filename, "r");
    FILE *fp1 = fopen(file_name, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    // read one character at a time and
    // display it to the output
    
    printf("Nama : ");
    char ch;
    while ((ch = fgetc(fp)) != EOF)
        putchar(ch);

    while ((ch = fgetc(fp1)) != EOF)
        putchar(ch);

	printf("\n\n");
    // close the file
    fclose(fp);

    return 0;
}


int main(){
	int a;
	
	display_score();
}
