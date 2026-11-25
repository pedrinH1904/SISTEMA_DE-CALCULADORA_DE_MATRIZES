#include <stdio.h>

#define MAX 10

int lerInteiro(char texto[], int min, int max) {
    int numero;

    printf("%s", texto);
    while (scanf("%d", &numero) != 1 || numero < min || numero > max) {
        while (getchar() != '\n');
        printf("Valor invalido! Digite um inteiro entre %d e %d: ", min, max);
    }
    while (getchar() != '\n');
    return numero;
}

float lerReal() {
    float numero;

    while (scanf("%f", &numero) != 1) {
        while (getchar() != '\n');
        printf("Valor invalido! Digite um numero valido (ex: 2.5): ");
    }
    while (getchar() != '\n');
    return numero;
}

float absoluto(float x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

void lerMatriz(float m[MAX][MAX], int linhas, int colunas) {
    int i, j;

    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            printf("Elemento [%d][%d]: ", i + 1, j + 1);
            m[i][j] = lerReal();
        }
    }
}

int cadastrarMatrizes(float matrizes[MAX][MAX][MAX], int linhas[], int colunas[]) {
    int quantidade, k;

    printf("\n=== Cadastro de Matrizes ===\n");
    quantidade = lerInteiro("Quantas matrizes deseja cadastrar (minimo 2)? ", 2, MAX);

    for (k = 0; k < quantidade; k++) {
        printf("\n--- Matriz %d ---\n", k + 1);
        linhas[k] = lerInteiro("Quantidade de linhas: ", 1, MAX);
        colunas[k] = lerInteiro("Quantidade de colunas: ", 1, MAX);
        lerMatriz(matrizes[k], linhas[k], colunas[k]);
    }
    return quantidade;
}

void mostrarMatriz(float m[MAX][MAX], int linhas, int colunas) {
    int i, j;
    float valor;

    for (i = 0; i < linhas; i++) {
        printf("| ");
        for (j = 0; j < colunas; j++) {
            valor = m[i][j];
            if (valor > -0.005 && valor < 0.005) {
                valor = 0;
            }
            printf("%8.2f ", valor);
        }
        printf("|\n");
    }
}

void mostrarTodas(float matrizes[MAX][MAX][MAX], int linhas[], int colunas[], int quantidade) {
    int k;

    for (k = 0; k < quantidade; k++) {
        printf("\nMatriz %d (%dx%d):\n", k + 1, linhas[k], colunas[k]);
        mostrarMatriz(matrizes[k], linhas[k], colunas[k]);
    }
}

void mostrarMenu() {
    printf("\n====== CALCULADORA DE MATRIZES ======\n");
    printf("1 - Adicao\n");
    printf("2 - Subtracao\n");
    printf("3 - Multiplicacao\n");
    printf("4 - Divisao\n");
    printf("5 - Ver matrizes cadastradas\n");
    printf("6 - Cadastrar novas matrizes\n");
    printf("0 - Sair\n");
    printf("=====================================\n");
}

void copiar(float origem[MAX][MAX], float destino[MAX][MAX], int linhas, int colunas) {
    int i, j;

    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            destino[i][j] = origem[i][j];
        }
    }
}

int somar(float a[MAX][MAX], int la, int ca, float b[MAX][MAX], int lb, int cb, float r[MAX][MAX]) {
    int i, j;

    if (la != lb || ca != cb) {
        printf("\nErro: para somar, as matrizes precisam ter as mesmas dimensoes.\n");
        return 0;
    }
    for (i = 0; i < la; i++) {
        for (j = 0; j < ca; j++) {
            r[i][j] = a[i][j] + b[i][j];
        }
    }
    return 1;
}

int subtrair(float a[MAX][MAX], int la, int ca, float b[MAX][MAX], int lb, int cb, float r[MAX][MAX]) {
    int i, j;

    if (la != lb || ca != cb) {
        printf("\nErro: para subtrair, as matrizes precisam ter as mesmas dimensoes.\n");
        return 0;
    }
    for (i = 0; i < la; i++) {
        for (j = 0; j < ca; j++) {
            r[i][j] = a[i][j] - b[i][j];
        }
    }
    return 1;
}

int multiplicar(float a[MAX][MAX], int la, int ca, float b[MAX][MAX], int lb, int cb, float r[MAX][MAX]) {
    int i, j, k;

    if (ca != lb) {
        printf("\nErro: colunas da primeira matriz devem ser iguais as linhas da segunda.\n");
        return 0;
    }
    for (i = 0; i < la; i++) {
        for (j = 0; j < cb; j++) {
            r[i][j] = 0;
            for (k = 0; k < ca; k++) {
                r[i][j] = r[i][j] + a[i][k] * b[k][j];
            }
        }
    }
    return 1;
}

