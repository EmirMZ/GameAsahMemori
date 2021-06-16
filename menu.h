void red () {
  printf("\033[1;31m");
}

void green () {
  printf("\033[0;32m");
}

void yellow () {
  printf("\033[0;35m");
}

void reset () {
  printf("\033[0m");
}


int menu(){
	system("cls");
	red ();
    printf("test");
    reset ();

	while(1){
		if (getch() == 224){ //224 is Escape
    	switch(getch()) {
    		case 72:
    			system("cls");
    			green ();
    			printf("up arrow");
    			reset ();
				break;
			case 80:
				system("cls");
				red ();
				printf("down arrow");
				reset ();
				break;
		}
	}
	    
		
	
    

	}
}
