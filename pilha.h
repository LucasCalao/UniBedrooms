/*
 * pilha.h
 */
#ifndef _H_PILHA
#define _H_PILHA

/* Tipo de dados: pilha ---> comportamento “Ultimo a chegar, Primeiro a sair” */
typedef struct _pilha * pilha;

/* Prototipos das funcoes associadas a uma pilha */

/***********************************************
criaPilha - Criacao da instancia da estrutura associada a uma pilha.
Parametros:
     cap - capacidade prevista da pilha
Retorno: apontador para a  instancia criada
Pre-condicoes:
***********************************************/
pilha criaPilha(int cap);

/***********************************************
destroiPilha - Liberta a memoria ocupada pela instancia da estrutura associada a pilha.
Parametros:
	p - pilha - pilha a destruir
Retorno:
Pre-condicoes: p != NULL
***********************************************/
void destroiPilha (pilha p );

/***********************************************
destroipilhaEElems - Liberta a memoria ocupada pela instancia da estrutura associada a pilha e os elementos.
Parametros:
	p - pilha a destruir	destroi - funcao para destruicao dos elementos
Retorno:
Pre-condicoes: p != NULL
***********************************************/
void destroiPilhaEElems(pilha p, void (*destroi)(void *) );

/***********************************************
vaziaPilha - Indica se a pilha esta vazia.
Parametros:
	p - pilha
Retorno: 1- caso pilha vazia; 0 - caso contrario
Pre-condicoes: p != NULL
***********************************************/
int vaziaPilha(pilha p);

/***********************************************
tamanhoPilha - Consulta o numero de elementos na pilha.
Parametros:
	p - pilha
Retorno: numero de elementos na pilha
Pre-condicoes: p != NULL
***********************************************/
int tamanhoPilha(pilha p);

/***********************************************
topoPilha – Retorna o elemento a menos tempo na pilha (no topo).
Parametros:
    p – pilha
Retorno: retorna o endereco do elemento
Pre-condicoes: p != NULL && tamanhoPilha(p) != 0
***********************************************/
void * topoPilha(pilha p);

/***********************************************
emPilha - Adiciona o elemento dado na pilha.
Parametros:
	p – pilha
	elem - endereco do elemento
Retorno:
Pre-condicoes: p != NULL
***********************************************/
void emPilha(pilha p, void * elem);

/***********************************************
desemPilha - Remove o elemento a menos tempo na pilha (no topo).
Parametros:
	p – pilha
Retorno: retorna o elemento
Pre-condicoes: p != NULL && vaziaPilha(p) != 1
***********************************************/
void * desemPilha(pilha p);

#endif
