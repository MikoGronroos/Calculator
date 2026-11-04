#include "stack.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "state.h"

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
   if(operator == UnaryMinus){
      return 3;
   }
   if(operator == UnaryMinusPow){
      return 6;
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
  if(type == UnaryMinus){
    return "right";
  }
  if(type == UnaryMinusPow){
    return "right";
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

type get_type(const char* input, int index){
   int val = -1;
   switch(input[index]){
      case '-':
         val = Substraction;
         if(index == 0){
            val = UnaryMinus;
         }
         if(index - 1 >= 0){
         char before = input[index-1];
            if(before != ')' && !isdigit(before)){
               val = UnaryMinus;
            }
            if(before == '^'){
               val = UnaryMinusPow;
            }
         }
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

int is_number(const char* input){
   int is = 1;
   for(int i = 0; i < strlen(input); i++){
      if(isdigit(input[i]) == 0){
         is = 0;
      }
   }
   return is;
}



void process_string(char* input, stack* tokens){
   if(is_number(input) == 1){
      add(tokens, input, Number);
   }else{
      if(strcmp(input, "ans") == 0){
         char str[128];
         sprintf(str, "%f", get_ans());
         int numberCount = 0;
         int length = strlen(str);
         for(int i = 0; i <= length; i++){
            int is_end = (i == length);
            if(is_end || is_sign(str, i) == 1){
               if(numberCount > 0){
                  char dest[length + 1];
                  strncpy(dest, str + i - numberCount, numberCount);
                  dest[numberCount] = '\0';
                  add(tokens, dest, Number);
                  numberCount = 0;
               }
               
               if(!is_end){
                  type fetch = get_type(str, i);
                  add(tokens, "empty", fetch);
               }
            }else{  
               numberCount++;
            }
         }
      }
   }
}



stack* tokenize(const char* input){
   stack* tokens = allocateNewStack();
   int numberCount = 0;
   int length = strlen(input);
   for(int i = 0; i <= length; i++){
      int is_end = (i == length);
      if(is_end || is_sign(input, i) == 1){
         if(numberCount > 0){
            char dest[length + 1];
            strncpy(dest, input + i - numberCount, numberCount);
            dest[numberCount] = '\0';
            process_string(dest, tokens);
            numberCount = 0;
         }
         
         if(!is_end){
            type fetch = get_type(input, i);
            add(tokens, "empty", fetch);
         }
      }else{
         numberCount++;
      }
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
