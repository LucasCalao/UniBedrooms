#ifndef _H_ESTUDANTE

#define _H_ESTUDANTE

#include "gerente.h"
#include "quarto.h"

typedef struct _estudante * estudante;

typedef struct _quarto * quarto;

estudante criaEstudante(char *login, char *nome, int idade, char *localidade, char *universidade);

void destroiEstudante (estudante e);

void destroiGenEstudante (void * e);

char *nomeEstudante(estudante e);

char *loginEstudante(estudante e);

char *universidadeEstudante(estudante e);

char *localidadeEstudante(estudante e);

int idadeEstudante(estudante e);

int nrCandidaturasEstudante(estudante e);

int registaCandidaturaEstudante(estudante e, quarto q);

void retiraCandidaturaEstudante(estudante e, quarto q);

int estudanteTemCandidaturaQuarto(estudante e, quarto q);

#endif // _H_ESTUDANTE