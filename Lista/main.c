#include <stdio.h>
#include <stdlib.h>

typedef struct list {
	int valor;
	struct list *prox;
} List;

List *inserir(List *lista, int v) {
	List *aux = lista;
	List *novo = (List *)malloc(sizeof(List));
	novo->valor = v;
	novo->prox = NULL;
	if (lista == NULL) {
		return novo;
	}
	while (aux->prox != NULL) {
		aux = aux->prox;
	}
	aux->prox = novo;
	return lista;
}

void exibir(List *lista) {
	List *aux = lista;
	while (aux != NULL) {
		printf("%d ", aux->valor);
		aux = aux->prox;
	}
	printf("\n");
}

List* inverter(List *lista1, List *lista2) {
  List *lista3= NULL;
	List *aux = lista2;
	List *temp = NULL;
	while (aux != NULL) {
		while (aux->prox != NULL) {
			temp = aux;
			aux = aux->prox;
		}
		lista3 = inserir(lista3, aux->valor);
		aux = lista2;
		if (temp != NULL) {
			temp->prox = NULL;
		} else {
			break;
		}
		temp = NULL;
	}
	aux = lista1;
	while (aux != NULL) {
		while (aux->prox != NULL) {
			temp = aux;
			aux = aux->prox;
		}
		lista3 = inserir(lista3, aux->valor);
		aux = lista1;
		if (temp != NULL) {
			temp->prox = NULL;
		} else {
			break;
		}
		temp = NULL;
	}
	return lista3;
}

void liberarMemoria(List *lista) {
	List *aux = lista;
	while (aux != NULL) {
		List *proximo = aux->prox;
		free(aux);
		aux = proximo;
	}
}

int main() {
	int opcao, v, escolha;
	List *lista1 = NULL;
	List *lista2 = NULL;
	List *listaC = NULL;

	printf("___________________________________________\n");
	printf("|                                          |\n");
	printf("|1. Inserir dados na lista 1               |\n");
	printf("|2. Inserir dados na lista 2               |\n");
	printf("|3. Exibir listas                          |\n");
	printf("|4. Inverter e concatenar listas           |\n");
	printf("|9. Encerrar programa                      |\n");
	printf("|__________________________________________|\n\n");
	do {
		printf("informe a opcao escolhida: ");
		scanf("%d", &opcao);
		switch (opcao) {
		case 1:
	  	printf("Digite o valor a ser inserido na lista 1:");
			scanf("%d", &v);
			lista1 = inserir(lista1, v);
			break;
		case 2:
			printf("Digite o valor a ser inserido na lista 2: ");
			scanf("%d", &v);
			lista2 = inserir(lista2, v);
			break;
		case 3:
			printf("Lista 1:\n");
			exibir(lista1);
			printf("Lista 2:\n");
			exibir(lista2);
			break;
		case 4:
			listaC=inverter(lista1, lista2);
			exibir(listaC);
			break;
	
		default:
			printf("Opcao invalida!!!\n");
		};
	} while (opcao != 9);
  liberarMemoria(lista1);
  liberarMemoria(lista2);
  liberarMemoria(listaC);
	return 0;
}