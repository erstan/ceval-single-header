//lang=c
#include<stdio.h>
#include<stdlib.h>

#include "ceval.h"

int main(int argc, char ** argv) {
  char expr[100];
  while (1) {
    printf("In = ");
    fgets(expr, 100, stdin);
    if (!strcmp(expr, "exit\n")) {
      break;
    } else if (!strcmp(expr, "clear\n")) {
      system("clear");
      continue;
    } else {
      ceval_tree(expr);
      printf("\nOut = %f\n\n", ceval_result(expr));
    }
  }
  return 0;
}
