#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float *dados;
    int tamanho;
    int capacidade;
} ArrayVetor;

// OPERAÇÕES BÁSICAS DA ESTRUTURA DE DADOS
  

ArrayVetor* inicializar_array(int capacidade) {
    ArrayVetor *arr = (ArrayVetor*) malloc(sizeof(ArrayVetor));
    if (arr == NULL) return NULL;

    arr->dados = (float*) malloc(capacidade * sizeof(float));
    if (arr->dados == NULL) {
        free(arr);
        return NULL;
    }

    arr->tamanho = 0;
    arr->capacidade = capacidade;
    return arr;
}

int inserir(ArrayVetor *arr, float valor) {
    if (arr == NULL || arr->tamanho >= arr->capacidade) {
        return 0; // Falha: array cheio ou nulo
    }
    arr->dados[arr->tamanho] = valor;
    arr->tamanho++;
    return 1; // Sucesso
}

void imprimir(ArrayVetor *arr) {
    if (arr == NULL || arr->tamanho == 0) {
        printf("[]\n");
        return;
    }
    printf("[");
    for (int i = 0; i < arr->tamanho; i++) {
        printf("%.4f", arr->dados[i]);
        if (i < arr->tamanho - 1) printf(", ");
    }
    printf("]\n");
}

int buscar(ArrayVetor *arr, float valor) {
    if (arr == NULL) return -1;
    for (int i = 0; i < arr->tamanho; i++) {
        if (fabs(arr->dados[i] - valor) < 0.00001) {
            return i; // Retorna o índice encontrado
        }
    }
    return -1; // Não encontrado
}

int remover(ArrayVetor *arr, int indice) {
    if (arr == NULL || indice < 0 || indice >= arr->tamanho) {
        return 0; // Índice inválido
    }
    for (int i = indice; i < arr->tamanho - 1; i++) {
        arr->dados[i] = arr->dados[i + 1];
    }
    arr->tamanho--;
    return 1;
}

void liberar_array(ArrayVetor *arr) {
    if (arr != NULL) {
        free(arr->dados);
        free(arr);
    }
}

// OPERAÇÕES MATEMÁTICAS
 

ArrayVetor* multiplicar_por_escalar(ArrayVetor *a, float k) {
    if (a == NULL) return NULL;
    ArrayVetor *resultado = inicializar_array(a->tamanho);
    for (int i = 0; i < a->tamanho; i++) {
        inserir(resultado, a->dados[i] * k);
    }
    return resultado;
}

ArrayVetor* somar_vetores(ArrayVetor *a, ArrayVetor *b) {
    if (a == NULL || b == NULL || a->tamanho != b->tamanho) {
        printf("\nErro: Vetores possuem dimensoes diferentes ou sao nulos.\n");
        return NULL;
    }
    ArrayVetor *resultado = inicializar_array(a->tamanho);
    for (int i = 0; i < a->tamanho; i++) {
        inserir(resultado, a->dados[i] + b->dados[i]);
    }
    return resultado;
}

float produto_escalar(ArrayVetor *a, ArrayVetor *b) {
    if (a == NULL || b == NULL || a->tamanho != b->tamanho) {
        return 0.0f;
    }
    float soma = 0.0f;
    for (int i = 0; i < a->tamanho; i++) {
        soma += a->dados[i] * b->dados[i];
    }
    return soma;
}

float norma(ArrayVetor *a) {
    if (a == NULL || a->tamanho == 0) return 0.0f;
    float soma_quadrados = 0.0f;
    for (int i = 0; i < a->tamanho; i++) {
        soma_quadrados += a->dados[i] * a->dados[i];
    }
    return sqrtf(soma_quadrados);
}

float similaridade_cosseno(ArrayVetor *a, ArrayVetor *b) {
    if (a == NULL || b == NULL || a->tamanho != b->tamanho) {
        printf("\nErro: Dimensoes incompativeis para similaridade de cosseno.\n");
        return -2.0f;
    }
    float norma_a = norma(a);
    float norma_b = norma(b);

    if (norma_a == 0.0f || norma_b == 0.0f) {
        printf("\nErro: Operacao invalida. Um dos vetores e nulo (norma igual a zero).\n");
        return -2.0f;
    }

    return produto_escalar(a, b) / (norma_a * norma_b);
}

int buscar_mais_similar(ArrayVetor *consulta, ArrayVetor **conjunto, int num_vetores) {
    int idx_melhor = -1;
    float maior_sim = -2.0f;

    for (int i = 0; i < num_vetores; i++) {
        float sim = similaridade_cosseno(consulta, conjunto[i]);
        if (sim > maior_sim) {
            maior_sim = sim;
            idx_melhor = i;
        }
    }
    return idx_melhor;
}

//(MENU DE NAVEGAÇÃO)
  

