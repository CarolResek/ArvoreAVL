//Definindo um nó
struct No { 
  int Info; //Valor armazenado pelo no
  int FB; // Fator de balanceamento
  int Altura; // Altura do nó
  No *Esq; // Ponteiro para a subárvore esquerda
  No *Dir; // Ponteiro para a subárvore direita
};

typedef struct No* Arvore; // Renomeia o nó e o define como tipo Arvore

// Funções principais
void IniciaArvore(Arvore &A); // Inicia a árvore
bool ArvoreVazia(Arvore A); // Verifica se a Árvore está vazia
Arvore CriaNo(int dado); // Cria o nó a ser inserido na árvore
void InsereAVLRec(Arvore &A, int dado); // Insere novo nó na árvore de forma recursiva
void RemoveAVLRec(Arvore &A, int dado); // Remove dado da árvore de forma recursiva
void EsvaziaArvore(Arvore &A); // Esvazia a árvore AVL
bool BuscaNo(Arvore A, int dado); // Busca um valor na árvore AVL
// Funções de Percursos na Árvore AVL
void PreOrdem(Arvore A); // Percurso Pré-Ordem: raiz - sub-arvore esquerda - sub-arvore direita
void Ordem(Arvore A); // Percurso Em Ordem: sub-arvore esquerda - raiz - sub-arvore direita
void PosOrdem(Arvore A); // Percurso Pós Ordem: sub-arvore esquerda - sub-arvore direita - raiz
// Funções de Árvores AVL - Rotações(para balanceamento)
Arvore RotacaoEsquerda(Arvore A); // Rotação à Esquerda
Arvore RotacaoDireita(Arvore A); // Rotação à Direita
Arvore RotacaoEsquerdaDireita(Arvore A); // Rotação Esquerda-Direita
Arvore RotacaoDireitaEsquerda(Arvore A); // Rotação Direita-Esquerda
// Funções Auxiliares
int ContaNos(Arvore A); // Conta o número de nós da árvore
Arvore Minimo(Arvore A); // Retorna o valor mínimo da árvore (descendente mais a esquerda da árvore)
Arvore Maximo(Arvore A); // Retorna o valor máximo da árvore (descendente mais a direita da árvore)
int max(int a, int b); // Função auxiliar para calcular o máximo entre dois valores inteiros (altura de dois nós da árvore)
// Funções Auxiliares - Balanceamento
int AlturaArvore(Arvore A); // Calcula o tamanho da árvore (comprimento do caminho mais longo da raiz até a folha)
void AtualizaAltura(Arvore A); // Função que atualiza a altura de um nó
int CalculaFB(Arvore A);// Função para calcular o fator de balanceamento de um nó
void AtualizaFB(Arvore A); // Função para atualizar o fator de balanceamento de um nó
void BalanceiaNo(Arvore &A);// Realiza, se necessário, o balanceamento da árvore após a inserção e a remoção de um novo elemento
