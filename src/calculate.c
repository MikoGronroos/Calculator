#include "stack.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double calculate(stack input){
   stack* output = allocateNewStack();
   for(int i = 0; i < input.count; i++){
      char* newChar = malloc(32);
      double secondNumber = 0;
      double firstNumber = 0;
      switch(input.stack[i]->type){
         case Number:
            sprintf(newChar, "%s", input.stack[i]->input);
            break;
         case UnaryMinusPow:
         case UnaryMinus:
            double number = atof(pop(output)->input);
            number *= -1;
            sprintf(newChar, "%f", number);
            break;
         case Addition:
            secondNumber = atof(pop(output)->input);
            firstNumber = atof(pop(output)->input);
            sprintf(newChar, "%f", firstNumber + secondNumber);
            break;
         case Substraction:
            secondNumber = atof(pop(output)->input);
            firstNumber = atof(pop(output)->input);
            sprintf(newChar, "%f", firstNumber - secondNumber);
            break;
         case Multiplication:
            secondNumber = atof(pop(output)->input);
            firstNumber = atof(pop(output)->input);
            sprintf(newChar, "%f", firstNumber * secondNumber);
            break;
         case Division:
            secondNumber = atof(pop(output)->input);
            firstNumber = atof(pop(output)->input);
            sprintf(newChar, "%f", firstNumber / secondNumber);
            break;
         case Power:
            secondNumber = atof(pop(output)->input);
            firstNumber = atof(pop(output)->input);
            sprintf(newChar, "%f",pow(firstNumber, secondNumber));
            break;
      }
      add(output, newChar, Number);
   }
   double value = atof(output->stack[0]->input);
   return value;
}
