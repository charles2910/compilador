// Font: https://github.com/rafaeltardivo/C-Stack
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

node_ptr top = NULL;
node_ptr top_aux = NULL;

node_ptr get_top(){
    return top;
}

bool is_empty(){
	return (top == NULL);
}

void display_top(){

	if(is_empty()){
		return;
	}

	printf("\n[%d]\n", top->data);
}

void display(){

	if(is_empty()){
		return;
	}

	node_ptr temp = top;

	printf("\n");

	while(temp != NULL){
		printf("\t[%d]\n", temp->data);
		temp = temp->previous;
	}
}

bool clear(){

	if(is_empty()){
		return false;
	}

	node_ptr current = top;
	node_ptr previous = NULL;

	while(current->previous != NULL){

		previous = current->previous;
		free(current);
		current = previous;
	}

	top = NULL;

}

bool push(int value){


	node_ptr item = (node_ptr) malloc(sizeof(struct node));

	if(item == NULL)
		return false;

	item->data = value;

	if(top == NULL)
		item->previous = NULL;
	else
		item->previous = top;

	top = item;
	top_aux = item;

	return true;

}

bool pop(){

	if(is_empty()){
		return false;
	}

	node_ptr temp = top;
	free(top);
	top = temp->previous;

	return true;

}

bool pop_aux(){

	if(is_empty()){
		return false;
	}

	node_ptr temp = top_aux;
	free(top_aux);
	top_aux = temp->previous;

	return true;

}