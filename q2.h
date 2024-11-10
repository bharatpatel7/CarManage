#ifndef Q1_H
#define Q1_H

/*
We will be creating a stack to solve our problem
This stack will follow a linked list based approach
*/
typedef struct operand {
  double value;
  struct operand *next;
} Operand;



/* Function defintions for our stack */

void push(Operand ** stack ,double value);
double pop(Operand ** stack);
void print(Operand * stack);

#endif



