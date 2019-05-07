#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"
#include "multiplica.h"

noh* oversoma(lista *l, noh *aux, int soma) {
    if (soma < 10) {        //enquanto soma > 10 recursao, ateachar uma menor que 10
        aux->chave = soma;
        return aux;
    }
    int overflow_soma = (soma)/10;
    int x_soma = (soma)%10;
    aux->chave = x_soma;
    if (aux->ant==NULL) { //n tem nd pra somar, adc anterior
        inserir_inicio(l, overflow_soma); 
        printf("inseriu inicio l3 na soma, overflow_soma=%d\n", overflow_soma);
        return aux;
    } else {
        int s = aux->ant->chave + overflow_soma;
        printf("recursao overflow soma=%d\n", s);
        return oversoma(l,aux->ant, s);
    }
}

void multi (lista *l3, lista *l1, lista *l2){

	noh *auxiliar1=l1->fim;
	noh *auxiliar2=l2->fim;
    inserir_inicio(l3, 0); 
	noh *auxiliar3=l3->fim; //anda junto com o l1
	noh *fixo3=l3->fim;  // marca onde tem que comecar a somar o total com a multiplicacao

    while (auxiliar2!=NULL){
        while (auxiliar1!=NULL) {
            printf("-----------------------------------------\n");
            printf("chave1=%d\n", auxiliar1->chave);
            printf("chave2=%d\n", auxiliar2->chave);

            int mult = auxiliar2->chave * auxiliar1->chave;
            printf("mult=%d\n", mult);

            int x;
            int overflow_mul = -1;
            if (mult > 9){
                printf("mult>9\n");
                overflow_mul = (mult)/10;
                x = (mult)%10;
            } else {
                x = mult;
            }

            printf("x=%d\n", x);
            printf("overflow mul=%d\n", overflow_mul);
            if (auxiliar3==NULL) {
                inserir_inicio(l3, x); 
                auxiliar3 = l3->comec;
                printf("inseriu inicio l3, x=%d\n", x);
            } else {
                printf("somou l3, chave=%d+x=%d\n", auxiliar3->chave, x);
                int soma = auxiliar3->chave + x;
                oversoma(l3,auxiliar3,soma);
            }

            if (overflow_mul!=-1) {
                if (auxiliar3->ant==NULL) {
                    inserir_inicio(l3, overflow_mul); 
                    printf("inseriu inicio l3, overflow_mul=%d\n", overflow_mul);
                } else {
                    printf("somou l3, chave=%d+overflow_mul=%d\n", auxiliar3->ant->chave, overflow_mul);
                    int soma = auxiliar3->ant->chave + overflow_mul;
                    oversoma(l3,auxiliar3->ant,soma);
                }
            }

            auxiliar1 = auxiliar1->ant;
            if (auxiliar1!=NULL) { //so print
                printf("aux1 apontando para=%d\n", auxiliar1->chave);
            }
            auxiliar3 = auxiliar3->ant;
            if (auxiliar3!=NULL) {
                printf("aux3 apontando para=%d\n", auxiliar3->chave);
            }

            printf("lista1:\n");
            imprime_lista(l1);
            printf("lista2:\n");
            imprime_lista(l2);
            printf("lista3:\n");
            imprime_lista(l3);
        }

        printf("move l2 e l3\n");
        auxiliar1 = l1->fim;
        printf("aux1 apontando para=%d pppppp\n", auxiliar1->chave);
        auxiliar2 = auxiliar2->ant;
        if (auxiliar2!=NULL) {
            printf("aux2 apontando para=%d\n", auxiliar2->chave);
        }
        printf("passou l1,l2\n");

        if (fixo3->ant==NULL) {
            inserir_inicio(l3, 0);
        }
        fixo3 = fixo3->ant;
        auxiliar3 = fixo3;
        if (auxiliar3!=NULL) {
            printf("aux3 apontando para=%d\n", auxiliar3->chave);
        }
        printf("passou l1,l2,l3\n");
    }
}

int main(){
    bool invertido = false;
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

	printf("leu arquivo!\n");

    //x=1;
	//inserir_inicio(l3, x);
   // x=8;
	//inserir_inicio(l3, x);



    if (l1->tam == l2->tam){
        //multiplica
        printf("entrou tam1=tam2!\n");
        multi (l3, l1, l2);

    }else if (l1->tam < l2->tam){
        //multiplica invertido
        printf("entrou tam1<tam2!\n");
        multi (l3, l2, l1);
    }else if (l1->tam > l2->tam){
        //multiplica 
        printf("entrou tam1>tam2!\n");
        multi (l3, l1, l2);
    }


	printf("lista1:\n");
	imprime_lista(l1);
	printf("lista2:\n");
	imprime_lista(l2);


//	remove_zero_esquerda(l3);

	printf("lista3:\n");
	imprime_lista(l3);

	escreve_arquivo(l3,invertido);

	return 0;


}                          