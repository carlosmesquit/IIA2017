#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "algoritmo.h"
#include "utils.h"

#define STRING_SIZE 255

// Leitura do ficheiro de input
// Recebe: nome do ficheiro, numero de vertices (ptr)
// Devolve a matriz de adjacencias
int* init_dados(char *nome, int *ver)
{
	FILE *f;

	int *p;
	int linha = 0, coluna = 0;
	int i = 0, j = 0; //contadores

	char buffer[STRING_SIZE]; //onde é guardada cada linha do ficheiro
	char primeira[2]; //onde é guardada a primeira letra

	f = fopen(nome, "r"); 
	//inst_teste_prob1.txt
	if (!f)
	{
		printf("Erro no acesso ao ficheiro dos dados\n");
		exit(1);
	}

	//Efectua a leitura do ficheiro
	while (fgets(buffer, 255, f) != NULL)
	{
		sscanf(buffer, "%s", primeira);

		if (!strcmp(primeira, "p")) {

			sscanf(buffer, "p edge %d", ver);
			//printf("Vertices: %d\n", *ver);

			// Alocacao dinamica da matriz
			p = malloc(sizeof(int)*(*ver)*(*ver));
			if (!p)
			{
				printf("Erro na alocacao de memoria\n");
				exit(1);
			}

			//preencher matriz com zeros;
			memset(p, 0, sizeof(int)*(*ver)*(*ver));
		}

		if (!strcmp(primeira, "e")) {
			sscanf(buffer, "e %d %d",&linha, &coluna);

			//cria a matriz de adjacências com a informação retirada do ficheiro
			*((int *)p + (linha - 1) * (*ver) + (coluna - 1)) = 1;
			*((int *)p + (coluna - 1) * (*ver) + (linha - 1)) = 1;
		}
	}
	fclose(f);
	return p;
}

// Gera a solucao inicial
// Parametros: solucao, numero de vertices
void gera_sol_inicial(int *sol, int v)
{
	int i, total = 0;

	while (total <= 1) {
		for (i = 0; i < v; i++)
		{
			sol[i] = random_l_h(0, 1);
			if (sol[i] == 1) {
				total++;
			}
		}
	}
}

// Inicializa o gerador de numeros aleatorios
void init_rand()
{
	srand((unsigned)time(NULL));
}

// Devolve valor inteiro aleatorio entre min e max
int random_l_h(int min, int max)
{
	return min + rand() % (max - min + 1);
}

// Devolve um valor real aleatorio do intervalo [0, 1]  
float rand_01()
{
	return ((float)rand()) / RAND_MAX;
}

// copia vector b para a (tamanho n)
void substitui(int a[], int b[], int n)
{
	int i;
	for (i = 0; i<n; i++)
		a[i] = b[i];
}

// Escreve solucao
// Parametros: solucao e numero de vertices
void escreve_sol(int *sol, int vert)
{
	int i, max=0;

	// Imprime a solução
	printf("Solucao: ");
	for (i = 0; i < vert; i++) {
		printf("%d ", sol[i]);
	}
	printf("\n");

	//Imprime o conjunto correspondente
	//aparentemente não está a apresentar os valores correctos
	printf("Conjunto = { ");

	for (i = 0; i < vert; i++) {
		if (sol[i] == 1) {
			printf("%d ", i + 1);
			max++;
		}
	}

	printf("}");

	//Imprime número máximo de vértices
	printf("\nMax. Clique: %d", max);
	printf("\n\n");
}