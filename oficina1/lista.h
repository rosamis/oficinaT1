#ifndef __LISTA__
#define __LISTA__


typedef struct Noh{

	int chave;
	struct Noh *prox, *ant;

}noh;

typedef struct Lista{

	noh *comec, *fim;
	int tam;

}lista;

void inicia(lista* l);
noh *cria_noh(int x);
void inserir_inicio(lista *l, int x);
void inserir_fim(lista *l, int x);
void remover_fim(lista *l);
void remover_inicio(lista *l);
void remove_zero_esquerda(lista *l3);
void imprime_lista(lista *l);
void le_arquivo(char nome_arquivo[], lista *l1, lista *l2);
void escreve_arquivo (lista *l3, bool invertido);


#endif