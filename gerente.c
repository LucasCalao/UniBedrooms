#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "gerente.h"
#include "quarto.h"
#include "estudante.h"
#include "dicionario.h"
#include "iterador.h"

#define MAX_QUARTOS 1000


struct _gerente{
    dicionario quartos; //preciso disto?
    char *nome;
    char *login;
    char *universidade;
};

gerente criaGerente(char *login, char *nome, char *universidade){

    gerente g = (gerente) malloc(sizeof(struct _gerente));
    if(g==NULL)
        return NULL;
    
    g->nome = (char*) malloc(sizeof(char)*(strlen(nome)+1));
    if(g->nome==NULL){
        free(g);
        return NULL;
    }
    strcpy(g->nome,nome);

    g->login = (char*) malloc(sizeof(char)*(strlen(login)+1));
    if(g->login==NULL){
        free(g->nome);
        free(g);
        return NULL;
    }
    strcpy(g->login,login);

    g->universidade = (char*) malloc(sizeof(char)*(strlen(universidade)+1));
    if(g->universidade==NULL){
        free(g->login);
        free(g->nome);
        free(g);
        return NULL;
    }
    strcpy(g->universidade,universidade);

    g->quartos = criaDicionario(MAX_QUARTOS,1);
    if(g->quartos==NULL){
        free(g->universidade);
        free(g->login);
        free(g->nome);
        free(g);
        return NULL;
    }

    return g;
}

void destroiGerente (gerente g){
    free(g->nome); free(g->login); free(g->universidade); destroiDicionario(g->quartos); free(g);
}

void destroiGenGerente (void * g){
    destroiGerente(g);
}

char *nomeGerente(gerente g){
    return g->nome;
}

char *loginGerente(gerente g){
    return g->login;
}

char *universidadeGerente(gerente g){
    return g->universidade;
}

/*
int registaQuartoGerente(gerente g, char *codigo, char *loginGerente, char *nome, char *universidade, char *localidade, char *descricao, int andar) {

    if(existeElemDicionario(g->nome,codigo))
        return 1;
    else{
        quarto q;
        q=criaQuarto(codigo, loginGerente, nome, universidade, localidade, descricao, andar);
        adicionaElemDicionario(g->quartos,codigo,q);
        return 0;
    }

}

int removeQuartoGerente(gerente g, char *codigo){
    quarto q; 

    q = removeElemDicionario(g->quartos,codigo);
    if(q==NULL)
        return 1;
    else{
        destroiQuarto(q);
        return 0;
    }
}

quarto daQuartoGerente(gerente g, char*codigo){
    
    quarto q=elementoDicionario(g->quartos,codigo);
    return q;
}

int aceitaCandidaturaEstudanteQuarto(gerente g, estudante e, quarto q){

    //quarto fica ocupado; candidaturas sao eliminadas; ocupante = estudante
    mudaEstadoQuarto(q,"ocupado");
    atribuiOcupanteQuarto(q,e);
    retiraCandidaturaEstudante(e,q);
    retiraCandidaturasQuarto(q);

}
*/