#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"
#include "subtrai.h"

noh* empresta(noh *atual) {

    int chave = atual->chave;

    if (atual == NULL)
        return atual->ant;

    if (chave>0) {
        if (atual->prox == NULL) {
            return atual;
        }
    	atual->chave=chave-1;
    	atual->prox->chave=atual->prox->chave+10;
    	return empresta(atual->prox);
    }

    return empresta(atual->ant);
}


void subtrai (lista *l3, lista *l1, lista *l2){  

	noh *auxiliar1=l1->fim;
	noh *auxiliar2=l2->fim;

	while (!(auxiliar1 == NULL && auxiliar2 == NULL)){            

		int sub;

		if(auxiliar2 == NULL){
			sub = auxiliar1->chave;
		}

		if (auxiliar2 != NULL && auxiliar1->chave < auxiliar2->chave){  
			empresta(auxiliar1->ant);
		}

		if (auxiliar1 != NULL && auxiliar2 != NULL) {
			sub = auxiliar1->chave - auxiliar2->chave;
		}

		inserir_inicio(l3,sub);
		remover_fim(l1);
		remover_fim(l2);

		if(auxiliar1 != NULL)
			auxiliar1=auxiliar1->ant;

		if (auxiliar2 != NULL)
			auxiliar2=auxiliar2->ant;
	}
}



int main(){

    char nome_arquivo[100];
    char nome_saida[20]="ResultadoSub.txt";
    bool invertido = false;
	
	printf("%s\n","Entre com o nome do arquivo .txt: " );
	scanf("%s", nome_arquivo);
	
	lista *l1, *l2, *l3; 

	l1=(lista *)malloc(sizeof(lista));
	l2=(lista *)malloc(sizeof(lista));
	l3=(lista *)malloc(sizeof(lista));

	inicia(l1);
	inicia(l2);
	inicia(l3);

	le_arquivo(nome_arquivo,l1,l2);

	noh *auxiliar1=l1->comec;
	noh *auxiliar2=l2->comec;

	if (l1->tam == l2->tam){
            
		while (auxiliar1->chave == auxiliar2->chave){
			auxiliar1 = auxiliar1->prox;
			auxiliar2 = auxiliar2->prox;
			
			if (auxiliar1 == NULL){
				inserir_fim(l3,0);
					break;
			}else if (auxiliar1->chave < auxiliar2->chave){
				subtrai(l3,l2,l1);
				invertido = true;
			}else if (auxiliar1->chave > auxiliar2->chave){
				subtrai(l3,l1,l2);
			}
		}
	}else if (l1->tam > l2->tam){
		subtrai(l3,l1,l2);

	}else if (l1->tam < l2->tam){
			subtrai(l3,l2,l1);
			invertido = true;
	}
			
	remove_zero_esquerda(l3);

	escreve_arquivo(nome_saida,l3,invertido);
	
	return 0;
}
