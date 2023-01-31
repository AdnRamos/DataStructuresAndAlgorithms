#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

//grafo

grafo * criarGrafo(int tamanho){
	grafo *g = malloc(sizeof(grafo));
	g->v = tamanho;
	g->mapa = (char *) malloc(sizeof(char)*tamanho);
	g->matriz = (int **) malloc(sizeof(int *)*tamanho);
	int i, j;
	//criação matriz
	for(i = 0; i < tamanho; i++){
		g->matriz[i] = (int *) malloc(sizeof(int)*tamanho);
	}
	for(i = 0; i<tamanho; i++){
		for(j=0; j<tamanho;j++){
			g->matriz[i][j] = 0;
		}
	}
	return g;
}



void adicionarAresta(grafo *g, int v1, int v2, int peso){

	//Representação matricial
	g->matriz[v1][v2] = peso;
	g->matriz[v2][v1] = peso;
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

	int vertices, arestas, i, peso;
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
		fscanf(input, " %d", &peso);
		adicionarAresta(g, indice(g, aresta1), indice(g, aresta2), peso);
	}
	fclose(input);
	return g;
}


//Algoritmo de Kruske

void sort(listaAresta *l){
	int i, j;
	aresta aux;

	for(i=1; i<l->quantidade-1;i++){
		for(j=0; j<l->quantidade; j++){
			if(l->arestas[j].peso > l->arestas[j+1].peso){
				aux = l->arestas[j];
				l->arestas[j] = l->arestas[j+1];
				l->arestas[j+1] = aux;
			}
		}
	}
}

int busca (int pertence[], int v){
	return pertence[v];
}

void uniao(grafo *g, int *pertence, int v1, int v2){
	int i;
	for(i=0; i<g->v; i++){
		if(pertence[i] == v2){
			pertence[i] = v1;
		}
	}

}

void algoritmoKruskal(grafo *g){

	int pertence[g->v];
	int i, j, v1, v2, v3, v4;
	aresta aux;

	listaAresta *lista = (listaAresta*)malloc(sizeof(listaAresta));
	listaAresta *la = (listaAresta*)malloc(sizeof(listaAresta));

	lista->quantidade = 0;
	la->quantidade = 0;

	for(i = 1; i<g->v;i++){
		for(j=0; j<i; j++){
			if(g->matriz[i][j] != 0){
				aux.peso = g->matriz[i][j];
				aux.u = g->mapa[i];
				aux.v = g->mapa[j];
				lista->arestas[lista->quantidade] = aux;
				lista->quantidade++;
			}
		}
	}
	sort(lista);

	for(i = 0; i<g->v; i++){
		for(j = 0;j<g->v; j++){
			g->matriz[i][j] = 0;
			g->matriz[j][i] = 0;
		}
	}
	for(i = 0; i<g->v; i++){
		pertence[i] = i;
	}

	for(i = 0; i<lista->quantidade; i++){
		v1 = indice(g, lista->arestas[i].u);
		v2 = indice(g, lista->arestas[i].v);
		v3 = busca(pertence, v1);
		v4 = busca(pertence, v2);
		if(v3 != v4){
			adicionarAresta(g, v1, v2, lista->arestas[i].peso);
			la->arestas[la->quantidade] = lista->arestas[i];
			la->quantidade = la->quantidade+1;
			uniao(g, pertence, v3, v4);
		}
	}
	imprimirGrafo(g);
	
}

int main(int argc, int* argv) { 
	grafo * g;

	g = inicializarGrafo(g);


	algoritmoKruskal(g);

	return 0;

}