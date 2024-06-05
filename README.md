# Implementação de uma Árvore AVL em C++

Árvores AVL são um tipo de árvore binária de busca autobalanceada que garantem operações eficientes de inserção, remoção e busca com complexidade *O(log n)*. Inventadas por Georgy Adelson-Velsky e Evgenii Landis em 1962, estas árvores mantêm-se equilibradas através de rotações durante as operações, assegurando que as alturas das subárvores esquerda e direita de qualquer nó diferem no máximo por um.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Conceitos Principais das Árvores AVL

1. **Fator de Balanceamento (FB)**: Para cada nó na árvore AVL, a diferença de altura entre as subárvores esquerda e direita deve ser no máximo 1. Esta diferença é chamada de fator de balanceamento (FB), calculado como:

   ***FB = HEsq - HDir***

   onde `HEsq` é a altura da subárvore esquerda e `HDir` é a altura da subárvore direita. Para manter a árvore balanceada:

   ***-1 ≤ FB ≤ 1***

2. **Propriedade de Pesquisa Binária**: A sequência em ordem das chaves na árvore permite que qualquer valor seja pesquisado em *O(log n)*.

3. **Propriedade do Fator de Equilíbrio**: As alturas das subárvores de qualquer nó diferem no máximo por um, garantindo que a altura de uma árvore AVL seja sempre *O(log n)*.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Operações Básicas

- **Inserção**: Ao inserir um novo nó, a árvore pode se desbalancear. Para restaurar o equilíbrio, são realizadas rotações simples ou duplas.
- **Remoção**: A remoção de um nó pode desbalancear a árvore. Similarmente à inserção, rotações são usadas para reequilibrar a árvore.
- **Busca**: A busca em uma árvore AVL é realizada de maneira semelhante à busca em uma árvore binária de busca padrão, seguindo a propriedade de pesquisa binária. Como a árvore está balanceada, a complexidade de busca é *O(log n)*.
- **Rotações**: Existem quatro tipos de rotações usadas para manter o equilíbrio:
  - Rotação Simples à Esquerda
  - Rotação Simples à Direita
  - Rotação Dupla à Esquerda (Rotação Direita-Esquerda)
  - Rotação Dupla à Direita (Rotação Esquerda-Direita)

**Observação 1:** Por ser uma árvore binária de busca balanceada, a árvore AVL mantém a propriedade de manter os nós menores que a raiz na subárvore esquerda e os nós maiores que a raiz na subárvore direita.

**Observação 2:** Após cada balanceamento (rotação) realizado na inserção e na remoção de um novo elemento (nó), as alturas e fatores de balanceamento devem ser atualizados.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Rotações

### Como decidir as rotações

Como mencionado anteriormente, para manter a árvore AVL balanceada, as rotações são realizadas com base no fator de balanceamento (FB) de cada nó. Aqui está o processo para decidir as rotações:

- Calcule o fator de balanceamento: ***FB = HEsq - HDir***
- Se ***-1 < FB < 1***: a *árvore está equilibrada*.
- Se ***FB > 1***:
  - Se a subárvore da direita tem ***FB < 0***:
    - Rotação dupla à esquerda.
  - Senão:
    - Rotação à esquerda.
- Se ***FB < -1***:
  - Se a subárvore da esquerda tem ***FB > 0***:
    - Rotação dupla à direita.
  - Senão:
    - Rotação à direita.

| FB da raiz | FB da subárvore direita | FB da subárvore esquerda |          Rotação          |
|------------|-------------------------|--------------------------|---------------------------|
|     -2     |        FB <= 0          |            -             |    Rotação à Esquerda     |
|     -2     |        FB > 0           |            -             | Rotação Esquerda-Direita  |
|      2     |            -            |        FB <= 0           |    Rotação à Direita      |
|      2     |            -            |        FB > 0            | Rotação Direita-Esquerda  |

### Rotação à Esquerda

- Filho da direita vira nova raiz
- A raiz original vira filho da esquerda da nova raiz

```plaintext
            x                   y
             \                 / \
              y      ->       x   C
               \              
                C               
```

