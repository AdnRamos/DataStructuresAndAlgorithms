#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

//fila


int vazio(fila *f){
	if(f->frente == -1 || f->frente > f->tras){
		return 1;
	}else{
		return 0;
	}
}

fila * criarFila(int tamanho){
	fila *f = malloc(sizeof(fila));
	f->itens = malloc(sizeof(int)*(tamanho*10));
	f->frente = -1;
	f->tras = -1;
	f->tamanhoFila = tamanho*10;

	for(int i=0; i< f->tamanhoFila; i++){
		f->itens[i] = 0;
	}
	return f;
}

void enfileirar(fila *f, int valor){
	if(f->tras == f->tamanhoFila-1){
		printf("Overflow da fila\n");
	}else{
		if(f->frente == -1){
			f->frente = 0;
		}
		f->tras++;
		f->itens[f->tras] = valor;
	}
}

int desenfileirar(fila *f){
	int retirar;

	if(vazio(f)){
		printf("Underflow da fila\n");
		exit(1);
	}
	retirar = f->itens[f->frente];
	f->frente++;
	
	return retirar;
}

void imprimirFila(fila *f, grafo *g){
	int i = f->frente;

	if(vazio(f)){
		printf("fila vazia\n");
	}else{
		printf("fila: ");
		for(i = f->frente; i<f->tras+1; i++){
			printf("%c ", g->mapa[f->itens[i]]);
		}
		printf("\n");
	}
}

//grafo

grafo * criarGrafo(int tamanho){
	grafo *g = malloc(sizeof(grafo));
	g->v = tamanho;
	g->mapa = (char *) malloc(sizeof(char)*tamanho);
	g->matriz = (int **) malloc(sizeof(int *)*tamanho);
	g->cor = malloc(sizeof(int)*(tamanho+1));

	int i, j;	

	//criação matriz
	for(i = 0; i < tamanho; i++){
		g->matriz[i] = (int *) malloc(sizeof(int)*tamanho);
		g->cor[i] = branco;
	}
	g->cor [tamanho] = branco;

	for(i = 0; i<tamanho; i++){
		for(j=0; j<tamanho;j++){
			if(i==j){
				g->matriz[i][j] = 1;
			}else{
				g->matriz[i][j] = 0;
			}
		}
	}
	return g;
}


void adicionarAresta(grafo *g, int v1, int v2){

	//Representação matricial
	g->matriz[v1][v2] = 1;
	g->matriz[v2][v1] = 1;
}

void imprimirGrafo(grafo *g){
	int i, j;

	printf("Representação matricial\n");

	for(i=0; i<g->v; i++){
		if(i==0){
			printf(" ");
		}
		printf(" %c", g->mapa[i]);
	}
	printf("\n");

	for(i=0; i<g->v; i++){
		printf("%c ", g->mapa[i]);
		for(j=0; j<g->v; j++){
			printf("%d ", g->matriz[i][j]);
		}
		printf("\n");
		
	}

}

int indice(grafo *g, char c){
    int i;
    for(i=0; i<g->v; i++){
        if(c == g->mapa[i]){
            return i;
        }
    }
    return -1;
}

grafo * inicializarGrafo (grafo *g) {
	FILE *input;
	input = fopen("entrada.txt", "r");

	int vertices, arestas, i;
	char aresta1, aresta2, c;

	fscanf(input, "%d %d", &vertices, &arestas);
	
	g = criarGrafo(vertices);

	for(i = 0; i<vertices; i++){
		c=fgetc(input);
		g->mapa[i] = fgetc(input);
	}

	for(i = 0; i<arestas; i++){
		c = fgetc(input);
		aresta1 = fgetc(input);
		aresta2 = fgetc(input);
		adicionarAresta(g, indice(g, aresta1), indice(g, aresta2));
	}
	fclose(input);
	return g;
}


//busca largura

void auxiliarBuscaLargura(char v, fila *f, grafo *g){
	int vertice = indice(g, v);
	if(vertice == -1){
		printf("Este vertice não existe\n");
	}else{
		buscaLargura(vertice, f, g);
	}
}

void buscaLargura(int v, fila *f, grafo *g){

	enfileirar(f, v);
	g->cor[v] = cinza;

	printf("Busca em largura a partir de: %c\n", g->mapa[v]);

	int i;
	imprimirFila(f, g);
	while(!vazio(f)){
		v = desenfileirar(f);
		g->cor[v] = preto;
		printf("visitado: %c\n", g->mapa[v]);


		for(i = 0; i<g->v; i++){
			if(g->matriz[v][i] == 1 && g->cor[i] == branco){
				enfileirar(f, i);
				g->cor[i] = cinza;
			}
		}
		imprimirFila(f, g);
	}
	printf("\n");
}

int main(int argc, int* argv) {
	grafo * g;
	fila * f;

	g = inicializarGrafo(g);
	f = criarFila(g->v);

	imprimirGrafo(g);

	auxiliarBuscaLargura('R', f, g);

	return 0;

}