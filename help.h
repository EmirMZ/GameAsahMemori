#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>


int help(){
	system("cls");
	printf("============================= HELP =============================");
	printf("\nCara Kerja game ini adalah sebagai berikut :\n");
	printf("\n1. Masukkan nama dan tingkat kesulitan (Difficulty) yang ingin anda mainkan\n2. Ingatlah urutan warna yang akan ditampilkan pada layar anda");
	printf("\n3. Masukkan jawaban dari urutan warna yang telah dilihat \n   -> Jika anda benar maka anda masuk ke level berikutnya");
	printf("\n   -> Jika anda kalah, maka permainan akan berakhir dan menampilkan score anda");
	printf("\n4. Jika anda ingin melihat score yang ada, maka pilihlah option SCORE");
	printf("\n5. Untuk keluar dari program, pilihlah option EXIT");
	
	printf("\n\npress any key to go back to menu...");
	getch();
	system("cls");
	
	return 0;
}
