#ifndef GRAFO_H
#define GRAFO_H

enum cor {branco, cinza, preto};

typedef struct fila{
    int tamanhoFila;
    int *itens;
    int frente;
    int tras;
}fila;

typedef struct grafo {
	int v;
	char *mapa;
	int *cor;
	int **matriz;
} grafo;

//fila

fila * criarFila(int tamanho);
void enfileirar(fila *f, int valor);
int desenfileirar(fila *f);
void imprimirFila(fila *f, grafo *g);
int vazio(fila *f);



//grafo

grafo * criarGrafo(int tamanho);
void adicionarAresta(grafo *g, int v1, int v2);
void imprimirGrafo(grafo *g );
int indice(grafo *g, char c);
grafo * inicializarGrafo (grafo *g);

//BFS
void auxiliarBuscaLargura(char v, fila *f, grafo*g);
void buscaLargura(int v, fila *f, grafo *g);


#endif
