#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"
#include "algoritmo.h"

//Parametros Gerais
#define RUNS 100

int main(int argc, char *argv[]) {

	char nome_fich[100]; //nome do ficheiro

	int *mat_adj; //matriz de adjac�ncias
	int *sol, *best_sol; //solu��o & melhor solu��o
	int qualidade, best_qualidade, melhor_k;
	
	int num_iter, k, runs = RUNS;

	int i = 0, j = 0; //contadores
	int ver; //v�rtices

	printf("Nome do Ficheiro: ");
	gets(nome_fich);
	printf("Numero de Iteracoes: "); 
	scanf("%d", &num_iter); 

	// Inicializa o gerador de n�meros aleat�rios
	init_rand();

	// Preenche matriz de adjacencias 
	mat_adj = init_dados(nome_fich, &ver);

	//reserva mem�ria para o array solu��o e para o array da melhor solu��o encontrada
	sol = malloc(sizeof(int)*ver);
	best_sol = malloc(sizeof(int)*ver);

	//preencher matriz solu��o com zeros;
	memset(sol, 0, sizeof(int)*ver);

	//preencher matriz best com zeros;
	memset(best_sol, 0, sizeof(int)*ver);

	if (sol == NULL || best_sol == NULL)
	{
		printf("Erro na alocacao de memoria");
		exit(1);
	}

	for (k = 0; k < runs; k++)
	{
		// Gerar solucao inicial
		gera_sol_inicial(sol, ver);

		// Trepa colinas
		qualidade = trepa_colinas(sol, mat_adj, ver, num_iter);

		//Recristaliza��o Simulada
		//qualidade = recristalizacao_simulada(sol, mat_adj, ver);

		// Escreve resultados da repeticao k
		printf("Repeticao: %d\n", k+1); //n�mero de repeti��o
		printf("Qualidade: %d\n", qualidade); //Imprime a "Qualidade"
		escreve_sol(sol, ver);

		//actualiza a melhor solu��o e respectiva qualidade
		if (k == 0 || best_qualidade < qualidade)
		{
			best_qualidade = qualidade;
			substitui(best_sol, sol, ver);
			melhor_k = k+1;
		}
	}

	// Escreve resultados globais
	printf("------------------ RESULTADOS FINAIS ------------------\n");

	if (best_qualidade<0) {
		printf("-->> SOLUCAO INVALIDA\n\n");
	}

	printf("Melhor qualidade: %d\n", best_qualidade); //Imprime a melhor "Qualidade"
	escreve_sol(best_sol, ver);

	printf("Solucao encontrada na repeticao: %d\n", melhor_k);
	
	free(mat_adj);
	free(sol);
	free(best_sol);

	return 0;
}