#include <stdlib.h>
#include "iterador.h"
#include "sequencia.h"

/* Estrutura de dados: sequencia implementada em vector */
struct _sequencia{
	void * * elems; // apontador para vector de enderecos de elementos
	int numElems;
	int capacidade; // capacidade corrente do vectorC:\Users\Germa\Desktop\2�Ano Faculdade\2�SEMESTRE\AED PRATICA\Turma\turma.c
};

void incCapacidadeSequencia(sequencia f){
    int i;
    void ** aux = malloc(sizeof(void *) * f->capacidade*2); //duplica
    for(i = 0 ; i<f->numElems ; i++)
        aux[i] = f->elems[i];
    free(f->elems);
    f->elems = aux;
    f->capacidade = f->capacidade * 2;
}

sequencia criaSequencia(int cap){

    sequencia s = (sequencia) malloc (sizeof(struct _sequencia));

	if (s == NULL)
        return NULL;
    //s->elems � um apontador void *
	s->elems = (void *) malloc (sizeof(void*) * cap); //(void *) � redodante (nao � necessario)
	if (s->elems == NULL){
		free(s);
		return NULL;
	}
	s->numElems = 0;
	s->capacidade = cap;
	return s;
}


void destroiSequencia (sequencia s ){
	//ordem inversa � criacao dos mallocs
	free(s->elems);
	free(s);
}
// void (*destroi) (void *)
//apontador para funcao que retorna void e recebe um void*
void destroiSeqElems(sequencia s, void (*destroi)(void *) ){
	int i;
	for(i = 0; i < s->numElems; i++){
        destroi(s->elems[i]);
	}
	free(s->elems); //liberta a memoria do malloc
	free(s);
}


int vaziaSequencia(sequencia s){
    if(s->numElems == 0){
        	return 1;
    }
	return 0;

	//alternativa
	//return s->numElems == 0 ;
}


int tamanhoSequencia(sequencia s){
	return s->numElems;
}


void * elementoPosSequencia(sequencia s, int i){
    return s->elems[i-1];//primeira posicao do elems � 0 mas o primeiro valor de i � 1
}


void adicionaPosSequencia(sequencia s, void * elem, int i){

    int k;
    if(s->capacidade == s->numElems){
        incCapacidadeSequencia(s); //TPC
        //i=3 elem=1
        // initial 6 4 5 9 7 8 0 0 0 0      <-enderecos de memoria de void *
        // 1st     6 4 5 5 9 7 8 0 0 0
        // 2nd     6 4[1]5 9 7 8 0 0 0
    }
    for(k = s->numElems ; k >= i; k--){
        s->elems[k] = s->elems[k-1];
    }
    s->elems[i-1] = elem;
    s->numElems++;
}


void * removePosSequencia(sequencia s, int i){
    int j;
	void *aux = elementoPosSequencia(s,i);

	// seja i = 3
	// initial   6 4 5 9 7 8 0 0 0 0 numElems = 6
	//final      6 4 9 7 8 8 0 0 0 0 numElems = 5

    for(j = i; j < s->numElems; j++){
        s->elems[j-1]=s->elems[j];
    }
    s->numElems--;
    return aux;
}


iterador iteradorSequencia(sequencia s){
	//CUIDADO: DEVE DAR AO ITERADOR UMA COPIA DO VECTOR A PERCORRER
	//
	//Fazer
	int i;
	void ** aux = (void *) malloc (sizeof(void *) * s->numElems);
	for(i = 0; i< s->numElems; i++){
            aux[i]= s->elems[i];
	}
	return criaIterador(aux , s->numElems);
}
