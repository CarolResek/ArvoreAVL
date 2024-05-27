#include <stdio.h>
#include <stdlib.h>
#include "avl.hpp"

//Inicia a árvore
void IniciaArvore(Arvore &A){
    A = nullptr;
}

//Verifica se a Árvore está vazia
bool ArvoreVazia(Arvore A){
    return A == nullptr; //Retorna true se A for nulo, caso contrário retorna false
} 

//Cria o nó a ser inserido na árvore
Arvore CriaNo(int dado){
    Arvore A = new No;
     if(!A){
        printf("\nFalha ao alocar memoria!\n");
        return nullptr;
    }
    A->Info = dado;
    A->FB = A->Altura = 0;
    A->Esq = A->Dir = nullptr;
    return A;
}

// Insere novo nó na árvore de forma recursiva
void InsereAVLRec(Arvore &A, int dado){
    // Se o ponteiro for nulo (árvore vazia), cria-se novo nó
    if(!A)
        A = CriaNo(dado);
    else if (dado > A->Info)
        // Inserção na subárvore direita (valores maiores que a raiz)
        InsereAVLRec(A->Dir, dado);
    else if (dado < A->Info)
        // Inserção na subárvore esquerda (valores menores que a raiz)
        InsereAVLRec(A->Esq, dado);
    else
        // Nó com o mesmo valor já existe
        return;

    // Atualiza a altura
    AtualizaAltura(A);
    // Atualiza o fator de balanceamento
    AtualizaFB(A);
    // Confere a necessidade de rebalancear a árvore
    BalanceiaNo(A);
}


// Remove dado da árvore de forma recursiva
void RemoveAVLRec(Arvore &A, int dado){
    if (A){
        // Se o valor a ser removido é menor que o valor na raiz, retirar dado da subárvore esquerda
        if(A->Info > dado)
            RemoveAVLRec(A->Esq, dado);
        // Se o valor a ser removido é maior que o valor na raiz, retirar da subárvore direita
        else if(A->Info < dado)
            RemoveAVLRec(A->Dir, dado);
        // Se encontrarmos o nó a ser removido
        else{
            Arvore aux = A;
            // Caso 1: Nó é uma folha
            // Atualiza o nó que passa a ser nulo e libera a memória
            if(A->Esq == nullptr && A->Dir == nullptr){
                delete(aux);
                A = nullptr;
            }
            // Caso 2: Nó tem apenas um filho
            //Atualiza o nó que passa a ser o filho (esquerdo ou direito) e libera o nó antigo
            else if(A->Esq == nullptr){
                A = A->Dir;
                delete(aux);
            }
            else if(A->Dir == nullptr){
                A = A->Esq;
                delete(aux);
            }      
            // Caso 3: Nó tem dois filhos
            else{
            // Encontrar o nó mais à direita da subárvore esquerda (maior dos menores), trocar os valores entre os dois nós e retirar o nó da subárvore esquerda (maior valor dos valores menores que a raiz)
            aux = Maximo(A->Esq); //Acha o nó mais a direita da árvore esquerda (maior valor)
            A->Info = aux->Info; //Aloca o valor armazenado no nó encontrado no nó atual (que quero excluir)
            RemoveAVLRec(A->Esq, aux->Info); // Remove o nó mais à direita da subárvore esquerda
            
            // Ou encontrar o nó mais à esquerda da subárvore direita (menor dos maiores), trocar os valores entre os dois nós e retirar o nó da subárvore esquerda (maior valor dos valores menores que a raiz)
            //aux = Minimo(A->Dir); //Acha o nó mais a esquerda da árvore direita (menor valor)
            //A->Info = aux->Info; //Aloca o valor armazenado no nó encontrado no nó atual (que quero excluir)
            //RemoveAVLRec(A->Dir, aux->Info); // Remove o nó mais à esdquerda da subárvore direita
            }

        }
    }
    // Se a árvore se tornou vazia após a remoção
    if(!A)
        return;

    // Atualiza a altura
    AtualizaAltura(A);
    // Atualiza o fator de balanceamento
    AtualizaFB(A);
    //Confere a necessidade de rebalancear a árvore 
    BalanceiaNo(A);
} 

