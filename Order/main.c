#include <stdio.h>
#include <stdlib.h>

 
      
void fillVet (int* vetNumb){
  for( int i = 0; i <10; i++ ){
    vetNumb[i] = rand()%100;
  }
}

void order(int*vet, int* vetAux){
 
  int auxBigger = vet[0], auxSmaller = vet[0];

  for(int i = 0, j= 10; i < 10; i++, j--){ // for para encontrar o maior e o menor numero 

    if(vet[i] >= auxBigger){//condição de maior numero
      auxBigger = vet[i];//armazenando o maior valor do vetor para o auxBigger
        
    }
    if(vet[j] < auxSmaller && vet[j] != 0){//condição de menor numero
      auxSmaller = vet[j];// armazenando o menor valor do vetor em auxSmaller 
    }
  } 
  printf("%d e %d", auxBigger, auxSmaller);
  for(int j = 0; j<10;j++){//retirar o maior valor
    if(vet[j] == auxBigger){
      for(int start =0; start<=5; start++){//percorre as 5 primeiras posições do vetor
        if(vetAux[start] == 0){//verifica se a posição do vetor auxiliar esta livre
          vetAux[start] = auxBigger;//insere o valor na posição
          start =5;//encerra o loop para não preencher o restane do vetor com o mesmo numero
        }
      }
      vet[j] =0; //retira o maior numero do vetor principal 
    }
    if(vet[j] == auxSmaller){//retirar o menor valor
      for(int end =10; end>=5; end--){//percorre as 5 ultimas possições do vetor
        if(vetAux[end] == 0){//verifica se a posição do vetor auxiliar esta disponivel
          vetAux[end] = auxSmaller;//insere o menor valor
          end =5;//encerra o loop para não preencher o restante do vetor com o mesmo numero
        }
      }
      vet[j] = 0; //retira o menor numero do vetor principal
      
    }
  }
}
void orderSort(int *vet, int *vetAux){//meta era deixar a função recursiva mas meu cerebro bugou
  for(int i=0; i<=5 ;i++){//como pegar o maior e o menor numero de uma vez o numero de repetição eh divido por 2
        order(vet, vetAux);//chama a função que separa e insere
        if(vetAux[i] == 0){//verifica se tem algum espaço que contenha 0
          order(vet, vetAux);//continua chamando até o vetor está todo ordenado
        }
      }
}
void toRemove (int * vet, int value){//remove e ordena 
  int temp = 0;
  for(int i= 0; i<10; i++){//repetição do tamanho do vetor 
    if(vet[i] == value){ //verifica o valor a ser retirado
      vet[i] = 0;//insere o 0 na posição do valor
      int j = i;//assumo j como posição do valor para reorganizar
      while(j <9){
        temp = vet[j+1];//o valor do próximo eh inserido no temp
        vet[j] = temp;//passo o valor do próximo para o atual
        vet[j+1] = 0;//e assumo que o valor do proximo é 0
        j++;
      };//enquanto não chegar no final do vetor
      i=10;
    }
  }
}

int main() {
  int vet[10], vetAux[10], option, remove;
   for( int i = 0; i <10; i++ ){
    vetAux[i] = 0;
  }

  fillVet(vet);
  orderSort(vet, vetAux);

	printf("______________________________\n");
	printf("|                             |\n");
	printf("|1. Exibir                    |\n");
	printf("|2. Remover elemento          |\n");
	printf("|9. Encerrar programa         |\n");
	printf("|_____________________________|\n\n");


	do {
		printf("informe a opcao escolhida: ");

		scanf("%d", &option);
    printf("\n");

		switch (option) {
		case 1:
      for(int i= 0; i<10; i++){
        printf("%d ", vetAux[i]);
      }
      printf("\n\n\n");

	  	
			break;
		case 2:
			printf("Digite o valor a ser removido: ");
      scanf("%d", &remove);
      toRemove(vetAux, remove);
      printf("\n\n\n");

				break;
	
		default:
			printf("Opcao invalida!!!\n");
		};
	} while (option != 9);
  
	return 0;
}