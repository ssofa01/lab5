#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <locale.h>

void printIncidence(int** A, int n) {
    int m = 0;
    for (int i = 0; i < n; i++) {
        if (A[i][i] == 1) m++;
        for (int j = i + 1; j < n; j++)
            if (A[i][j] == 1) m++;
    }

    int** B = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        B[i] = (int*)calloc(m, sizeof(int));

    int col = 0;

    for (int i = 0; i < n; i++) {
        if (A[i][i] == 1) {
            B[i][col] = 2;
            col++;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (A[i][j] == 1) {
                B[i][col] = 1;
                B[j][col] = 1;
                col++;
            }
        }
    }

    printf("\nМатрица инцидентности:\n");
    printf("     ");
    for (int j = 0; j < m; j++) printf("e%-2d", j + 1);
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("v%-2d ", i);
        for (int j = 0; j < m; j++) printf(" %d ", B[i][j]);
        printf("\n");
    }

    for (int i = 0; i < n; i++) free(B[i]);
    free(B);
}

void printVertexAnalysis(int** A, int n) {
    printf("\nИзолированные вершины (степень 0): ");
    int found = 0;
    for (int i = 0; i < n; i++) {
        int deg = 0;
        for (int j = 0; j < n; j++) deg += A[i][j];
        deg += A[i][i];
        if (deg == 0) { printf("%d ", i); found = 1; }
    }
    if (!found) printf("нет");
    printf("\n");

    printf("Концевые вершины (степень 1): ");
    found = 0;
    for (int i = 0; i < n; i++) {
        int deg = 0;
        for (int j = 0; j < n; j++) deg += A[i][j];
        deg += A[i][i];
        if (deg == 1) { printf("%d ", i); found = 1; }
    }
    if (!found) printf("нет");
    printf("\n");

    printf("Доминирующие вершины (степень %d): ", n - 1);
    found = 0;
    for (int i = 0; i < n; i++) {
        int deg = 0;
        for (int j = 0; j < n; j++) deg += A[i][j];
        deg += A[i][i];
        if (deg == n - 1) { printf("%d ", i); found = 1; }
    }
    if (!found) printf("нет");
    printf("\n");
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand((unsigned)time(NULL));

    int n;
    double p;
    double pLoop;

    printf("Введите число вершин: ");
    scanf_s("%d", &n);
    printf("Введите вероятность ребра (от 0 до 1): ");
    scanf_s("%lf", &p);
    printf("Введите вероятность петли (от 0 до 1): ");
    scanf_s("%lf", &pLoop);

    if (n <= 0 || p < 0 || p > 1 || pLoop < 0 || pLoop > 1) {
        printf("Ошибка ввода\n");
        return 1;
    }

    int** A = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        A[i] = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++) {
            double r = (double)rand() / RAND_MAX;
            if (r < p) {
                A[i][j] = 1;
                A[j][i] = 1;
            }
        }

    for (int i = 0; i < n; i++) {
        double r = (double)rand() / RAND_MAX;
        if (r < pLoop) A[i][i] = 1;
    }

    printf("\nМатрица смежности графа G:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%d ", A[i][j]);
        printf("\n");
    }

    int edges = 0;
    for (int i = 0; i < n; i++) {
        if (A[i][i] == 1) edges++;
        for (int j = i + 1; j < n; j++)
            if (A[i][j] == 1) edges++;
    }
    printf("\nРазмер графа G: %d\n", edges);


    for (int i = 0; i < n; i++) {
        int deg = 0;
        for (int j = 0; j < n; j++) deg += A[i][j];
        deg += A[i][i];
        printf("  Вершина %d: степень %d\n", i, deg);
    }

    printVertexAnalysis(A, n);

    printIncidence(A, n);
    printf("\nРазмер графа G через матрицу инцдентности: %d\n", edges);


    for (int i = 0; i < n; i++) {
        int deg = 0;
        for (int j = 0; j < n; j++)
            deg += A[i][j];
        deg += A[i][i];
        printf("  Вершина %d: степень %d\n", i, deg);
    }

    printVertexAnalysis(A, n);

    for (int i = 0; i < n; i++) free(A[i]);
    free(A);

    return 0;
}



