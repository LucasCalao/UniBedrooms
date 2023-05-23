#ifndef _H_QUARTO

#define _H_QUARTO

#include "iterador.h"
#include "gerente.h"
#include "estudante.h"


typedef struct _quarto * quarto;

typedef struct _estudante * estudante;

quarto criaQuarto(char *codigo, char *loginGerente, char *nome, char *universidade, char *localidade, char *descricao, int andar);

void destroiQuarto (quarto q);

void destroiGenquarto (void * q);

char *nomeQuarto(quarto q);

char *codigoQuarto(quarto q);

char *universidadeQuarto(quarto q);

char *localidadeQuarto(quarto q);

char *descricaoQuarto(quarto q);

char *estadoQuarto(quarto q);

int andarQuarto(quarto q);

void mudaEstadoQuarto(quarto q, char *estado);

char *loginQuarto(quarto q);

void criaCandidaturaQuarto(quarto q, estudante e);

int temCandidaturaEstudanteQuarto(quarto q, estudante e);

int existeCandidaturasQuarto(quarto q);

void removeCandidaturasQuarto(quarto q);

iterador daIteradorCandidaturasQuarto(quarto q);

#endif // _H_quarto