- E se o filho da direita já tem filho da esquerda?
  - Por estar na subárvore direita, já se sabe que esse valor é maior que a raiz original, portanto:

```plaintext
                x                   y
                 \                 / \
                  y      ->       x   C
                 / \               \
                B   C               B
```

  1. y é a nova raiz
  2. O filho da esquerda de y (B) vira o filho da direita de x
  3. x vira filho da esquerda de y

### Rotação à Direita

- Filho da esquerda vira nova raiz
- A raiz original vira filho da direita da nova raiz

```plaintext
                 y             x
                /             / \
               x      ->     A   y
              /
             A
```

- E se o filho da esquerda já tem filho da direita?
  - Por estar na subárvore esquerda, já se sabe que esse valor é menor que a raiz original, portanto:

```plaintext
                 y             x
                /             / \
               x      ->     A   y
              / \               /
             A   B             B  
```

  1. x é a nova raiz
  2. O filho da direita de x (B) vira o filho da esquerda de y
  3. y vira filho da direita de x

### Rotação Direita-Esquerda (ou Rotação Dupla à Esquerda)

- Uma rotação apenas não basta
- É necessário realizar uma rotação à direita na subárvore da direita e uma rotação à esquerda na árvore original

```plaintext
        x         x            y
         \         \          / \
          C    ->   y   ->   x   C
         /           \
        y             C
```

### Rotação Esquerda-Direita (ou Rotação Dupla à Direita)

- Uma rotação apenas não basta
- É necessário realizar uma rotação à esquerda na subárvore da esquerda e uma rotação à direita na árvore original

```plaintext
        y        y        x
       /        /        / \
      A   ->   x   ->   A   y
       \      /   
        x    A     
```


------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Implementação em C++

### Implementação da Árvore AVL usando um TAD

A implementação da árvore AVL foi estruturada usando um TAD (Tipo Abstrato de Dados), dividida em três arquivos:

- **avl.hpp**: Este arquivo contém a definição da estrutura de dados da árvore AVL, juntamente com os protótipos das funções que serão implementadas. Aqui estão declaradas todas as operações básicas da árvore, como inserção, remoção, busca, os percursos pré-ordem, em ordem e pós-ordem, impressão da árvore, as funções de balanceamento etc.

- **avl.cpp**: Aqui é onde a implementação das funções declaradas em avl.hpp é realizada. Todas as operações definidas no TAD são desenvolvidas neste arquivo. Isso inclui a lógica para inserir e remover nós da árvore, bem como qualquer outra operação necessária para manter a propriedade de árvore AVL.

- **main.cpp**: Este arquivo contém o menu de usuário e a lógica para interagir com a árvore AVL. Aqui, o usuário pode realizar diversas operações na árvore, como inserir, remover e buscar elementos, além de qualquer outra funcionalidade desejada.

Essa estrutura ajuda a manter o código organizado e modular, facilitando a manutenção e compreensão do programa. Cada parte do código tem uma responsabilidade clara, o que torna mais fácil entender e fazer alterações no sistema conforme necessário.

### Funcionalidades Principais

- **Inserção de Elementos**: A função `InsereAVLRec` permite inserir novos elementos na árvore AVL de forma recursiva, mantendo-a balanceada.
- **Remoção de Elementos**: A função `RemoveAVLRec` permite remover elementos da árvore AVL de forma recursiva, mantendo-a balanceada.
- **Busca de Elementos**: A função `BuscaNo` permite buscar um elemento na árvore AVL.
- **Percursos na Árvore AVL**: As funções `PreOrdem`, `Ordem` e `PosOrdem` permitem realizar os percursos pré-ordem, em ordem e pós-ordem, respectivamente, na árvore AVL.
- **Balanceamento da Árvore AVL**: As funções de rotação (`RotacaoEsquerda`, `RotacaoDireita`, `RotacaoEsquerdaDireita` e `RotacaoDireitaEsquerda`) são responsáveis por manter a árvore AVL balanceada após a inserção e remoção de elementos.

### Função Principal (main)

