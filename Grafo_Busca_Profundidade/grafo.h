#ifndef GRAFO_H
#define GRAFO_H

enum cor {branco, cinza, preto};


typedef struct no_vertice{
    char *v;
    int vertice;
    struct no_vertice * prox;
}no_vertice;

typedef struct grafo {
	int v;
	char *mapa;
	int *cor;
	no_vertice ** listaAdjacente;
} grafo;


//grafo

grafo * criarGrafo(int tamanho);
no_vertice * novoVertice(int v);
void adicionarAresta(grafo *g, int v1, int v2);
void imprimirGrafo(grafo *g );
int indice(grafo *g, char c);
grafo * inicializarGrafo (grafo *g);

//DFS

void auxiliarBuscaProfundidade(grafo *g, char v);
void buscaProfundidade(grafo *g, int v);


#endif
