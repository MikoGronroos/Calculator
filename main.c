#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include <string.h>

int main(void){
   stack* stack = allocateNewStack();
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
      }
   }
   return 0;
}
