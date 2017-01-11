#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"

int calcula_fit(int sol[], int *mat, int vert)
{
	int i, j, ligados=0, nao_ligados=0, fitness=0;

	for (i = 0; i < vert; i++)
    {
		for (j = 0; j < vert; j++)
    {
			if (i != j)
			{
				if (sol[i] == 1 && sol[j] == 1)
				{
					if (*((int *)mat + i * vert + j) == 1)
					{
						ligados++;
					}
					else
					{
						nao_ligados++;
					}
				}
			}
		}
	}

	if (nao_ligados > 0) // SE HOUVER NÃO LIGADOS
    {
		fitness -= nao_ligados/2;
	}
	else // SE NÃO
	{
		fitness += ligados/2;
	}
	return fitness;
}