// Calcula a matriz inversa usando eliminacao de Gauss-Jordan
int inverter(float original[MAX][MAX], int n, float inversa[MAX][MAX]) {
    float m[MAX][MAX];
    float aux, pivo, fator;
    int i, j, k, maior;

    copiar(original, m, n, n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == j) {
                inversa[i][j] = 1;
            } else {
                inversa[i][j] = 0;
            }
        }
    }

    for (k = 0; k < n; k++) {
        maior = k;
        for (i = k + 1; i < n; i++) {
            if (absoluto(m[i][k]) > absoluto(m[maior][k])) {
                maior = i;
            }
        }

        if (absoluto(m[maior][k]) < 0.0001) {
            printf("\nErro: a matriz divisora e singular e nao possui inversa.\n");
            return 0;
        }

        for (j = 0; j < n; j++) {
            aux = m[k][j];
            m[k][j] = m[maior][j];
            m[maior][j] = aux;

            aux = inversa[k][j];
            inversa[k][j] = inversa[maior][j];
            inversa[maior][j] = aux;
        }

        pivo = m[k][k];
        for (j = 0; j < n; j++) {
            m[k][j] = m[k][j] / pivo;
            inversa[k][j] = inversa[k][j] / pivo;
        }

        for (i = 0; i < n; i++) {
            if (i != k) {
                fator = m[i][k];
                for (j = 0; j < n; j++) {
                    m[i][j] = m[i][j] - fator * m[k][j];
                    inversa[i][j] = inversa[i][j] - fator * inversa[k][j];
                }
            }
        }
    }
    return 1;
}

// Divisao matricial: A / B = A * B^-1
int dividir(float a[MAX][MAX], int la, int ca, float b[MAX][MAX], int lb, int cb, float r[MAX][MAX]) {
    float inversa[MAX][MAX];

    if (lb != cb) {
        printf("\nErro: a matriz divisora precisa ser quadrada para ter inversa.\n");
        return 0;
    }
    if (ca != lb) {
        printf("\nErro: colunas da primeira matriz devem ser iguais as linhas da segunda.\n");
        return 0;
    }
    if (inverter(b, lb, inversa) == 0) {
        return 0;
    }
    return multiplicar(a, la, ca, inversa, lb, lb, r);
}

void calcular(int opcao, float matrizes[MAX][MAX][MAX], int linhas[], int colunas[], int quantidade) {
    float atual[MAX][MAX];
    float novo[MAX][MAX];
    int linhasAtual = linhas[0];
    int colunasAtual = colunas[0];
    int deuCerto = 1;
    int i;

    copiar(matrizes[0], atual, linhasAtual, colunasAtual);

    for (i = 1; i < quantidade; i++) {
        if (opcao == 1) {
            deuCerto = somar(atual, linhasAtual, colunasAtual, matrizes[i], linhas[i], colunas[i], novo);
        } else if (opcao == 2) {
            deuCerto = subtrair(atual, linhasAtual, colunasAtual, matrizes[i], linhas[i], colunas[i], novo);
        } else if (opcao == 3) {
            deuCerto = multiplicar(atual, linhasAtual, colunasAtual, matrizes[i], linhas[i], colunas[i], novo);
        } else if (opcao == 4) {
            deuCerto = dividir(atual, linhasAtual, colunasAtual, matrizes[i], linhas[i], colunas[i], novo);
        }

        if (deuCerto == 0) {
            printf("Operacao cancelada.\n");
            return;
        }

        if (opcao == 3 || opcao == 4) {
            colunasAtual = colunas[i];
        }
        copiar(novo, atual, linhasAtual, colunasAtual);
    }

    printf("\nMatriz resultante (%dx%d):\n", linhasAtual, colunasAtual);
    mostrarMatriz(atual, linhasAtual, colunasAtual);
}

int main() {
    float matrizes[MAX][MAX][MAX];
    int linhas[MAX];
    int colunas[MAX];
    int quantidade;
    int opcao;

    quantidade = cadastrarMatrizes(matrizes, linhas, colunas);

    do {
        mostrarMenu();
        opcao = lerInteiro("Escolha uma opcao: ", 0, 6);

        if (opcao >= 1 && opcao <= 4) {
            calcular(opcao, matrizes, linhas, colunas, quantidade);
        } else if (opcao == 5) {
            mostrarTodas(matrizes, linhas, colunas, quantidade);
        } else if (opcao == 6) {
            quantidade = cadastrarMatrizes(matrizes, linhas, colunas);
        }
    } while (opcao != 0);

    printf("\nPrograma encerrado.\n");
    return 0;
}