#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"
#include "subtrai.h"

noh* empresta(noh *atual) {
    int chave = atual->chave;
    printf("chave rec %d\n", chave);
    if (atual==NULL)
        return atual->ant;
    if (chave>0) {
        if (atual->prox==NULL) {
            return atual;
        }
    	atual->chave=chave-1;
    	atual->prox->chave=atual->prox->chave+10;
    	return empresta(atual->prox);
    }
    return empresta(atual->ant);
}


void subtrai (lista *l3, lista *l1, lista *l2){  //são do mesmo tamanho e que o l1 > l2

	noh *aux1=l1->fim;
	noh *aux2=l2->fim;

	while (!(aux1==NULL && aux2==NULL)){             //   ();

		if(aux1!=NULL)
			printf("aux1=%d!\n", aux1->chave);
		if (aux2!=NULL)
			printf("aux2=%d!\n", aux2->chave);

		int sub;
		if(aux2==NULL){
			sub = aux1->chave;//inserir_inicio(l3,aux1->chave);
		}

		if (aux2!=NULL && aux1->chave < aux2->chave){  //empresta
			empresta(aux1->ant);
		}

		if (aux1!=NULL && aux2!=NULL) {
			sub = aux1->chave - aux2->chave;
		}
		printf("sub=%d!\n", sub);

		inserir_inicio(l3,sub);
		remover_fim(l1);
		remover_fim(l2);

		if(aux1!=NULL)
			aux1=aux1->ant;
		if (aux2!=NULL)
			aux2=aux2->ant;
	}
}



int main(){

    char nome_arquivo[100];
	printf("%s\n","Entre com o nome do arquivo .txt: " );
	scanf("%s", nome_arquivo);
	
	printf("leu nome_arquivo %s\n", nome_arquivo);


	lista *l1, *l2, *l3; 

	l1=(lista *)malloc(sizeof(lista));
	l2=(lista *)malloc(sizeof(lista));
	l3=(lista *)malloc(sizeof(lista));

	
	printf("malloc!\n");

	inicia(l1);
	inicia(l2);
	inicia(l3);

	printf("inicia!\n");

	le_arquivo(nome_arquivo,l1,l2);



	printf("build numbers!\n");


	noh *auxiliar1=l1->comec;
	noh *auxiliar2=l2->comec;

	printf("antes!\n");
    bool invertido = false;
	printf("depois!\n");

	if (l1->tam==l2->tam){
		//while do começo ate achar diferente, verifica quem é maior e inverte, subtrai.. subtrai invertido
            
        printf("aqui!\n");
		while (auxiliar1->chave == auxiliar2->chave){
            printf("aux1=%d aux2=%d!\n", auxiliar1->chave,auxiliar2->chave);
			auxiliar1 = auxiliar1->prox;
			auxiliar2 = auxiliar2->prox;
			
			if (auxiliar1==NULL){
				inserir_fim(l3,0);
					printf("insere fim!\n");
					break;
			}else if (auxiliar1->chave < auxiliar2->chave){
				//subtrai invertido
				subtrai(l3,l2,l1);
					printf("subtraiu!\n");
				invertido = true;
			}else if (auxiliar1->chave > auxiliar2->chave){
				//subtrai normal
				subtrai(l3,l1,l2);
					printf("subtraiu!\n");
			}
		}
	}else if ((l1->tam)>(l2->tam)){
		printf("tam1>tam2!\n");
		subtrai(l3,l1,l2);
		printf("subtraiu normal!\n");
	}else if ((l1->tam)<(l2->tam)){
		//subtrai invertido e l3->comec=l3->comec*(-1)
			subtrai(l3,l2,l1);
			invertido = true;
	}
			
	printf("passou laco!\n");
		
	printf("lista1:\n");
	imprime_lista(l1);
	printf("lista2:\n");
	imprime_lista(l2);


	remove_zero_esquerda(l3);

	printf("lista3:\n");
	imprime_lista(l3);

	escreve_arquivo(l3,invertido);

	return 0;
}
