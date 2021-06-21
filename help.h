#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>


void help(){
	system("cls");
	printf("\t\t     ----------------------------- HELP -----------------------------");
	printf("\n\nCara Kerja game ini adalah sebagai berikut :\n");
	printf("\n1. Masukkan nama dan tingkat kesulitan (Difficulty) yang ingin anda mainkan\n2. Ingatlah urutan warna yang akan ditampilkan pada layar anda");
	printf("\n3. Masukkan jawaban dari urutan warna yang telah dilihat \n   -> Jika anda benar maka anda masuk ke level berikutnya");
	printf("\n   -> Jika anda kalah, maka permainan akan berakhir dan menampilkan score anda");
	printf("\n4. Jika anda ingin melihat score yang ada, maka pilihlah option SCORE");
	printf("\n5. Untuk keluar dari program, pilihlah option EXIT");
	printf("\n\n\t\t     ----------------------------------------------------------------");
	
	printf("\n\n\t\t\t\t     Press the ENTER key to continue...");
    fflush(stdin);
	getch();
	system("cls");
}
