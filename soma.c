#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"
#include "soma.h"


int main(){

	bool invertido = false;
    char nome_arquivo[100];
    char nome_saida[20]="ResultadoSom.txt";

	printf("%s\n","Entre com o nome do arquivo .txt: " );
	scanf("%s", nome_arquivo);

	int x, overflow;

	lista *l1, *l2, *l3; 

	l1=(lista *)malloc(sizeof(lista));
	l2=(lista *)malloc(sizeof(lista));
	l3=(lista *)malloc(sizeof(lista));

	inicia(l1);
	inicia(l2);
	inicia(l3);

	le_arquivo(nome_arquivo,l1,l2);

	noh *auxiliar1 = l1->fim;
	noh *auxiliar2 = l2->fim;

	while (!(auxiliar1 == NULL && auxiliar2 == NULL)){


		int soma;
		if (auxiliar1 == NULL) {
			soma = auxiliar2->chave;
		} else if (auxiliar2 == NULL) {
			soma = auxiliar1->chave;
		} else {
			soma = auxiliar1->chave + auxiliar2->chave;
		}
		if (soma > 9){

			overflow = (soma)/10;
			x=(soma)%10;
			inserir_inicio(l3, x); 
			noh *anterior1 = auxiliar1->ant;
			noh *anterior2 = auxiliar2->ant;
			if (anterior1 == NULL && anterior2 == NULL) {
				inserir_inicio(l3, overflow); 				
			} else if ((anterior1 != NULL && anterior2 != NULL) || (anterior1 != NULL && anterior2 == NULL)) {
				anterior1->chave=anterior1->chave + overflow;
			} else if (anterior1 == NULL && anterior2 != NULL) {
				anterior2->chave = anterior2->chave + overflow;
			}

		}else{

			inserir_inicio(l3, soma);

		}

		if(auxiliar1 != NULL)
			auxiliar1 = auxiliar1->ant;
		if (auxiliar2 != NULL)
			auxiliar2 = auxiliar2->ant;

	}

	remove_zero_esquerda(l3);

	escreve_arquivo(nome_saida,l3,invertido);

	return 0;
}