Na função principal está implementado um menu que possibilita que o usuário insira e remova elementos em uma árvore AVL, imprima essa árvore em pré-ordem, ordem e pós-ordem e lhe dá acesso a um exemplo de árvore AVL. Neste exemplo são inseridos os elementos 15 - 27 - 49 - 10 - 8 - 67 - 59 - 9 - 13 - 20 - 14 (nesta ordem). Neste exemplo são executados os 4 tipos de rotação.

- Insere 15

  ```
    15
  ```
    - **Pré-ordem:** 15 (H = 0, FB = 0)
    - **Em ordem:**  15 (H = 0, FB = 0)
    - **Pós-ordem:** 15 (H = 0, FB = 0)

  
- Insere 27

  ```
    15
      \
       27
  ```
    - **Pré-ordem:** 15 (H = 1, FB = -1) - 27 (H = 0, FB = 0)
    - **Em ordem:**  15 (H = 1, FB = -1) - 27 (H = 0, FB = 0)
    - **Pós-ordem:** 27 (H = 0, FB = 0) - 15  (H = 1, FB = -1)

 
- Insere 49 

  ```
    15
      \
       27
         \
          49
  ```
  Rotação à Esquerda (15 - 27 - 49):
  ```
      27
     /  \
    15  49
  ```

    - **Pré-ordem:** 27 (H = 1, FB = 0) - 15 (H = 0, FB = 0) - 49 (H = 0, FB = 0)
    - **Em ordem:**  15 (H = 0, FB = 0) - 27 (H = 1, FB = 0) - 49 (H = 0, FB = 0)
    - **Pós-ordem:** 15 (H = 0, FB = 0) - 49 (H = 0, FB = 0) - 27 (H = 1, FB = 0)


- Insere 10

  ```
       27
      /  \
     15  49
     /
    10
  ```
    - **Pré-ordem:** 27 (H = 2, FB = 1) - 15 (H = 1, FB = 1) - 10 (H = 0, FB = 0) - 49 (H = 0, FB = 0)
    - **Em ordem:**  15 (H = 1, FB = 1) - 10 (H = 0, FB = 0) - 27 (H = 2, FB = 1) - 49 (H = 0, FB = 0)
    - **Pós-ordem:** 10 (H = 0, FB = 0) - 15 (H = 1, FB = 1) - 49 (H = 0, FB = 0) - 27 (H = 2, FB = 1)


- Insere 8

  ```
          27
         /  \
        15  49
       /
      10
     /
    8
  ```
  
  Rotação à Direita (15 - 10 - 8):

  ```
        27
       /  \
      10  49
     /  \
    8   15
  ```

    - **Pré-ordem:** 27 (H = 2, FB = 1) - 10 (H = 1, FB = 0) - 8 (H = 0, FB = 0) - 15 (H = 0, FB = 0) - 49 (H = 0, FB = 0)
    - **Em ordem:** 8 (H = 0, FB = 0) - 10 (H = 1, FB = 0) - 15 (H = 0, FB = 0) - 27 (H = 2, FB = 1) - 49 (H = 0, FB = 0)
    - **Pós-ordem:** 8 (H = 0, FB = 0) - 15 (H = 0, FB = 0) - 10 (H = 1, FB = 0) - 49 (H = 0, FB = 0) - 27 (H = 2, FB = 1)


- Insere 67

  ```
        27
       /  \
      10  49
     /  \   \
    8   15   67
  ```
    - **Pré-ordem:** 27 (H = 2, FB = 0) - 10 (H = 1, FB = 0) - 8 (H = 0, FB = 0) - 15 (H = 0, FB = 0) - 49 (H = 1, FB = -1) - 67 (H = 0, FB = 0)
    - **Em ordem:** 8 (H = 0, FB = 0) - 10 (H = 1, FB = 0) - 15 (H = 0, FB = 0) - 27 (H = 2, FB = 0) - 49 (H = 1, FB = -1) - 67 (H = 0, FB = 0)
    - **Pós-ordem:** 8 (H = 0, FB = 0) - 15 (H = 0, FB = 0) - 10 (H = 1, FB = 0) - 67 (H = 0, FB = 0) - 49 (H = 1, FB = -1) - 27 (H = 2, FB = 0)


