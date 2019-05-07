#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"
#include "soma.h"

int main(){

	bool invertido = false;

    char nome_arquivo[100];
	printf("%s\n","Entre com o nome do arquivo .txt: " );
	scanf("%s", nome_arquivo);
	
	printf("leu nome_arquivo %s\n", nome_arquivo);

	int x, overflow;

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

	noh *aux1=l1->fim;
	noh *aux2=l2->fim;

	while (!(aux1==NULL && aux2==NULL)){


		int soma;
		if (aux1==NULL) {
			soma = aux2->chave;
		} else if (aux2==NULL) {
			soma = aux1->chave;
		} else {
			soma = aux1->chave + aux2->chave;
		}
		printf("soma=%d\n",soma);
		if ((soma) > 9){

			overflow = (soma)/10;
			x=(soma)%10;
			inserir_inicio(l3, x); 
			printf("inseriu inicio l3!\n");
			noh *anterior1 = aux1->ant;
			noh *anterior2 = aux2->ant;
			if (anterior1==NULL && anterior2==NULL) {
				inserir_inicio(l3, overflow); 				
			} else if ((anterior1!=NULL && anterior2!=NULL) || (anterior1!=NULL && anterior2==NULL)) {
				anterior1->chave=anterior1->chave + overflow;
			} else if (anterior1==NULL && anterior2!=NULL) {
				anterior2->chave=anterior2->chave + overflow;
			// } else if (anterior1!=NULL && anterior2!=NULL) {  // se não fazer o || em cima
				// anterior1->chave=anterior1->chave + overflow;
			}
			printf("somou overflow!\n");

		}else{

			inserir_inicio(l3, soma); 
			printf("inseriu inicio l3 sem overflow!\n");

		}

		if(aux1!=NULL)
			aux1=aux1->ant;
		if (aux2!=NULL)
			aux2=aux2->ant;

	}

	imprime_lista(l3);

	escreve_arquivo(l3,invertido);

	return 0;
}
