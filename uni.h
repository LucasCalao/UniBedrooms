#ifndef _H_UNI
#define _H_UNI

#include "estudante.h"
#include "gerente.h"
#include "quarto.h"

typedef struct _unibedrooms * unibedrooms;

/***********************************************
criaUnibedrooms - Funcao da instancia da estrutura associada
a uniBedrooms que contem um dicionario de estudantes,
um dicionario de quartos e um dicionario de gerentes.
Parametros:
Retorno: ub - se o ub foi criado com sucesso
***********************************************/
unibedrooms criaUniBedrooms();

int existeEstudante(unibedrooms ub, char *login);

int existeQuarto(unibedrooms ub, char *codigo);

int existeGerente(unibedrooms ub, char *login);

int adicionaEstudante(unibedrooms ub, char *login,char *nome,int idade,char *localidade,char *universidade);

int adicionaGerente(unibedrooms ub, char *login, char*nome, char *universidade);

int adicionaQuarto(unibedrooms ub, char *codigo, char*login, char *nome, char *universidade, char *localidade, char *descricao, int andar);

estudante daEstudanteUniBedrooms(unibedrooms ub, char *login);

gerente daGerenteUniBedrooms(unibedrooms ub, char *login);

quarto daQuartoUniBedrooms(unibedrooms ub, char *codigo);

void mudaEstadoQuartoUni(unibedrooms ub, char *codigo, char *estado);

void insereCandidaturaUni(unibedrooms ub, char *codigo, char *login);

int temCandidaturasAtivas(unibedrooms ub, char *codigo);

char *loginGerenteUni(unibedrooms ub,char *login);

void removeQuartoUni(unibedrooms ub, char *codigo);

char *codigoQuartoUni(unibedrooms ub, char *codigo);

int temCandidaturaEstudanteQuartoUni(unibedrooms ub, char *codigo, char *login);

/*Funcao que verifica se o login dado corresponde ao login do gerente do
quarto.
Retornos: 1- se o login for correto; 0- se o login for incorreto
*/
int existeLoginQuartoUni(unibedrooms ub, char *codigo,char *login);

//int existeLogin(unibedrooms ub,char *login);

char *loginQuartoUni(unibedrooms ub, char *codigo);

char *estadoQuartoUni(unibedrooms ub,char *codigo);

void destroiTudoUb(unibedrooms ub);

#endif