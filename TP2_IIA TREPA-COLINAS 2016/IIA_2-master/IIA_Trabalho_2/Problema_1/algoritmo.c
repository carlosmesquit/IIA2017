#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

// Repara a solução
// Parametros: solucao actual, matriz de adjacencias, numero de vertices
//substitui por zero um dos dois vértices que não estejam ligados por uma aresta
void repara(int *sol, int *mat, int vert) {

	int i, j;
	float aux;

	for (i = 0; i < vert; i++) {
		for (j = 0; j < vert; j++) {
			if (i != j) {
				if (sol[i] == 1 && sol[j] == 1) {
					if (*((int *)mat + i * vert + j) != 1) {
						aux = rand_01();
						if (aux <= 0.5) {
							sol[i] = 0;
						}
						else {
							sol[j] = 0;
						}
						i = j = 0;
					}
				}
			}
		}
	}
}

// Gera um vizinho
// Parametros: solucao actual, vizinho, numero de vertices
//troca vertices, acrescenta ou retira
void gera_vizinho(int a[], int b[], int n) //ALTERAR NO FINAL <<-----------------------
{
	int i, res, n_vert = 0;
	int p1, p2;	// 0, 1

	for (i = 0; i<n; i++)
		b[i] = a[i];

	//Calcula o número de vértices e arestas que existem na solução
	for (i = 0; i < n; i++) {
		if (b[i] == 1)
			n_vert++;
	}

	res = n_vert * 100 / n;

	if (n_vert == n) {
		// Encontra posicao com valor 1
		do
			p2 = random_l_h(0, n - 1);
		while (b[p2] != 1);
	}
	else if (n_vert == 0) {
		// Encontra posicao com valor 0
		do
			p1 = random_l_h(0, n - 1);
		while (b[p1] != 0);
	}
	else {
		// Encontra posicao com valor 1
		do
			p2 = random_l_h(0, n - 1);
		while (b[p2] != 1);

		// Encontra posicao com valor 0
		do
			p1 = random_l_h(0, n - 1);
		while (b[p1] != 0);
	}

	//Se o numero de vertices na solução for > 66% 
	if (res >= 66) {
		//retira vertice
		b[p2] = 0;
	}

	//Se o numero de vertices na solução estiver entre 33% e 66%
	if (res > 33 && res < 66) {
		//troca vertice
		b[p1] = 1;
		b[p2] = 0;
	}

	//Se o numero de vertices na solução for < 33% 
	if (res <= 33) {
		//adiciona vertice
		b[p1] = 1;
	}
}

// Trepa colinas first-choice
// Parametros: solucao, matriz de adjacencias, numero de vertices e numero de iteracoes
// Devolve o custo da melhor solucao encontrada

int trepa_colinas(int sol[], int *mat, int vert, int num_iter)
{
	int *nova_sol, qualidade, qualidade_viz, i;
	qualidade = qualidade_viz = 0;

	nova_sol = malloc(sizeof(int)*vert);
	if (nova_sol == NULL)
	{
		printf("Erro na alocacao de memoria");
		exit(1);
	}

	// Avalia solucao inicial
	qualidade = calcula_fit(sol, mat, vert);

	for (i = 0; i < num_iter; i++) {

		//***************** NÃO ACEITA SOLUÇÕES INVÁLIDAS *****************
		//Funcionando desta forma torna-se extremamente lento, é bastante mais rápido se 
		//aceitar soluções inválidas e as reparar posteriormente.

		//while (qualidade_viz <= 0) {
		//	// Gera vizinho
		//	gera_vizinho(sol, nova_sol, vert);

		//	// Avalia vizinho
		//	qualidade_viz = calcula_fit(nova_sol, mat, vert);
		//}
		//*****************************************************************


		//***************** ACEITA SOLUÇÕES INVÁLIDAS *****************
		// Gera vizinho
		gera_vizinho(sol, nova_sol, vert);
		
		// Avalia vizinho
		qualidade_viz = calcula_fit(nova_sol, mat, vert);

		// Repara a solução caso seja inválida
		if (qualidade_viz < 0) {
			repara(nova_sol, mat, vert); //CHAMA A FUNÇÃO REPARA <<-----------------------
			qualidade_viz = calcula_fit(nova_sol, mat, vert);
		}
		//*************************************************************
		
		// Aceita vizinho se a qualidade aumentar
		if (qualidade_viz > qualidade)
		{
			substitui(sol, nova_sol, vert);
			qualidade = qualidade_viz;
		}
	}

	free(nova_sol);

	return qualidade;
}

//int recristalizacao_simulada(int *sol, int *mat, int vert) {
//
//#define t_max 10
//#define t_min 0.1
//#define f_a 0.99
//
//	int *nova_sol, qualidade, qualidade_viz, k;
//	float tmax = t_max, tmin = t_min, fa = f_a;
//
//	float t = tmax;
//
//	nova_sol = malloc(sizeof(int)*vert);
//	if (nova_sol == NULL)
//	{
//		printf("Erro na alocacao de memoria");
//		exit(1);
//	}
//
//	// Avalia solucao inicial
//	qualidade = calcula_fit(sol, mat, vert);
//
//	while (t > tmin) {
//		for (k=0; k<5; k++)
//		{
//			// Gera vizinho
//			gera_vizinho(sol, nova_sol, vert);
//
//			// Avalia vizinho
//			qualidade_viz = calcula_fit(nova_sol, mat, vert);
//
//			// Aceita vizinho se a qualidade aumentar (problema de maximização)
//			if (qualidade_viz > qualidade)
//			{
//				substitui(sol, nova_sol, vert);
//				qualidade = qualidade_viz;
//			}
//			else {
//				if (rand_01() <= exp(qualidade - qualidade_viz) / t) {
//					sol = nova_sol;
//					qualidade = qualidade_viz;
//				}
//			}
//		}
//		t = t*fa;
//	}
//
//	free(nova_sol);
//	return qualidade;
//}