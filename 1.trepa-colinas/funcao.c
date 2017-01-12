#include <stdio.h>
#include <stdlib.h>

#include "funcao.h"

float calcula_fit(int *sol, float *matriz, int n_elementos, int m)
{
	int i, j, origem, destino;
	float fitness = 0, temp, res;

	for(i = 0; i < m - 1; i++) {
		for (j = i + 1; j < m; j++) {	
			temp = *(matriz + sol[j] + sol[i] * n_elementos);
			printf("%d %d %f\n", sol[i]+1, sol[j]+1, temp);
			fitness += temp;
		}
	}

	res = fitness / m;

	if(fitness != 0)
		return res;

	return 0;
}