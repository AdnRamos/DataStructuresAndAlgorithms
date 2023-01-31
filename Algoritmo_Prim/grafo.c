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
	g->listaAdjacente = malloc(tamanho * sizeof(no_vertice));


	int i, j;
	//criação lista de adjacencia
	for(i = 0; i < tamanho; i++){
		g->listaAdjacente[i]= NULL;
	}

	return g;
}

no_vertice * novoVertice(int v, int peso){
	no_vertice * novo = malloc(sizeof(no_vertice));
	novo->vertice = v;
	novo->peso = peso;
	novo->prox = NULL;
	return novo;
}

void adicionarAresta(grafo *g, int v1, int v2, int peso){
	//Representação em lista de Adjacencia
	no_vertice * novo = novoVertice(v2, peso);
	novo->prox = g->listaAdjacente[v1];
	g->listaAdjacente[v1]= novo;
	
	novo = novoVertice(v1, peso);
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
			printf("-> %c%d", g->mapa[p->vertice], g->listaAdjacente[p->vertice]->peso);
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


//Algoritmo de Prim

heap * criarHeap(int capacidade){

	heap *novo = (heap*)malloc(sizeof(heap));
	novo->posicao=(int*)malloc(capacidade*sizeof(int));
	novo->tamanhoHeap =0;
	novo->capacidade = capacidade;
	novo->matriz = (noHeap **)malloc(capacidade*sizeof(noHeap));

	return novo;
}

noHeap * novoNoHeap(int v, int chave){

	noHeap * novo = (noHeap*)malloc(sizeof(noHeap));
	novo->v = v;
	novo->chave = chave;

	return novo;
}

void heapficar(heap *h, int indice){
	int menor, esq, dir;

	menor = indice;
	esq = 2*indice+1;
	dir = 2*indice+2;

	if(esq< h->tamanhoHeap && h->matriz[esq]->chave < h->matriz[menor]->chave){
		menor=esq;
	}else if(dir< h->tamanhoHeap && h->matriz[dir]->chave < h->matriz[menor]->chave){
		menor=dir;
	}

	if(menor != indice){
		noHeap *menorNo = h->matriz[menor];
		noHeap *indiceNo = h->matriz[indice];

		h->posicao[menorNo->v] = indice;
		h->posicao[indiceNo->v] = menor;

		trocar(&h->matriz[menor], &h->matriz[indice]);
		heapficar(h, menor);
	}
}

int vazio(heap *h){
	return h->tamanhoHeap == 0;
}

noHeap *retiraMenorNoHeap(heap *h){

	if(vazio(h)){
		return NULL;
	}
	noHeap *raiz = h->matriz[0];

	noHeap *ultimo = h->matriz[h->tamanhoHeap-1];
	h->matriz[0] = ultimo;

	h->posicao[raiz->v] = h->tamanhoHeap-1;
	h->posicao[ultimo->v] = 0;

	h->tamanhoHeap -= 1;
	heapficar(h, 0);

	return raiz;
}

void diminuirChave(heap *h, int v, int chave){
	int indice = h->posicao[v];
	h->matriz[indice]->chave = chave;

	while(indice && h->matriz[indice]->chave < h->matriz[(indice-1)/2]->chave){
		h->posicao[h->matriz[indice]->v]= (indice-1)/2;
		h->posicao[h->matriz[(indice - 1)/2]->v] = indice;
        trocar(&h->matriz[indice], &h->matriz[(indice-1)/2]);
        indice = (indice-1)/2;
	}
}

int existe(heap *h, int v){
    if(h->posicao[v] < h->tamanhoHeap){
        return 1;
    }else{
        return 0;
    }
}

void trocar(noHeap ** a, noHeap ** b){
    noHeap* aux = *a;
    *a = *b;
    *b = aux;
}

void imprimir(int *arr, int n, grafo *g){
    int i, peso, custo = 0;
    for(i=1; i<n; i++){
        peso = retornaPeso(g, arr[i], i);
        printf("%c - %c : %d\n", g->mapa[arr[i]], g->mapa[i], peso);
        custo += peso;
    }
}

void algoritmoPrim(grafo *g){

    int v = g->v;
    int pai[v];
    int chave[v];

    heap *h = criarHeap(v);

    int i;
    for(i=1; i<v; i++){
        pai[i]=-1;
        chave[i] = 9999999;
        h->matriz[i] = novoNoHeap(i, chave[i]);
        h->posicao[i] = i;
    }

    chave[0]=0;
    h->matriz[0] = novoNoHeap(0, chave[0]);
    h->posicao[0]=0;

    h->tamanhoHeap = v;

    while(!vazio(h)){
        noHeap* novo = retiraMenorNoHeap(h);
        int u = novo->v;

        no_vertice *p = g->listaAdjacente[u];
        while(p!=NULL){
            int i = p->vertice;

            if(existe(h, i) && p->peso < chave[i]){
                chave[i]=p->peso;
                pai[i]=u;
                diminuirChave(h, i, chave[i]);
            }
            p = p->prox;
        }
    }

    imprimir(pai, v, g);
}


int retornaPeso(grafo *g, int a, int b){
    no_vertice *aux = g->listaAdjacente[a];
    int peso =-1;
    while(aux!=NULL){
        if(aux->vertice == b){
            peso = aux->peso;
            break;
        }else{
            aux = aux->prox;
        }
    }
    return peso;
}

int main(int argc, int* argv) { 

	grafo * g;

	g = inicializarGrafo(g);


	algoritmoPrim(g);

	return 0;

}