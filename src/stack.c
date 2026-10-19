#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <string.h>

int add(stack* stack, char* input, type type){
   if(stack->count > 0){
      content** newptr= realloc(stack->stack, (1 + stack->count) * sizeof(content));
      stack->stack = newptr;
   }
   stack->stack[stack->count] = malloc(sizeof(content));
   stack->stack[stack->count]->type = type;
   strncpy(stack->stack[stack->count]->input, input, input_length-1);
   stack->count++;
   return 0;
}

content* pop(stack* stack){
   if(stack->count <= 0){
      return NULL;
   }
   stack->count--;
   content* newContent = stack->stack[stack->count];
   if(stack->count <= 0){
      freeStack(stack);
   }
   return newContent;
}
stack* allocateNewStack(){
   stack *newStack;
   newStack = malloc(sizeof(stack));
   newStack->stack = malloc(sizeof(content));
   newStack->count = 0;
   return newStack;
}
int freeStack(stack* target){
   free(target->stack);
}
