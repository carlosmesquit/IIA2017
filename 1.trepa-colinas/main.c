#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definicoes.h"
#include "utils.h"
#include "algoritmo.h"

int main(int argc, char *argv[])
{
    char nome_ficheiro[50];
    int i, j, n_elementos = 0;
    int m, melhor_m;
    int *solucao, *melhor_solucao;
    float fitness, melhor_fitness;
    float *matriz;

    printf("Qual o Nome do Ficheiro?\n");
    gets(nome_ficheiro);

    init_rand();

    // Obter dados do ficheiro
    matriz = init_dados(nome_ficheiro, &n_elementos);

    // Alocar memória para a solução atual com o número máximo de elementos
    solucao = malloc(sizeof(int) * n_elementos);
    if (solucao == NULL)
    {
        printf("Erro na alocacao de memoria para a solucao atual.\n");
        exit(1);
    }

    // Alocar memória para a melhor solução com o número máximo de elementos
    melhor_solucao = malloc(sizeof(int) * n_elementos);
    if (melhor_solucao == NULL)
    {
        printf("Erro na alocacao de memoria para a melhor solucao.\n");
        exit(1);
    }

    memset(solucao, 0, sizeof(int) * n_elementos);
    memset(melhor_solucao, 0, sizeof(int) * n_elementos);

    for (i = 0; i < NUM_EXECUCOES; i++) //
    {
        // Gerar Solução Inicial
        m = gerar_solucao(solucao, n_elementos);

        // Aplicar trepa colinas
        fitness = trepa_colinas(solucao, matriz, n_elementos, &m);

        // Mostar Resultados
        printf("\nIteracao: %d\n", i + 1);
        printf("Fitness: %.3f\n", fitness);
        mostrar_sol(solucao, m);

        // Se tiver encontrado uma solução melhor
        if ((fitness >= 0 && fitness > melhor_fitness) || i == 0)
        {
            melhor_m = m;
            melhor_fitness = fitness;
            substitui(melhor_solucao, solucao, melhor_m);
        }
    }

    // APRESENTA A SOLUCAO
    printf("\n\nA melhor ");
    printf("Fitness: %.3f\n", melhor_fitness);
    mostrar_sol(melhor_solucao, melhor_m);

    // LIBERTAR MEMÓRIA ALOCADA
    free(matriz);
    free(solucao);
    free(melhor_solucao);

    scanf("%d", &i);
    return 0;
}
