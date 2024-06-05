#include <stdio.h>
#include <stdlib.h>
#include "avl.hpp"

// Funções de menu e entrada do usuário

// itens do menu
const char * menu[] ={
    "Sair",
    "Inserir elemento",
    "Remover elemento",
    "Imprimir arvore",
    "Exemplo"
};

// Exibir menu
void showMenu(){

    printf("\nMenu:\n");
    // sizeof(menu)/sizeof(menu[0] dá o número de elementos do array de chars
    // sizeof(menu) retorna o tamanho total do array menu em bytes
    // sizeof(menu[0]) retorna o tamanho de um elemento do array menu em bytes, que neste caso é um ponteiro para char (uma string)
    // Ao dividir o tamanho total do array pelo tamanho de um elemento, obtemos o número total de elementos no array. 
    // Isso funciona porque o array menu é um array de ponteiros para char, e todos os ponteiros têm o mesmo tamanho em bytes na memória, 
    //independentemente do conteúdo ao qual apontam.
    for (size_t i = 0; i < sizeof(menu)/sizeof(menu[0]); i++)
    {
        printf("\n\t%zu. %s", i, menu[i]);
    }
    printf("\nSua opcao? << ");
}

// Captura a opção do usuário
size_t getUserOption(){
    //size_t é um número inteiro sem sinal (unsigned) - garante que o valor não é negativo
    size_t op, ok;
    ok = 1;
    do
    {
        fflush(stdin); // descarta qualquer lixo anterior
        // se opção digitada for inválida, informa o usuário
        if (ok!=1)
        {
            printf("\nOpcao inexistente ou invalida, tente novamente!\n\n");
        }
        // exibe as opções do menu
        showMenu();
        // somente inteiros positivos menores que o tamanho do array (Nº de itens do menu) são aceitos
        ok = scanf("%zu", &op) && op<sizeof(menu)/sizeof(menu[0]);
    } while (ok != 1);
    // repete qual foi a opção digitada
    printf("\nSua opcao foi %zu: %s\n\n", op, menu[op]);
    return op;
}

int main(){

    Arvore A;
    IniciaArvore(A);

    size_t op;
    int dado;

    do{
        // captura opção
        op = getUserOption();
        // executa
        switch (op)
        {
        // insere novo nó
        case 1:
            // pergunta qual o elemento será inserido
            printf("Informe o elemento a ser inserido na arvore: ");
             // lê entrada do usuário            
            scanf("%d", &dado);
            InsereAVLRec(A, dado);
            break;
        // remove nó
        case 2: 
            // pergunta qual o elemento será removido
            printf("Informe o elemento a ser removido da arvore: ");
             // lê entrada do usuário            
            scanf("%d", &dado);
            
            // confere se a árvore está vazia
            if(!ArvoreVazia(A)){
                // confere primeiro se o elemento existe na árvore
                if(BuscaNo(A, dado)){
                    RemoveAVLRec(A, dado);
                }
                else printf("\nElemento nao encontrado!\n");
            }
            else printf("\nArvore Vazia\n");
            break;
        // imprime a árvore em pós-ordem, ordem e pré-ordem
        case 3:
            imprimeArvore(A);
            break;
        // Exemplo
        case 4:
            // Cria e inicia árvore Exemplo
            Arvore Exemplo;
            IniciaArvore(Exemplo);

            // Inserção de elementos na árvore Exemplo
            InsereAVLRec(Exemplo, 15);
            InsereAVLRec(Exemplo, 27);
            InsereAVLRec(Exemplo, 49); // Rotação à Esquerda
            InsereAVLRec(Exemplo, 10);
            InsereAVLRec(Exemplo, 8); // Rotação à Direita
            InsereAVLRec(Exemplo, 67);
            InsereAVLRec(Exemplo, 59); // Rotação Direita-Esquerda
            InsereAVLRec(Exemplo, 9);
            InsereAVLRec(Exemplo, 13);
            InsereAVLRec(Exemplo, 20);
            InsereAVLRec(Exemplo, 14); // Rotação Esquerda-Direita

            //Impressão da árvore
            imprimeArvore(Exemplo);
            
            //liberar a árvore
            EsvaziaArvore(Exemplo);            
            break;
        default:
            break;
        }
    }
    while (op != 0); // opção 0 é para terminar a execução

    //liberar a árvore
    EsvaziaArvore(A);
    return 0;
}

