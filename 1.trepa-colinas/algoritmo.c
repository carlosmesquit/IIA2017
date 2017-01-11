#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

void repara(int *sol, int *mat, int vert)
{
	int i, j;
    float aux;

	for (i = 0; i < vert; i++)
        {
		for (j = 0; j < vert; j++)
		{
			if (i != j)
			{
				if (sol[i] == 1 && sol[j] == 1)
				{
					if (*((int *)mat + i * vert + j) != 1)
					{
						aux = random_l_h(0, 1);
						if (aux == 0)
						{
							sol[i] = 0;
						}
						else
						{
							sol[j] = 0;
						}
						i = j = 0;
					}
				}
			}
		}
	}
}

void gera_vizinho(int sol[], int vizinho[], int vert_tot)
{
	int i;
	int pos;

	for (i = 0; i<vert_tot; i++)
    {
		vizinho[i] = sol[i];
    }

	pos = random_l_h(0, vert_tot - 1);
	vizinho[pos] = !vizinho[pos];
}

int trepa_colinas(int sol[], int *mat, int vert, int num_iter)
{
	int *nova_sol, fitness=0, fitness_viz=0, i;

    // ALOCAR MEMÓRIA
	nova_sol = malloc(sizeof(int)*vert);
	// VERIFICA SE ALOCAÇÃO DE MEMORIA CORREU BEM
	if (nova_sol == NULL)
	{
		printf("Erro na alocacao de memoria");
		exit(1);
	}

	// CALCULA FITNESS DA SOLUCAO INICIAL
	fitness = calcula_fit(sol, mat, vert);

	for (i = 0; i < num_iter; i++) {
        //GERA VIZINHO
		gera_vizinho(sol, nova_sol, vert);
		// CALCULA FITNESS DO VIZINHO
		fitness_viz = calcula_fit(nova_sol, mat, vert);

		// TENTA REPARAR O VIZINHO SE O FITNESS FOR NEGATIVO
		if (fitness_viz < 0) {
			repara(nova_sol, mat, vert);
			fitness_viz = calcula_fit(nova_sol, mat, vert);
		}

		// SE O VIZINHO TIVER MELHOR FITNESS SUBSTITUI
		if (fitness_viz > fitness)
		{
			substitui(sol, nova_sol, vert);
			fitness = fitness_viz;
		}
	}

    // LIBERTA MEMÓRIA ALOCADA
	free(nova_sol);

	return fitness;
}
