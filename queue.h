#include <stdio.h>
#include <stdlib.h>

struct Node{
    int answer;
    struct Node *next;
} *front, *rear;
typedef struct Node Node;

void free_answer(){
    Node *var = rear;
    while(var!=NULL){
        Node* buf = var->next;
		free(var);
		var = buf;
    }
    rear = NULL;
    front = NULL;
}

void add_answer(int random_answer){
    Node *temp;
    temp = (Node*)malloc(sizeof(Node));
    temp->answer = random_answer;
    if (front == NULL){
        front = temp;
        front->next = NULL;
        rear = front;
    }else{
        front->next = temp;
        front = temp;
        front->next = NULL;
    }
}

void display_answer(){
	printf("Key: ");
    Node *var = rear;
    if(var != NULL){
        while(var != NULL){
            printf("%d", var->answer);
            var = var->next;
        }
    }
}
