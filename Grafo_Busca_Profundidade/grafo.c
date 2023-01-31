#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

//grafo

grafo * criarGrafo(int tamanho){
	grafo *g = malloc(sizeof(grafo));
	g->v = tamanho;
	g->mapa = (char *) malloc(sizeof(char)*tamanho);
	g->listaAdjacente = malloc(tamanho*sizeof(no_vertice));
	g->cor = malloc(tamanho*sizeof(no_vertice));

	int i;
	//criação lista de adjacencia
	for(i = 0; i < tamanho; i++){
		g->listaAdjacente[i]= NULL;
		g->cor[i]=branco;
	}
	g->cor [tamanho] = branco;

	return g;
}

no_vertice * novoVertice(int v){
	no_vertice * novo = malloc(sizeof(no_vertice));
	novo->vertice = v;
	novo->prox = NULL;
	return novo;
}

void adicionarAresta(grafo *g, int v1, int v2){
	//Representação em lista de Adjacencia
	no_vertice * novo = novoVertice(v2);
	novo->prox = g->listaAdjacente[v1];
	g->listaAdjacente[v1]= novo;
	
	novo = novoVertice(v1);
	novo->prox = g->listaAdjacente[v2];
	g->listaAdjacente[v2]= novo;	

}

void imprimirGrafo(grafo *g){
	int i;

	
	printf("Representação lista de adjacencia\n");
	for(i = 0; i<g->v;i++){
		no_vertice * p = g->listaAdjacente[i];
		printf("%c", g->mapa[i]);
		while(p != NULL){
			printf("-> %c", g->mapa[p->vertice]);
			p=p->prox;
		}
        printf("\n");
    }
    printf("\n");

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


//busca profundidade

void auxiliarBuscaProfundidade(grafo *g, char v){
	int vertice = indice(g, v);
	if(vertice == -1){
		printf("Este vertice nao existe\n");
	}else{
		printf("Busca em profundidade a partir de: %c\n", g->mapa[vertice]);
		buscaProfundidade(g, vertice);
	}
}

void buscaProfundidade(grafo *g, int v){
	no_vertice * listaAdjacente = g->listaAdjacente[v];
	no_vertice * temp = listaAdjacente;
	
	g->cor[v] = cinza;
	printf("Visitados %c\n", g->mapa[v]);//Parar representar o vertice como char utilizamos %c caso queiramos representar como numero utilziarmos o %d

	while(temp!=NULL){
		int verticeLigacao = temp->vertice;
		if(g->cor[verticeLigacao]==branco){
			buscaProfundidade(g, verticeLigacao);
		}
		temp = temp->prox;
	}
	g->cor[v]=preto;
}

int main(int argc, int* argv) { 
	grafo * g;

	g = inicializarGrafo(g);

	imprimirGrafo(g);

	auxiliarBuscaProfundidade(g, 'R');

	return 0;

}