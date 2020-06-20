#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>

bool is_empty();
bool clear();
bool push(int value);
bool pop();
bool pop_aux();
node_ptr get_top();

typedef struct node{
	int data;
	struct node* previous;
} *node_ptr;

#endif __STACK_H__

