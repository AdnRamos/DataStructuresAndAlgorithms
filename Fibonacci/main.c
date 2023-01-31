#include <stdio.h>
#include <stdlib.h>
#include "funcaoFib.h"

int main (void){
  
  while(1){
    int numSequenciaFib, result = 0;

    printf("Deseja calcular qual número da sequencia de fibonacci:\n");
    scanf("%i", &numSequenciaFib);

    result = fibonacci(numSequenciaFib);

    printf("O %d termo da sequencia de fibonacci eh:%d\n", numSequenciaFib, result);

  }
   
    return 0;
}