<h1>AVL Tree Implementation in C</h1>

Este é um exemplo de implementação de uma Árvore AVL em C. A Árvore AVL é uma árvore binária 
de busca balanceada, onde a diferença de altura entre as subárvores esquerda e direita de cada 
nó (chamada de fator de balanceamento) é mantida em um intervalo específico.

<h2>Estrutura de Dados</h2>

O código contém a seguinte estrutura de dados para os nós da Árvore AVL:
```
typedef struct no
{
    int chave, bal;
    struct no *dir;
    struct no *esq;
} No;
```

- chave: Valor inteiro armazenado no nó.
- bal: Fator de balanceamento do nó.
- dir: Ponteiro para o filho direito do nó.
- esq: Ponteiro para o filho esquerdo do nó.

<h2>Funções Principais</h2>

- **void InserirAVL(int x, No (*(*pt)), bool (*(*h)))** :
Esta função insere um novo elemento na Árvore AVL.

- **void RemoverAVL(int x, No (*(*pt)), bool (*(*h)))** :
Esta função remove um elemento da Árvore AVL.

- **void PreOrdem(No (*pt))** :
Esta função percorre a árvore em pré-ordem e imprime os valores dos nós.

- **bool E_AVL(No (*ptraiz))** :
Esta função verifica se a árvore é uma Árvore AVL válida.

<h2>Compilação e Execução</h2>

Para compilar o código, você pode usar um compilador C como o GCC:
```
gcc main.c -o avl_tree
```

Em seguida, execute o programa:
```
./avl_tree
```
O programa contém testes automáticos para inserção, remoção e verificação da propriedade de AVL.

<h2>Notas</h2>

- Este código foi testado com números inteiros aleatórios para demonstrar o funcionamento da Árvore AVL.
- Certifique-se de ter um ambiente de desenvolvimento C configurado para compilar e executar o código.
