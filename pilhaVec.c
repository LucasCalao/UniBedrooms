/*
 * pilhaVec.c
 */
#include <stdlib.h>

#include "pilha.h"

/* Estrutura de dados: pilha ---> comportamento “Ultimo a chegar, Primeiro a sair” */
struct _pilha{
	void ** elems;
	int numElems;
	int capacidade;
};

pilha criaPilha(int cap){
	pilha p = (pilha) malloc(sizeof(struct _pilha));
	if (p == NULL) return NULL;
	p->elems = malloc(sizeof(void *)*cap);
	if (p->elems == NULL){
		free(p);
		return NULL;
	}
	p->capacidade = cap;
	p->numElems = 0;
	return p;
}

void destroiPilha (pilha p ){
	free(p->elems);
	free(p);
}

void destroiPilhaEElems(pilha p, void (*destroi)(void *) ){
	int i =0;
	for(;i<p->numElems;i++)
		destroi(p->elems[i]);
	free(p->elems);
	free(p);
}

int vaziaPilha(pilha p){
	if (p->numElems == 0)
		return 1;
	return 0;
}

int tamanhoPilha(pilha p){
	return p->numElems;
}

void * topoPilha(pilha p){
	return p->elems[p->numElems-1];
}
/* Aumenta o vector da pilha */
void incPilha (pilha p){
	int i = 0;
	void ** aux = malloc(sizeof(void * ) * p->capacidade*2); // duplica
	for (;i<p->numElems;i++)
		aux[i] = p->elems[i];
	free(p->elems);
	p->elems = aux;
	p->capacidade = p->capacidade * 2;
}

void emPilha(pilha p, void * elem){
	if (p->capacidade == p->numElems)
		incPilha(p);
	p->elems[p->numElems++] = elem;
}

void * desemPilha(pilha p){
	p->numElems--;
	return p->elems[p->numElems];
}

