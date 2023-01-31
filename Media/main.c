#include <stdio.h>
//
typedef struct pessoas{
 char sexo;
 float altura;
}Pessoas;

//funcao p/ calcular altura geral
void altMedia(Pessoas *pess) {
  
	float media = 0;
	
	for(int i=0; i< 5; i++ ){
	  media += pess[i].altura;
	}
	media /= 5;

	printf("A altura media eh:_____________%.2f m\n", media);

}
//funcao p/ encontrar maior altura
void maiorAlt(Pessoas *pess) {
  
	float aux = 0;
	
	for (int i = 0; i < 5; i++) {
		if (aux <= pess[i].altura) {
			aux = pess[i].altura;
		};
	}
	
	printf("A maior altura eh:_____________%.2f m \n", aux);
}
//funcao p/ encontrar a altura media feminino e masculino
void mediaSex(Pessoas *pess) {

	float mediaMasc = 0, mediaFem = 0, totalMasc = 0, totalFem = 0;

	for (int i = 0; i < 5; i++) {
		if (pess[i].sexo == 'M') {
			mediaMasc += pess[i].altura;
			totalMasc++;
		} else if (pess[i].sexo == 'F') {
			mediaFem += pess[i].altura;
		}
	}
	totalFem = 5 - totalMasc;
	mediaMasc = mediaMasc / totalMasc;
	mediaFem = mediaFem / totalFem;

	printf(
		"A altura media masculina eh:___%.2f m\nA altura media feminina eh:____%.2f m\n",
		mediaMasc,
		mediaFem);
}
//funcao p/ encontrar a quantidade de homens
void quantMasc(Pessoas *pess) {
  
	float totalMasc = 0;

	for (int i = 0; i < 5; i++) {
		if (pess[i].sexo == 'M') {
			totalMasc++;
		};
	}
	printf("O numero total de homens eh:___%.2f\n", totalMasc);

}

int main(void) {
  
  //criacao do vetor  pessoa
	Pessoas nP[5];

  //preenchimento do veror
	nP[0].sexo = 'M';
	nP[0].altura = 1.70;
	nP[1].sexo = 'F';
	nP[1].altura = 1.68;
	nP[2].sexo = 'M';
	nP[2].altura = 1.80;
	nP[3].sexo = 'F';
	nP[3].altura = 1.75;
	nP[4].sexo = 'F';
	nP[4].altura = 1.60;
	
	altMedia(nP);
  maiorAlt(nP);
  mediaSex(nP);
  quantMasc(nP);
  nP[3].altura = 1.66;
	printf("_____________________________________\n");
  altMedia(nP);
  maiorAlt(nP);
	mediaSex(nP);

	return 0;
};