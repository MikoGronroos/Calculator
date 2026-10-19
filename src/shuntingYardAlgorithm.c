#include "stack.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int getPrecedence(type operator){
  if(operator == Power){
    return 5;
  }
  if(operator == Sqrt){
    return 4;
  }
  if(operator == Multiplication){
    return 3;
  }
  if(operator == Division){
    return 3;
  }
  if(operator == Addition){
    return 2;
  }
  if(operator == Substraction){
    return 2;
  }
  return 0;
}

char* getAssociativity(type type){
  if(type == Power){
    return "right";
  }
  if(type == Sqrt){
    return "left";
  }
  if(type == Multiplication){
    return "left";
  }
  if(type == Division){
    return "left";
  }
  if(type == Addition){
    return "left";
  }
  if(type == Substraction){
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
      case '(':
         val = LBracket;
         break;
      case ')':
         val = RBracket;
         break;
   }
   return val;
}

stack* tokenize(const char* input){
   stack* tokens = allocateNewStack();
   int numberCount = 0;
   int length = strlen(input);
   for(int i = 0; i < length; i++){
      if(is_sign(input, i) == 1){
         if(numberCount > 0){
            char dest[input_length];
            strncpy(dest, input + i - numberCount, numberCount);
            dest[numberCount] = '\0';
            add(tokens, dest, Number);
         }
         add(tokens, "empty", get_type(input[i]));
         numberCount = 0;
      }else{
         numberCount++; 
      }
   }
   if(numberCount > 0){
      char dest[input_length];
      strncpy(dest, input + length - numberCount, numberCount);
      dest[numberCount] = '\0';
      add(tokens, dest, Number);
   }
   return tokens;
}

stack* parse(const char* input){
   stack* output = allocateNewStack();
   stack* operators = allocateNewStack();
   stack* tokens = tokenize(input);
   for(int i = 0; i < tokens->count; i++){
      content item = *tokens->stack[i];
      if(item.type == Number){
         add(output, item.input, item.type);
      } else if(item.type != Number && item.type != LBracket && item.type != RBracket){
         if(operators->count >= 1){
            while(operators->stack[operators->count-1]->type != LBracket && (getPrecedence(operators->stack[operators->count-1]->type) > getPrecedence(item.type) || (getPrecedence(operators->stack[operators->count-1]->type) == getPrecedence(item.type) && getAssociativity(item.type) == "left"))){
               content* new = pop(operators);
               add(output, new->input, new->type); 
               break;        
            }
         }
         add(operators, item.input, item.type); 
      }else if(item.type != Number && item.type == LBracket){
         add(operators, item.input, item.type); 
      }else if(item.type != Number && item.type == RBracket){
         while(true){
            content* new = pop(operators);
            if(new->type != LBracket){
               add(output, new->input, new->type);
            }else{
               break;
            }
         }
      }
   }
   while(operators->count > 0){
      content* new = pop(operators);
      add(output, new->input, new->type);
   }
   return output;
}
