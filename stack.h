#ifndef __stack_H__
#define __stack_H__

struct StackNode { 
    int data; 
    struct StackNode* next; 
}; 
  
struct StackNode* newNode(int data);
int isEmpty(struct StackNode* root);
void push(struct StackNode** root, int data);
int pop(struct StackNode** root);
struct StackNode* peek(struct StackNode* root);

#endif __stack_H__

