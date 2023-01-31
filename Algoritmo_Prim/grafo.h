#ifndef GRAFO_H
#define GRAFO_H


typedef struct noHeap{
    int v;
    int chave;
}noHeap;

typedef struct heap{
    int tamanhoHeap;
    int capacidade;
    int *posicao;
    noHeap ** matriz;
}heap;

typedef struct no_vertice{
    char *v;
    int vertice;
	int peso;
    struct no_vertice * prox;
}no_vertice;

typedef struct grafo {
	int v;
	int *cor;
	char *mapa;
    int *visitado;
	no_vertice ** listaAdjacente;
} grafo;



//grafo

grafo * criarGrafo(int tamanho);
no_vertice * novoVertice(int v, int peso);
void adicionarAresta(grafo *g, int v1, int v2, int peso);
void imprimirGrafo(grafo *g);
int indice(grafo *g, char c);
grafo * inicializarGrafo (grafo *g);
//DFS

heap * criarHeap(int capacidade);
noHeap * novoNoHeap(int v, int chave);
void trocar(noHeap ** a, noHeap ** b);
void heapficar(heap *h, int indice);
int vazio(heap *h);
noHeap * retiraMenorNoHeap(heap *h);
void diminuirChave(heap *h, int v, int chave);
int existe(heap *h, int v);
void imprimir(int *arr, int n, grafo *g);
void algoritmoPrim(grafo *g);
int retornaPeso(grafo *g, int a, int b);




#endif
