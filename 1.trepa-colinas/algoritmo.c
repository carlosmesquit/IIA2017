#include <stdio.h>
#include <stdlib.h>

#include "definicoes.h"
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

float trepa_colinas(int *sol, float *matriz, int n_elementos, int *m)
{
    int *nova_sol, i, m_novo;
	float fitness = 0, fitness_novo = 0;

    //  Alocar memória para a nova solução com o número máximo de n_elementosentos
    nova_sol = malloc(sizeof(int) * n_elementos);
    if (nova_sol == NULL)
    {
		printf("Erro na alocacao de memoria.\n");
		exit(1);
    }

    // Calcular fitness da solução inicial
    fitness = calcula_fit(sol, matriz, n_elementos, *m);

    for (i = 0; i < NUM_ITERACOES; i++) {
		// Gerar Solucao
		m_novo = gerar_solucao(nova_sol, n_elementos);
		fitness_novo = calcula_fit(nova_sol, matriz, n_elementos, m_novo);

		// Se a nova solução tiver melhor fitness
		if (fitness_novo >= 0 && fitness_novo > fitness)
		{
			fitness = fitness_novo;
			*m = m_novo;
			substitui(sol, nova_sol, m_novo);
		}
	}

    // LIBERTA MEMÓRIA ALOCADA
    free(nova_sol);

    return fitness;
}
