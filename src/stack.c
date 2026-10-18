#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int add(stack* stack, content* item){
   if(stack->count <= 0){
    stack->stack = malloc(2 * sizeof(content*));
   }else{
    content** newptr= realloc(stack->stack, (1 + stack->count) * sizeof(content*));
    stack->stack = newptr;
   }
   stack->count++;
   stack->stack[stack->count-1] = item;
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
