#include "q2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_oparator(char c);
double perform_operation(double a, double b, char oprator);

int main(int argc, char** argv){

  //Pointer to the stack
  Operand * stack = NULL;

  if(argc != 2){
    printf("Usage: %s <operands>\n", argv[0]);
    return 1;
  }
  //Loop through the second command line arguement, containing the operands and the numbers 
  for (int i = 0; i < strlen(argv[1]); ++i){
    char current_cahr = argv[1][i];

    if (isdigit(current_cahr)){
      double num = current_cahr - '0';
      push(&stack, num);
    }
    else if (is_oparator(current_cahr)){
      if(stack == NULL || stack->next == NULL){
        printf("Invalid input\n");
        return 1;
      }

      double b = pop(&stack);
      double a = pop(&stack);
      double result = perform_operation(a, b, current_cahr);
      push(&stack, result);
    }
  }

  //After the Expression
  if(stack != NULL && stack->next == NULL){
    double result = pop(&stack);
    printf("Result: %.2f\n", result);
  }
  else{
    printf("Invalid input\n");
  }

  return 0;
}

int is_oparator(char c){
  return c == '+' || c == '-' || c == '*' || c == '/';
}

double perform_operation(double a, double b, char oprator){
  switch(oprator){
    case '+':
      return a + b;
    case '-':
      return a - b;
    case '*':
      return a * b;
    case '/':
      if (b == 0){
        printf("Invalid input\n");
        exit(1);
      }
      return a / b;

    default:
      printf("Invalid input\n");
      exit(1);
  }
}

