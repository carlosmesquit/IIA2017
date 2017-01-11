#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "algoritmo.h"
#include "utils.h"

int* init_dados(char *nome, int *vert)
{
	int *matriz;
	int linha = 0, coluna = 0;
	char buffer[255];
	char primeira[2];
	FILE *f;

	f = fopen(nome, "rt");
	if (!f)
	{
		printf("Erro ao abrir ficheiro!\n");
		exit(1);
	}

	while (fgets(buffer, 255, f) != NULL)
	{
		sscanf(buffer, "%s", primeira);

		if (!strcmp(primeira, "p"))
        {
			sscanf(buffer, "p edge %d", vert);
			// ALOCAR MEMÓRIA PARA A MATRIZ
			matriz = malloc(sizeof(int)*(*vert)*(*vert));
			if (!matriz)
			{
				printf("Erro na alocacao de memoria\n");
				exit(1);
			}

			// PREENCHER A MATRIZ COM ZEROS
			memset(matriz, 0, sizeof(int)*(*vert)*(*vert));
		}

		if (!strcmp(primeira, "e"))
        {
			sscanf(buffer, "e %d %d",&linha, &coluna);
			// PREENCHE MATRIZ
			*((int *)matriz + (linha - 1) * (*vert) + (coluna - 1)) = 1;
			*((int *)matriz + (coluna - 1) * (*vert) + (linha - 1)) = 1;
		}
	}
	fclose(f);
	return matriz;
}

void gera_sol_inicial(int *sol, int v)
{
	int i, total = 0;

	while (total <= 1)
    {
		for (i = 0; i < v; i++)
		{
			sol[i] = random_l_h(0, 1);
			if (sol[i] == 1)
			{
				total++;
			}
		}
	}
}

void init_rand()
{
	srand((unsigned)time(NULL));
}

int random_l_h(int min, int max)
{
	return min + rand() % (max - min + 1);
}

float rand_01()
{
	return ((float)rand()) / RAND_MAX;
}

void substitui(int a[], int b[], int n)
{
	int i;
	for (i = 0; i<n; i++)
		a[i] = b[i];
}

void escreve_sol(int *sol, int vert)
{
	int i, cliques=0;

	printf("Solucao encontrada: ");
	for (i = 0; i < vert; i++)
    {
		printf("%d ", sol[i]);
	}

	printf("\nConjunto de vertices = { ");
	for (i = 0; i < vert; i++)
    {
		if (sol[i] == 1)
		{
			printf("%d ", i + 1);
			cliques++;
		}
	}
	printf("}");

	printf("\nClique maximo: %d", cliques);
	printf("\n");
}
