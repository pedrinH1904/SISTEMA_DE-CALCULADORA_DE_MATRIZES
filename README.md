# # Calculadora de Matrizes em C

Sistema desenvolvido em linguagem C com o objetivo de permitir o cadastro de duas ou mais matrizes e realizar operações matemáticas entre elas direto pelo terminal.

**Autor:** Pedro Henrique de Lira Tavares  
**RGM:** 47754672  
**Link no OnlineGDB:** [https://onlinegdb.com/WK1N6xrr3H](https://onlinegdb.com/WK1N6xrr3H)

---

## O que o sistema faz

- Cadastra de 2 até 10 matrizes por vez, com tamanhos escolhidos pelo usuário (limite de até 10x10).
- Valida o que é digitado para não travar caso entre alguma letra, número inválido ou matriz com tamanho incompatível.
- **Adição e Subtração:** soma ou subtrai as matrizes na ordem em que foram cadastradas, verificando se todas têm o mesmo número de linhas e colunas.
- **Multiplicação:** multiplica as matrizes em sequência (da esquerda para a direita), conferindo se o número de colunas de uma bate com o de linhas da próxima.
- **Divisão ($A / B = A \times B^{-1}$):** calcula a inversa da matriz divisora usando eliminação de Gauss-Jordan e depois multiplica pela primeira. Se a matriz divisora não for quadrada ou não tiver inversa (determinante zero), o programa avisa e cancela a conta.
- Permite ver as matrizes já cadastradas a qualquer momento ou cadastrar novas matrizes sem precisar fechar o programa.

---

## Como compilar e executar

### Rodando direto pelo OnlineGDB
1. Acesse o projeto compartilhado no link: [https://onlinegdb.com/WK1N6xrr3H](https://onlinegdb.com/WK1N6xrr3H)
2. Clique no botão verde **Run** no topo da tela para compilar e interagir com o menu pelo console.

### Rodando pelo terminal (GCC)
1. Baixe o arquivo `main.c` deste repositório para o seu computador.
2. Abra o terminal na pasta onde o arquivo está salvo e compile com o comando:
   ```bash
   gcc main.c -o calculadora
   ```
3. Execute o programa gerado:
   - **Windows:**
     ```bash
     calculadora.exe
     ```
   - **Linux / Mac:**
     ```bash
     ./calculadora
     ```

---

## Funções do programa

Todo o código foi dividido em funções menores para deixar a `main()` apenas controlando o menu principal:

- `lerInteiro()` e `lerReal()`: leem os números digitados pelo usuário e limpam o buffer do teclado se algum valor inválido for informado.
- `absoluto()`: retorna o valor positivo de um número real (`float`), usada na hora de comparar os pivôs na inversão.
- `lerMatriz()` e `cadastrarMatrizes()`: pedem a quantidade de matrizes, suas dimensões e cada elemento.
- `mostrarMatriz()` e `mostrarTodas()`: exibem uma ou todas as matrizes cadastradas organizadas em linhas e colunas.
- `mostrarMenu()`: mostra as opções disponíveis na tela.
- `copiar()`: copia os valores de uma matriz para outra auxiliar durante os cálculos.
- `somar()` e `subtrair()`: fazem a soma e a subtração entre duas matrizes de mesmo tamanho.
- `multiplicar()`: faz a multiplicação entre duas matrizes compatíveis.
- `inverter()`: calcula a inversa de uma matriz quadrada pelo método de Gauss-Jordan.
- `dividir()`: valida a matriz divisora, chama `inverter()` e depois usa `multiplicar()` para chegar ao resultado.
- `calcular()`: aplica a operação escolhida em sequência para todas as matrizes cadastradas.
- `main()`: inicia o cadastro e mantém o menu rodando até o usuário escolher sair.

---

## Exemplo de uso

### Entrada (cadastrando e somando duas matrizes 2x2)
```text
=== Cadastro de Matrizes ===
Quantas matrizes deseja cadastrar (minimo 2)? 2

--- Matriz 1 ---
Quantidade de linhas: 2
Quantidade de colunas: 2
Elemento [1][1]: 2
Elemento [1][2]: 4
Elemento [2][1]: 6
Elemento [2][2]: 8

--- Matriz 2 ---
Quantidade de linhas: 2
Quantidade de colunas: 2
Elemento [1][1]: 1
Elemento [1][2]: 3
Elemento [2][1]: 5
Elemento [2][2]: 7

====== CALCULADORA DE MATRIZES ======
1 - Adicao
2 - Subtracao
3 - Multiplicacao
4 - Divisao
5 - Ver matrizes cadastradas
6 - Cadastrar novas matrizes
0 - Sair
=====================================
Escolha uma opcao: 1
```

### Saída no terminal
```text
Matriz resultante (2x2):
|     3.00     7.00 |
|    11.00    15.00 |
```
