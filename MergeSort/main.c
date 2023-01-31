#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char cidade[20];
} Cidades;

void Merge(Cidades *V, int left, int middle, int right) {
	int vL = middle - left + 1;
	int vR = right - middle;

	char **L = malloc(sizeof(char *) * vL);
	char **R = malloc(sizeof(char *) * vR);
	int i;
	for (i = 0; i < vL; i++) {
		L[i] = malloc(sizeof(V[left + i]));
		strcpy(L[i], V[left + i].cidade);
	}
	for (i = 0; i < vR; i++) {
		R[i] = malloc(sizeof(V[middle + i + 1]));
		strcpy(R[i], V[middle + i + 1].cidade);
	}
	int j = 0, k;
	i = 0;
	k = left;
	while (i < vL && j < vR) {
		if (strcmp(L[i], R[j]) > 0) {
			strcpy(V[k++].cidade, L[i++]);
		} else {
			strcpy(V[k++].cidade, R[j++]);
		}
	}
	while (i < vL) {
		strcpy(V[k++].cidade, L[i++]);
	}
	while (j < vR) {
		strcpy(V[k++].cidade, R[j++]);
	}
}

void MergeSort(Cidades *V, int left, int right) {
	if (left < right) {
		int middle = (left + right) / 2;
		MergeSort(V, left, middle);
		MergeSort(V, middle + 1, right);
		Merge(V, left, middle, right);
	}
}
void convert(Cidades *cidades) {
	int i = 0, j = 0;

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j <= strlen(cidades[i].cidade); j++) {
			if (cidades[i].cidade[j] >= 'A' && cidades[i].cidade[j] <= 'Z') {
				cidades[i].cidade[j] += 32;
			}
		}
	}
}

int main() {
	int left = 0, right = 19;
	Cidades cidades[20];

	strcpy(cidades[0].cidade, "Sao Paulo");
	strcpy(cidades[1].cidade, "Rio de Janeiro");
	strcpy(cidades[2].cidade, "Brasilia");
	strcpy(cidades[3].cidade, "Salvador");
	strcpy(cidades[4].cidade, "Fortaleza");
	strcpy(cidades[5].cidade, "Belo Horizonte");
	strcpy(cidades[6].cidade, "Manaus");
	strcpy(cidades[7].cidade, "Curitiba");
	strcpy(cidades[8].cidade, "Recife");
	strcpy(cidades[9].cidade, "Goiania");
	strcpy(cidades[10].cidade, "Belem");
	strcpy(cidades[11].cidade, "Porto Alegre");
	strcpy(cidades[12].cidade, "Campinas");
	strcpy(cidades[13].cidade, "Sao Luis");
	strcpy(cidades[14].cidade, "São Goncalo");
	strcpy(cidades[15].cidade, "Maceio");
	strcpy(cidades[16].cidade, "Duque de Caxias");
	strcpy(cidades[17].cidade, "Campo Grande");
	strcpy(cidades[18].cidade, "Natal");
	strcpy(cidades[19].cidade, "Teresina");

	convert(cidades);
	MergeSort(cidades, left, right);

	for (int i = 0; i < 20; i++) {
		printf("%d - %s\n", i, cidades[i].cidade);
	}
	return 0;
}