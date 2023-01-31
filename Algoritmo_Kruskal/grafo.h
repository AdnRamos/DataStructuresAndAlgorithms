#ifndef GRAFO_H
#define GRAFO_H


typedef struct aresta{
	char u;
	char v;
	int peso;
}aresta;


typedef struct listaAresta{
	aresta arestas[100];
	int quantidade;
}listaAresta;


typedef struct grafo {
	int v;
	int *cor;
	char *mapa;
	int **matriz;
} grafo;



//grafo

grafo * criarGrafo(int tamanho);
void adicionarAresta(grafo *g, int v1, int v2, int peso);
void imprimirGrafo(grafo *g);
int indice(grafo *g, char c);
grafo * inicializarGrafo (grafo *g);
//DFS

void sort(listaAresta *l);
int busca(int pertence[], int v);
void uniao(grafo *g, int *pertence, int v1, int v2);
void algoritmoKruskal(grafo *g);

#endif