//Esvazia a árvore
void EsvaziaArvore(Arvore &A){
    if(A){
        EsvaziaArvore(A->Dir);
        EsvaziaArvore(A->Esq);
        delete A;
        A = nullptr;
    }
}

//Busca um valor na árvore
bool BuscaNo(Arvore A, int dado){
    // A função começa sua “busca” pela raiz, caso a raiz seja nula (árvore vazia) ou a informação seja igual ao dado armazenado na raiz, a função devolve a raiz (o nó foi encontrado ou a árvore é nula)
    if(!A || A->Info == dado)
        return A != nullptr; // Se A não for nulo, retorna true, caso contrário, retorna false
    else{
        // se a informação for maior que o dado da raiz, prosseguimos pela subarvore direita
        if(A->Info < dado)
            return BuscaNo(A->Dir, dado);
        // Caso contrário, prosseguimos pela subarvore esquerda
        else
            return BuscaNo(A->Esq, dado);
    }
} 

//Percurso Pré-Ordem: raiz - sub-arvore esquerda - sub-arvore direita
void PreOrdem(Arvore A){
    if(A){
        printf("%d (H = %d, FB= %d)  ", A->Info, A->Altura, A->FB);
        PreOrdem(A->Esq);
        PreOrdem(A->Dir);
    }
} 

// Percurso Em Ordem: sub-arvore esquerda - raiz - sub-arvore direita
void Ordem(Arvore A){
    if(A){
        Ordem(A->Esq);
        printf("%d (H = %d, FB= %d)  ", A->Info, A->Altura, A->FB);
        Ordem(A->Dir);
    }    
} 

//Percurso Pós Ordem: sub-arvore esquerda - sub-arvore direita - raiz
void PosOrdem(Arvore A){
    if(A){
        PosOrdem(A->Esq);
        PosOrdem(A->Dir);
        printf("%d (H = %d, FB= %d)  ", A->Info, A->Altura, A->FB);
    }
}

// Rotação à Esquerda
Arvore RotacaoEsquerda(Arvore A) {
    // Armazena o filho direito da antiga raiz (o novo nó raiz após a rotação à esquerda)
    Arvore novaRaiz = A->Dir;
    // Armazena o neto esquerdo da subárvore direita da antiga raiz 
    Arvore netoEsquerdo = novaRaiz->Esq;

    // A antiga raiz (A) se torna o filho esquerdo da nova raiz
    novaRaiz->Esq = A;
    // O neto esquerdo da subárvore direita da antiga raiz se torna o filho direito do filho esquerdo da nova raiz
    A->Dir = netoEsquerdo;

    // Atualiza a altura dos nós
    AtualizaAltura(A);
    AtualizaAltura(novaRaiz);

    // Atualiza o fator de balanceamento dos nós
    AtualizaFB(A);
    AtualizaFB(novaRaiz);

    // Retorna a nova raiz após a rotação
    return novaRaiz;
}

//  Rotação à Direita
Arvore RotacaoDireita(Arvore A) {
    // Armazena o filho esquerdo da antiga raiz (o novo nó raiz após a rotação à esquerda)
    Arvore novaRaiz = A->Esq;
    // Armazena o neto direito da subárvore esquerda da antiga raiz 
    Arvore netoDireito = novaRaiz->Dir;

    // A antiga raiz (A) se torna o filho direito da nova raiz
    novaRaiz->Dir = A;
    // O neto direito da subárvore esquerda da antiga raiz se torna o filho esquerdo do filho direito da nova raiz
    A->Esq = netoDireito;

    // Atualiza a altura dos nós
    AtualizaAltura(A);
    AtualizaAltura(novaRaiz);

    // Atualiza o fator de balanceamento dos nós
    AtualizaFB(A);
    AtualizaFB(novaRaiz);

    // Retorna a nova raiz após a rotação
    return novaRaiz;
}

// Rotação Esquerda-Direita
Arvore RotacaoEsquerdaDireita(Arvore A) {
    // Realiza a rotação à esquerda na subárvore esquerda 
    A->Esq = RotacaoEsquerda(A->Esq);
    // Realiza a rotação à direita na árvore original (ainda desbalanceada)    
    return RotacaoDireita(A);
}

