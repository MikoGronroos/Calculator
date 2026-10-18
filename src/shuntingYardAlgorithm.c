#include "stack.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int getPrecedence(char operator){
  if(operator == '^'){
    return 5;
  }
  if(operator == 's'){
    return 4;
  }
  if(operator == '*'){
    return 3;
  }
  if(operator == '/'){
    return 3;
  }
  if(operator == '+'){
    return 2;
  }
  if(operator == '-'){
    return 2;
  }
  return 0;
}

char* getAssociativity(char operator){
  if(operator == '^'){
    return "right";
  }
  if(operator == 's'){
    return "left";
  }
  if(operator == '*'){
    return "left";
  }
  if(operator == '/'){
    return "left";
  }
  if(operator == '+'){
    return "left";
  }
  if(operator == '-'){
    return "left";
  }
  return "none";

}

int is_sign(const char* input, int index){
   int length = strlen(input);
   char all[] = {'^', '*', '/', '+', '-', '(', ')'};
   int value = 0;
   int count = 7;
   for(int i = 0; i < count; i++){
      if(input[index] == all[i]){
         value = 1;
      }
   }
   if(value == 1){
      if(input[index] == '-'){
         if(index == 0){
            value = 0;
         }
         if(index - 1 > 0){
            char before = input[index-1];
            if(before != ')' && !isdigit(before)){
               value = 0;
            }
         }
      }
   }
   return value;
}

type get_type(char character){
   int val = -1;
   switch(character){
      case '-':
         val = Substraction;
         break;
      case '+':
         val = Addition;
         break;
      case '*':
         val = Multiplication;
         break;
      case '/':
         val = Division;
         break;
      case 's':
         val = Sqrt;
         break;
      case '^':
         val = Power;
         break;
   }
   return val;
}

stack* tokenize(const char* input){
   stack* tokens = allocateNewStack();
   for(int i = 0; i < strlen(input); i++){
      if(is_sign(input, i) == 1){
         content* new = malloc(sizeof(content));
         new->type = get_type(input[i]);
         add(tokens, new);
      }else{
         printf("No sign\n");   
      }
   }
   
   return tokens;
}

stack* parse(const char* input){
   stack* output = allocateNewStack();
   stack* operators = allocateNewStack();
   stack* tokens = tokenize(input);
   for(int i = 0; i < tokens->count; i++){
      printf("%d\n", tokens->stack[i]->type); 
   }
   return output;
}
