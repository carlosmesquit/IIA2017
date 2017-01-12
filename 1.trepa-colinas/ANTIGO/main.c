#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"
#include "algoritmo.h"

#define DEFAULT_RUNS 20
#define NUM_ITERACOES 100

int main()
{
	char nome_ficheiro[50];
	float *mat_adjacencias;
	int *solucao, *melhor_solucao;
	int fitness, melhor_fitness;
	int i, num_vertices=0;

	printf("Qual o Nome do Ficheiro?");
	gets(nome_ficheiro);

	// INICIALIZA O GERADOR DE N�MEROS ALEAT�RIOS
	init_rand();

	// PASSA DADOS DO FICHEIRO PARA A MATRIZ DE ADJAC�NCIAS
	mat_adjacencias = init_dados(nome_ficheiro, &num_vertices);

	// AlOCA MEM�RIA PARA SOLUC�O
	solucao = malloc(sizeof(int)*num_vertices);
    if (solucao == NULL)
	{
		printf("Erro na alocacao de memoria.\n");
		exit(1);
	}

	// AlOCA MEM�RIA PARA A MELHOR SOLUC�O
	melhor_solucao = malloc(sizeof(int)*num_vertices);
    if (melhor_solucao == NULL)
	{
		printf("Erro na alocacao de memoria.\n");
		exit(1);
	}

	// "ZERAR" AS MATRIZES
	memset(solucao, 0, sizeof(int)*num_vertices);
	memset(melhor_solucao, 0, sizeof(int)*num_vertices);

	for (i = 0; i<DEFAULT_RUNS; i++)
	{
		// GERAR SOLUCAO INICIAL
		gera_sol_inicial(solucao, num_vertices);

		// ALGORITMO TREPA COLINAS
		fitness = trepa_colinas(solucao, mat_adjacencias, num_vertices, NUM_ITERACOES);

		// MOSTRA RESULTADOS
		printf("Itera��o: %d\n", i+1);
		printf("Fitness: %d\n", fitness);
		escreve_sol(solucao, num_vertices);

		// SE ENCONTRA SOLUCAO MELHOR ACTUALIZA
		if (melhor_fitness<fitness || i==0 )
		{
			melhor_fitness= fitness;
			substitui(melhor_solucao, solucao, num_vertices);
		}
	}


    // APRESENTA A SOLUCAO
    printf("\nA melhor ");
	escreve_sol(melhor_solucao, num_vertices);

	// LIBERTAR MEM�RIA ALOCADA
	free(mat_adjacencias);
	free(solucao);
	free(melhor_solucao);

	return 0;
}
