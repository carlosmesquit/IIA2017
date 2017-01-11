#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"

int calcula_fit(int sol[], int *mat, int vert);

// Calcula a qualidade de uma solucao
// Recebe: solucao, matriz, numero de vertices
// Devolve a qualidade
int calcula_fit(int sol[], int *mat, int vert)
{
	int correctas, erradas, qualidade;
	int i, j;

	correctas = erradas = qualidade = 0;

	for (i = 0; i < vert; i++) {
		for (j = 0; j < vert; j++) {
			if (i != j) {
				if (sol[i] == 1 && sol[j] == 1){
					if (*((int *)mat + i * vert + j) == 1) {
						correctas++;
					}
					else{
						erradas++;
					}
				}
			}
		}
	}

	if (erradas > 0) {
		qualidade -= erradas/2;
	}
	else {
		qualidade += correctas/2;
	}

	//É feita a divisão por 2 porque para cada aresta o algoritmo encontra duas soluções, Ex: {1,2} & {2,1}
	//qualidade = (correctas /2) - (erradas /2)*vert;

	return qualidade;
}