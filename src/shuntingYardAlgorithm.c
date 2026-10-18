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

int is_sign(char character){
   char all[] = {'^', '*', '/', '+', '-', '(', '9'};
   int value = 0;
   int count = 5;
   for(int i = 0; i < count; i++){
      if(character == all[i]){
         value = 1;  
      }
   }
   return value;
}

stack* tokenize(const char* input){
   stack* tokens = allocateNewStack();
   for(int i = 0; i < strlen(input); i++){
      if(is_sign(input[i]) == 1){
      
      }
   }
   
   return tokens;
}

stack* parse(const char* input){
   stack* output = allocateNewStack();
   stack* operators = allocateNewStack();
   stack* tokens = tokenize(input);
   for(int i = 0; i < strlen(input); i++){
      
   }
   free(tokens);
   free(operators);
   return output;
}