- Insere 59

  ```
        27
       /  \
      10  49
     /  \   \
    8   15   67
            /
          59
  ```
  Rotação Direita-Esquerda (49-67-59):
  
  1. Rotação Direita (67-59):

  ```
        27
       /  \
      10  49
     /  \   \
    8   15   59
               \
                67
  ```
  2. Rotação Esquerda (49-59-67):

  ```
          27
       /      \
      10      59
     /  \    /  \
    8   15  49  67

  ```
    - **Pré-ordem:** 27 (H = 2, FB = 0) - 10 (H = 1, FB = 0) - 8 (H = 0, FB = 0) - 15 (H = 0, FB = 0) - 59 (H = 1, FB = 0) - 49 (H = 0, FB = 0) - 67 (H = 0, FB = 0)
    - **Em ordem:** 8 (H = 0, FB = 0) - 10 (H = 1, FB = 0) - 15 (H = 0, FB = 0) - 27 (H = 2, FB = 0) - 49 (H = 0, FB = 0) - 59 (H = 1, FB = 0) - 67 (H = 0, FB = 0)
    - **Pós-ordem:** 8 (H = 0, FB = 0) - 15 (H = 0, FB = 0) - 10 (H = 1, FB = 0) - 49 (H = 0, FB = 0) - 67 (H = 0, FB = 0) - 59 (H = 1, FB = 0) - 27 (H = 2, FB = 0)
  

- Insere 9

  ```
          27
       /      \
      10      59
     /  \    /  \
    8   15  49  67
     \
      9
  ```

    - **Pré-ordem:** 27 (H = 3, FB = 1) - 10 (H = 2, FB = 1) - 8 (H = 1, FB = -1) - 9 (H = 0, FB = 0) - 15 (H = 0, FB = 0) - 59 (H = 1, FB = 0) - 49 (H = 0, FB = 0) - 67 (H = 0, FB = 0)
    - **Em ordem:** 8 (H = 1, FB = -1) - 9 (H = 0, FB = 0) - 10 (H = 2, FB = 1) - 15 (H = 0, FB = 0) - 27 (H = 3, FB = 1) - 49 (H = 0, FB = 0) - 59 (H = 1, FB = 0) - 67 (H = 0, FB = 0)
    - **Pós-ordem:** 8 (H = 1, FB = -1) - 9 (H = 0, FB = 0) - 10 (H = 2, FB = 1) - 15 (H = 0, FB = 0) - 59 (H = 1, FB = 0) - 49 (H = 0, FB = 0) - 67 (H = 0, FB = 0)
 
