#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

void init_rand()
{
    srand((unsigned)time(NULL));
}

int random_l_h(int min, int max)
{
    return min + rand() % (max - min + 1);
}

void substitui(int a[], int b[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        a[i] = b[i];
}

float *init_dados(char *nome, int *n_elementos)
{
    float *matriz, temp = 2;
    int i, j;
    char buffer[255];
    FILE *f;

    f = fopen(nome, "rt");
    if (!f)
    {
        printf("Erro ao abrir ficheiro!\n");
        exit(1);
    }

    if (!fgets(buffer, 255, f))
    {
        printf("Erro ao ler o ficheiro!\n");
        exit(2);
    }

    // Obter número de elementos
    if (sscanf(buffer, "%d", n_elementos) == EOF && *n_elementos <= 0)
    {
        printf("Número de elementos inválido!\n");
        exit(3);
    }

    // ALOCAR MEMÓRIA PARA A MATRIZ
    matriz = malloc(sizeof(float) * (*n_elementos) * (*n_elementos));
    if (!matriz)
    {
        printf("Erro na alocacao de memoria!\n");
        exit(4);
    }

    while (fgets(buffer, 255, f) != NULL)
    {
        if (sscanf(buffer, "%d %d %f", &i, &j, &temp) == 3)
        {
            *(matriz + j - 1 + (i - 1) * (*n_elementos)) = temp; // matriz[i][j]
        }
        else
        {
            printf("Erro ao ler o ficheiro (valores invalidos)!\n");
            exit(4);
        }
    }

    fclose(f);
    return matriz;
}

// Obtem a solução inicial, devolve o número de elementos na solução inicial
int gerar_solucao(int *sol, int elem)
{
    int m = 0, i;
    int min = random_l_h(1, elem - 1);
    int max = random_l_h(min + 1, elem);

    sol[m] = min;

    for (i = min + 1; i < max - 1; i++)
    {
        if (rand() % 2 == 0) // 50% de passar por este elemento
            sol[++m] = i;
    }

    sol[++m] = max;

    return m + 1;
}

void mostrar_sol(int *sol, int m)
{
    int i;

    printf("Solucao encontrada: ");
    for (i = 0; i < m; i++)
    {
        printf("%d ", sol[i] + 1);
    }

    printf("\n");
}