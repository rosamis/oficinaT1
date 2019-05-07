#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"
#include "multiplica.h"

noh* oversoma(lista *l, noh *aux, int soma) {

    if (soma < 10) {        
        aux->chave = soma;
        return aux;
    }

    int overflow_soma = (soma)/10;
    int x_soma = (soma)%10;
    aux->chave = x_soma;

    if (aux->ant == NULL) { 
        inserir_inicio(l, overflow_soma); 
        return aux;
    } else {
        int s = aux->ant->chave + overflow_soma;
        return oversoma(l,aux->ant, s);
    }
}

void multi (lista *l3, lista *l1, lista *l2){

	noh *auxiliar1 = l1->fim;
	noh *auxiliar2 = l2->fim;
    inserir_inicio(l3, 0); 
	noh *auxiliar3 = l3->fim; 
	noh *fixo3 = l3->fim;  

    while (auxiliar2 != NULL){
        while (auxiliar1 != NULL) {

            int mult = auxiliar2->chave * auxiliar1->chave;
            int x;
            int overflow_mul = -1;

            if (mult > 9){
                overflow_mul = (mult)/10;
                x = (mult)%10;
            } else {
                x = mult;
            }


            if (auxiliar3 == NULL) {
                inserir_inicio(l3, x); 
                auxiliar3 = l3->comec;

            } else {
    
                int soma = auxiliar3->chave + x;
                oversoma(l3,auxiliar3,soma);
            }

            if (overflow_mul != -1) {
                if (auxiliar3->ant == NULL) {
                    inserir_inicio(l3, overflow_mul); 
                   
                } else {

                    int soma = auxiliar3->ant->chave + overflow_mul;
                    oversoma(l3,auxiliar3->ant,soma);
                }
            }

            auxiliar1 = auxiliar1->ant;
            auxiliar3 = auxiliar3->ant;

        }

        auxiliar1 = l1->fim;
        auxiliar2 = auxiliar2->ant;

        if (fixo3->ant == NULL) {
            inserir_inicio(l3, 0);
        }

        fixo3 = fixo3->ant;
        auxiliar3 = fixo3;

    }
}


int main(){
    bool invertido = false;
    char nome_arquivo[100];
    char nome_saida[20]="ResultadoMul.txt";

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

    if (l1->tam == l2->tam){
        multi (l3, l1, l2);

    }else if (l1->tam < l2->tam){
        multi (l3, l2, l1);
    }else if (l1->tam > l2->tam){
        multi (l3, l1, l2);
    }

    remove_zero_esquerda(l3);
    
	escreve_arquivo(nome_saida,l3,invertido);

	return 0;
}                          