- Insere 13
  ```
            27
         /     \
       10       59
     /    \    /  \
    8     15  49  67
     \   /  \                     
      9 13  20
  ```
    - **Pré-ordem:** 27 (H = 3, FB = 1) - 10 (H = 2, FB = 0) - 8 (H = 1, FB = -1) - 9 (H = 0, FB = 0) - 15 (H = 1, FB = 0) - 13 (H = 0, FB = 0) - 59 (H = 1, FB = 0) - 49 (H = 0, FB = 0) - 67 (H = 0, FB = 0) - 20 (H = 0, FB = 0)
    - **Em ordem:** 8 (H = 1, FB = -1) - 9 (H = 0, FB = 0) - 10 (H = 2, FB = 0) - 13 (H = 0, FB = 0) - 15 (H = 1, FB = 0) - 20 (H = 0, FB = 0) - 27 (H = 3, FB = 1) - 49 (H = 0, FB = 0) - 59 (H = 1, FB = 0) - 67 (H = 0, FB = 0)
    - **Pós-ordem:** 9 (H = 0, FB = 0) - 8 (H = 1, FB = -1) - 13 (H = 0, FB = 0) - 20 (H = 0, FB = 0) - 15 (H = 1, FB = 0) - 10 (H = 2, FB = 0) - 49 (H = 0, FB = 0) - 67 (H = 0, FB = 0) - 59 (H = 1, FB = 0) - 27 (H = 3, FB = 1) 

  - Insere 20   

  ```
           27     
        /      \   
       10        59 
     /     \    /  \      
    8      15  49  67
     \    /  \                     
      9  13  20        
  ```

     - **Pré-ordem:** 27 (H = 3, FB = 1) - 10 (H = 2, FB = 0) - 8 (H = 1, FB = -1) - 9 (H = 0, FB = 0) - 15 (H = 1, FB = 0) - 13 (H = 0, FB = 0) - 20 (H = 0, FB = 0) - 59 (H = 1, FB = 0) - 49 (H = 0, FB = 0) - 67 (H = 0, FB = 0) 
    - **Em ordem:** 8 (H = 1, FB = -1) - 9 (H = 0, FB = 0) - 10 (H = 2, FB = 0) - 13 (H = 0, FB = 0) - 15 (H = 1, FB = 0) - 20 (H = 0, FB = 0) - 27 (H = 3, FB = 1) - 49 (H = 0, FB = 0) - 59 (H = 1, FB = 0) - 67 (H = 0, FB = 0)
    - **Pós-ordem:** 9 (H = 0, FB = 0) - 8 (H = 1, FB = -1) - 13 (H = 0, FB = 0) - 20 (H = 0, FB = 0) - 15 (H = 1, FB = 0) - 10 (H = 2, FB = 0) - 49 (H = 0, FB = 0) - 67 (H = 0, FB = 0) - 59 (H = 1, FB = 0) - 27 (H = 3, FB = 1) 

  - Insere 14 
  
  ```
           27
        /      \
       10        59
     /     \    /  \
    8      15  49  67
     \    /  \
      9  13  20
           \
            14                                     
  ``` 
  Rotação Esquerda-Direita (27-10-15):

  1. Rotação Esquerda (10-15):

  ```

                27 
            /        \
           15          59
        /     \       /  \
      10      20   49    67 
     / \
    8   13
     \    \                                         
      9   14                                        
  ``` 
  2. Rotação Direita (27-15-10):
  
  ```
           15  
        /       \ 
      10          27
    /     \     /    \
    8      13  20     59
     \      \        /  \
      9      14     49  67
                                      
  ``` 
  
    - **Pré-ordem:** 15 (H = 3, FB = 0) - 10 (H = 2, FB = 0) - 8 (H = 1, FB = -1) - 9 (H = 0, FB = 0) - 13 (H = 1, FB = -1) - 14 (H = 0, FB = 0) - 27 (H = 2, FB = -1) - 20 (H = 0, FB = 0) - 59 (H = 1, FB = 0) - 49 (H = 0, FB = 0) - 67 (H = 0, FB = 0) 
    - **Em ordem:** 8 (H = 1, FB = -1) - 9 (H = 0, FB = 0) - 10 (H = 2, FB = 0) - 13 (H = 1, FB = -1) - 14 (H = 0, FB = 0) - 15 (H = 3, FB = 0) - 20 (H = 0, FB = 0) - 27 (H = 2, FB = -1) - 49 (H = 0, FB = 0) - 59 (H = 1, FB = 0) - 67 (H = 0, FB = 0)
    - **Pós-ordem:** 8 (H = 1, FB = -1) - 9 (H = 0, FB = 0) - 14 (H = 0, FB = 0) - 13 (H = 1, FB = -1) - 10 (H = 2, FB = 0) - 20 (H = 0, FB = 0) - 49 (H = 0, FB = 0) - 67 (H = 0, FB = 0) - 59 (H = 1, FB = 0) - 27 (H = 2, FB = -1) - 15 (H = 3, FB = 0) 

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Como Rodar o Projeto

### Pré-requisitos

- g++ versão 7.4 ou superior.

### Compilação

Para compilar o projeto, execute o seguinte comando no seu terminal:

```bash
g++ *.cpp -o avl
```

### Execução

Para executar o programa, use um dos seguintes comandos:

- No Windows: `avl` ou `avl.exe`
- No Linux/Mac: `./avl`

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
