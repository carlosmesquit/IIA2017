#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"
#include "algoritmo.h"

#define DEFAULT_RUNS 20

int main()
{
	char nome_ficheiro[50];
	int *mat_adjacencias;
	int *solucao, *melhor_solucao;
	int fitness, melhor_fitness;
	int num_iteracoes=100; // IR ALTERANDO
	int i, num_vertices;

	printf("Qual o Nome do Ficheiro?");
	gets(nome_ficheiro);

	// INICIALIZA O GERADOR DE NÚMEROS ALEATÓRIOS
	init_rand();

	// PASSA DADOS DO FICHEIRO PARA A MATRIZ DE ADJACÊNCIAS
	mat_adjacencias = init_dados(nome_ficheiro, &num_vertices);

	// AlOCA MEMÓRIA PARA SOLUCÁO
	solucao = malloc(sizeof(int)*num_vertices);
    // VER SE COREU BEM
    if (solucao == NULL)
	{
		printf("Erro na alocacao de memoria");
		exit(1);
	}
	// AlOCA MEMÓRIA PARA A MELHOR SOLUCÁO
	melhor_solucao = malloc(sizeof(int)*num_vertices);
    // VER SE COREU BEM
    if (melhor_solucao == NULL)
	{
		printf("Erro na alocacao de memoria");
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
		fitness = trepa_colinas(solucao, mat_adjacencias, num_vertices, num_iteracoes);

		// MOSTRA RESULTADOS
		printf("Iteração: %d\n", i+1);
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

	// LIBERTAR MEMÓRIA ALOCADA
	free(mat_adjacencias);
	free(solucao);
	free(melhor_solucao);

	return 0;
}
