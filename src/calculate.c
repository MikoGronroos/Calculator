#include "stack.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double calculate(stack input){
   stack* output = allocateNewStack();
   for(int i = 0; i < input.count; i++){
      char* newChar = malloc(128*sizeof(char));
      if(input.stack[i]->type == Number){
         sprintf(newChar, "%s", input.stack[i]->input);
         add(output, newChar, Number);
      }else if(input.stack[i]->type == Sqrt){
         //double firstNumber = atof(pop(output)->input);
         //double sqrtValue = sqrt(firstNumber);
         //sprintf(newChar, "%f", sqrtValue);
         //add(output, newChar, Number);
      }else{
         double secondNumber = atof(pop(output)->input);
         double firstNumber = atof(pop(output)->input);
         if(input.stack[i]->type == Addition){
            double final = firstNumber + secondNumber;
            sprintf(newChar, "%f", final);
         }
         if(input.stack[i]->type == Substraction){
            double final = firstNumber - secondNumber;
            sprintf(newChar, "%f", final);
         }
         if(input.stack[i]->type == Multiplication){
            double final = firstNumber * secondNumber;
            sprintf(newChar, "%f", final);
         }
         if(input.stack[i]->type == Division){
            double final = firstNumber / secondNumber;
            sprintf(newChar, "%f", final);
         }
         if(input.stack[i]->type == Power){
            double final = pow(firstNumber, secondNumber);
            sprintf(newChar, "%f", final);
         }
         add(output, newChar, Number);
      }
   }
   double value = atof(output->stack[0]->input);
   return value;
}
