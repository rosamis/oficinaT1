#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"

void inicia(lista* l){

	l->tam = 0;
	l->comec = NULL;
	l->fim = NULL;

}

noh *cria_noh(int x){
    
	noh* n = (noh*)malloc(sizeof(noh));
	n->prox = NULL;
	n->ant = NULL;
	n->chave = x;
	return n;
    
}

void inserir_inicio(lista *l, int x){ 

    noh* n = cria_noh(x);
	if(l->tam == 0){
		l->comec = n;
		l->fim = n;

	}else{

		n->prox = l->comec;
		l->comec->ant = n;
		l->comec = n;
		
	}

	l->tam++;

}

void inserir_fim(lista *l, int x){

    noh* n = cria_noh(x);
    
	if(l->tam == 0){

		l->comec = n;
		l->fim = n;

	}else{

		l->fim->prox = n;
		n->ant = l->fim;
		l->fim = n;
	}
    l->tam++;
}

void remover_fim(lista *l){

    noh *atu = l->fim;

    if (atu == NULL)
        return;
    
    noh *ant = atu->ant;

    if (ant != NULL) {
        l->fim = ant;
        ant->prox = NULL;

    } else {
        l->comec = NULL;
        l->fim = NULL;
    }

    free (atu);
    l->tam--;
}

void remover_inicio(lista *l){

    noh *atu = l->comec;

    if (atu == NULL)
        return;

    noh *proxi = atu->prox;

    if (proxi != NULL) {
        l->comec = proxi;
        proxi->ant = NULL;
    } else {
        l->comec = NULL;
        l->fim = NULL;
    }

    free (atu);
    l->tam--;
}

void remove_zero_esquerda(lista *l3){

    noh *aux = l3->comec;

	while (aux->chave == 0){
		if (aux->prox == NULL){
			return;
		}

		remover_inicio(l3);
		aux = aux->prox;
	}
}

void le_arquivo(char nome_arquivo[], lista *l1, lista *l2){

	char ch;
	FILE *fp;
	fp = fopen(nome_arquivo, "r");

	if(fp == NULL){
		printf("%s\n","Erro na abertura do arquivo!" );
		exit(1);
	}

	lista *aux = l1;

	while((ch = fgetc(fp)) != EOF){ 

		if (ch == ' '){
			aux = l2;
			continue;
		}

		int r = ch;			
		if (r > 47 && r < 58) {
			int i = ch - '0';
			inserir_fim(aux, i);
		}
	}

	fclose(fp);
}

void escreve_arquivo (char nome_saida[],lista *l3, bool invertido){
	
  FILE *fp;
  fp = fopen(nome_saida ,"w");

  if (fp == NULL){
   printf("Um erro ocorreu ao tentar criar o arquivo.\n");
   }

  noh *aux = l3->comec;

  if (invertido == true) {
  	fputc('-', fp);
  }

  while( aux != NULL) {
    char ch = aux->chave +'0';
    int r = ch;
    if (r > 47 && r < 58) {
      fputc(ch, fp);
    }
      aux = aux->prox;
  }

	printf("Arquivo escrito com sucesso");
	
  fclose(fp);
}