// Rotação Direita-Esquerda
Arvore RotacaoDireitaEsquerda(Arvore A) {
    // Realiza a rotação à direita na subárvore direita 
    A->Dir = RotacaoDireita(A->Dir);
    // Realiza a rotação à esquerda na árvore original (ainda desbalanceada)    
    return RotacaoEsquerda(A);
}

//Conta o número de nós da árvore
int ContaNos(Arvore A){
    if(A) //Se A não é nulo
        return 1 + ContaNos(A->Dir) + ContaNos(A->Esq);
    return 0;
} 

//Retorna o valor mínimo da árvore (descendente mais a esquerda da árvore)
Arvore Minimo(Arvore A){
    //A função começa sua “busca” pela raiz, caso a raiz seja nula (árvore vazia) ou a sub-árvore esquerda seja nula, a função devolve a raiz
    if(!A || !A->Esq)
        return A;
    //Caso contrário, continuará sua busca pela sub-árvore esquerda recursivamente até chegar no menor valor
    else
        return Minimo(A->Esq);
}

//Retorna o valor máximo da árvore (descendente mais a direita da árvore)
Arvore Maximo(Arvore A){
    //A função começa sua “busca” pela raiz, caso a raiz seja nula (árvore vazia) ou a sub-árvore direita seja nula, a função devolve a raiz
    if(!A || !A->Dir)
        return A;
    //Caso contrário, continuará sua busca pela sub-árvore direita recursivamente até chegar no maior valor
    else
        return Maximo(A->Dir);
} 

// Função que retorna a altura de uma árvore
int AlturaArvore(Arvore A){
    if (A == NULL) return -1; // A altura de uma árvore vazia é -1
    return A->Altura; // Retorna a altura armazenada no nó
}

// Função que atualiza a altura de um nó
void AtualizaAltura(Arvore A) {
    if (A) {
        // Atualiza a altura do nó com base nas alturas das subárvores esquerda e direita
        // A altura é 1 + a maior altura entre os filhos esquerdo e direito
        A->Altura = 1 + max(AlturaArvore(A->Esq), AlturaArvore(A->Dir));
    }
}

// Função para calcular o fator de balanceamento de um nó
int CalculaFB(Arvore A) {
    if (!A) return 0;  // O fator de balanvceamento de uma árvore vazia é 0 
    return AlturaArvore(A->Esq) - AlturaArvore(A->Dir); // Retorna o fator de balanceamento do nó (Altura da subárvore esquerda - Altura da subárvore direita)
}

// Função para atualizar o fator de balanceamento de um nó
void AtualizaFB(Arvore A) {
    if (A) {
        // Atualiza o fator de balanceamento do nó atual
        A->FB = CalculaFB(A);
        // Chama recursivamente a função AtualizaFB para a subárvore esquerda
        AtualizaFB(A->Esq);
        // Chama recursivamente a função AtualizaFB para a subárvore direita
        AtualizaFB(A->Dir);
    }
}

//Realiza, se necessário, o balanceamento da árvore após a inserção e a remoção de um novo elemento
void BalanceiaNo(Arvore &A){
    // Verifica se é necessário fazer rotações
    int fb = A->FB;
    // Rotação à Esquerda
    if(fb < -1 && CalculaFB(A->Dir) <= 0)
        A = RotacaoEsquerda(A);

    // Rotação à Direita
    else if(fb > 1 && CalculaFB(A->Esq) >= 0)
        A = RotacaoDireita(A);

    // Rotação Dupla à Esquerda
    else if(fb > 1 && CalculaFB(A->Esq) < 0)
        A = RotacaoEsquerdaDireita(A);

    // Rotação Dupla à Direita
    else if(fb < -1 && CalculaFB(A->Dir) > 0)
        A = RotacaoDireitaEsquerda(A);
}

// Função auxiliar para calcular o máximo entre dois valores inteiros
// a,b -> altura de dois nós da árvore
int max(int a, int b) {
    return (a > b) ? a : b;
}
