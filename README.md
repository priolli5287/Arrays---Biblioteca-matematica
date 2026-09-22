# Biblioteca Matemática baseada em Arrays - Estruturas de Dados

Este projeto implementa uma estrutura de dados de Array Dinâmico/Contínuo para manipulação de vetores de números reais (`float`) e operações matemáticas avançadas, incluindo o cálculo de **Similaridade de Cosseno**, sem a utilização de bibliotecas externas de processamento de dados.

## Instruções de Compilação e Execução

### Pré-requisitos
* Compilador C (`gcc` ou `clang`)
* Biblioteca C padrão (`stdio.h`, `stdlib.h`, `math.h`)

### Compilação
No terminal, execute o comando abaixo para compilar o programa utilizando a flag `-lm` (necessária para a biblioteca matemática `<math.h>`):

```bash
gcc -std=c99 main.c -o biblioteca_matematica -lm
```

### Execução
Após compilar, execute o binário gerado:

* **Linux/macOS:**
  ```bash
  ./biblioteca_matematica
  ```
* **Windows (PowerShell/CMD):**
  ```bash
  .\biblioteca_matematica.exe
  ```

---

## Exemplos de Uso no Código

### 1. Inicializando e Inserindo Dados
```c
ArrayVetor *v = inicializar_array(3);
inserir(v, 0.80f);
inserir(v, 0.20f);
inserir(v, 0.50f);
imprimir(v); // Saída: [0.80, 0.20, 0.50]
```

### 2. Calculando Similaridade de Cosseno
```c
ArrayVetor *v1 = inicializar_array(3);
/* insere dados em v1... */

ArrayVetor *v2 = inicializar_array(3);
/* insere dados em v2... */

float sim = similaridade_cosseno(v1, v2);
printf("Similaridade: %.4f\n", sim);
```

---

## Conjunto de Testes Realizados

A aplicação executa automaticamente uma suíte de testes cobrindo os seguintes casos:

1. **Operações da Estrutura de Dados:**
   - Inserção sequencial por índice.
   - Busca de elemento por valor com retorno de índice.
   - Remoção por índice ajustando o tamanho lógico.
2. **Operações Vetoriais Básicas:**
   - Produto escalar ($A \cdot B$).
   - Multiplicação por escalar ($k \cdot A$).
   - Soma de vetores ($A + B$) com validação de dimensões.
3. **Cálculo de Norma e Similaridade:**
   - Validação com os dados de exemplo do enunciado (A=[0.8, 0.2, 0.5, 0.9] e B=[0.7, 0.1, 0.6, 0.8] $\rightarrow$ Similaridade = 0.9876).
4. **Tratamento de Exceções:**
   - Tentativa de cálculo de similaridade com vetor nulo (norma 0).
   - Tentativa de soma entre vetores de tamanhos divergentes.
5. **Busca por Maior Similaridade:**
   - Seleção do vetor mais próximo dentre um conjunto de vetores de consulta.