void menu_interativo() {
    int dimensao = 0, qtd_vetores = 0;

    printf("=========================================\n");
    printf("   SISTEMA DE MANIPULACAO DE VETORES     \n");
    printf("=========================================\n");

    // Requisito: Informe o tamanho (dimensão)
    while (dimensao <= 0) {
        printf("Informe a dimensao (tamanho) dos vetores: ");
        scanf("%d", &dimensao);
        if (dimensao <= 0) printf("A dimensao deve ser maior que zero!\n");
    }

    // Requisito: Crie dois ou mais vetores
    while (qtd_vetores < 2) {
        printf("Informe a quantidade de vetores (minimo 2): ");
        scanf("%d", &qtd_vetores);
        if (qtd_vetores < 2) printf("E necessario criar pelo menos 2 vetores para comparacoes!\n");
    }

    // Alocação da lista de vetores
    ArrayVetor **vetores = (ArrayVetor**) malloc(qtd_vetores * sizeof(ArrayVetor*));

    // Requisito: Informe os valores reais de cada vetor
    for (int i = 0; i < qtd_vetores; i++) {
        vetores[i] = inicializar_array(dimensao);
        printf("\n--- Digite os %d valores para o Vetor %d ---\n", dimensao, i);
        for (int j = 0; j < dimensao; j++) {
            float val;
            printf("Elemento [%d]: ", j);
            scanf("%f", &val);
            inserir(vetores[i], val);
        }
    }

    int opcao = -1;
    while (opcao != 0) {
        printf("\n================ MENU DE OPCOES ================\n");
        printf("1. Exibir todos os vetores armazenados\n");
        printf("2. Multiplicar um vetor por um escalar\n");
        printf("3. Somar dois vetores\n");
        printf("4. Calcular produto escalar entre dois vetores\n");
        printf("5. Calcular norma de um vetor\n");
        printf("6. Calcular similaridade de cosseno entre dois vetores\n");
        printf("7. Determinar vetor mais similar a um vetor de consulta\n");
        printf("0. Sair do programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: { // Exibir vetores
                printf("\n--- VETORES ARMAZENADOS ---\n");
                for (int i = 0; i < qtd_vetores; i++) {
                    printf("Vetor %d: ", i);
                    imprimir(vetores[i]);
                }
                break;
            }
            case 2: { // Multiplicar por escalar
                int idx;
                float k;
                printf("Informe o indice do vetor (0 a %d): ", qtd_vetores - 1);
                scanf("%d", &idx);
                if (idx < 0 || idx >= qtd_vetores) { printf("Indice invalido!\n"); break; }
                printf("Informe o valor escalar (k): ");
                scanf("%f", &k);

                ArrayVetor *res = multiplicar_por_escalar(vetores[idx], k);
                printf("Resultado (Vetor %d * %.2f): ", idx, k);
                imprimir(res);
                liberar_array(res);
                break;
            }
            case 3: { // Soma de dois vetores
                int i1, i2;
                printf("Informe o indice do primeiro vetor (0 a %d): ", qtd_vetores - 1);
                scanf("%d", &i1);
                printf("Informe o indice do segundo vetor (0 a %d): ", qtd_vetores - 1);
                scanf("%d", &i2);
                if (i1 < 0 || i1 >= qtd_vetores || i2 < 0 || i2 >= qtd_vetores) { printf("Indices invalidos!\n"); break; }

                ArrayVetor *res = somar_vetores(vetores[i1], vetores[i2]);
                if (res != NULL) {
                    printf("Resultado da Soma: ");
                    imprimir(res);
                    liberar_array(res);
                }
                break;
            }
            case 4: { // Produto escalar
                int i1, i2;
                printf("Informe o indice do primeiro vetor (0 a %d): ", qtd_vetores - 1);
                scanf("%d", &i1);
                printf("Informe o indice do segundo vetor (0 a %d): ", qtd_vetores - 1);
                scanf("%d", &i2);
                if (i1 < 0 || i1 >= qtd_vetores || i2 < 0 || i2 >= qtd_vetores) { printf("Indices invalidos!\n"); break; }

                float pe = produto_escalar(vetores[i1], vetores[i2]);
                printf("Produto Escalar entre Vetor %d e Vetor %d: %.4f\n", i1, i2, pe);
                break;
            }
            case 5: { // Norma
                int idx;
                printf("Informe o indice do vetor (0 a %d): ", qtd_vetores - 1);
                scanf("%d", &idx);
                if (idx < 0 || idx >= qtd_vetores) { printf("Indice invalido!\n"); break; }

                printf("Norma do Vetor %d: %.4f\n", idx, norma(vetores[idx]));
                break;
            }
            case 6: { // Similaridade de cosseno
                int i1, i2;
                printf("Informe o indice do primeiro vetor (0 a %d): ", qtd_vetores - 1);
                scanf("%d", &i1);
                printf("Informe o indice do segundo vetor (0 a %d): ", qtd_vetores - 1);
                scanf("%d", &i2);
                if (i1 < 0 || i1 >= qtd_vetores || i2 < 0 || i2 >= qtd_vetores) { printf("Indices invalidos!\n"); break; }

                float sim = similaridade_cosseno(vetores[i1], vetores[i2]);
                if (sim >= -1.0f) {
                    printf("Similaridade de Cosseno: %.4f\n", sim);
                }
                break;
            }
            case 7: { // Determinar vetor mais similar
                ArrayVetor *consulta = inicializar_array(dimensao);
                printf("\n--- Digite os %d valores do Vetor de Consulta ---\n", dimensao);
                for (int j = 0; j < dimensao; j++) {
                    float val;
                    printf("Elemento [%d]: ", j);
                    scanf("%f", &val);
                    inserir(consulta, val);
                }

                int idx_melhor = buscar_mais_similar(consulta, vetores, qtd_vetores);
                if (idx_melhor != -1) {
                    printf("\nO vetor mais similar no conjunto e o Vetor %d: ", idx_melhor);
                    imprimir(vetores[idx_melhor]);
                    printf("Similaridade: %.4f\n", similaridade_cosseno(consulta, vetores[idx_melhor]));
                }
                liberar_array(consulta);
                break;
            }
            case 0:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    }

    // Liberação de memória
    for (int i = 0; i < qtd_vetores; i++) {
        liberar_array(vetores[i]);
    }
    free(vetores);
}

int main() {
    menu_interativo();
    return 0;
}
