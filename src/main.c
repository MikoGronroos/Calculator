#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "shuntingYardAlgorithm.h"
#include <string.h>

int main(void){
   while(true){
      char buffer[128];
      if(fgets(buffer, sizeof(buffer), stdin)){
         if (strchr(buffer, '\n') == NULL) {
           int c;
           while ((c = getchar()) != '\n' && c != EOF) {
           }
         }else{
           buffer[strlen(buffer)-1] = '\0';
         }
         stack* output = parse(buffer);
         free(output);
      }
   }
   return 0;
}
