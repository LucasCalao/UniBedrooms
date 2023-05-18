#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "estudante.h"
#include "quarto.h"

#define MAX_CANDIDATURAS 10

struct _estudante{

    quarto candidaturas[MAX_CANDIDATURAS];
    char *nome;
    int idade;
    int nrCandidaturas;
    char *login;
    char *universidade;
    char *localidade;
};

estudante criaEstudante(char *login, char *nome, int idade, char *localidade, char *universidade){

    estudante e = (estudante) malloc(sizeof(struct _estudante));
    if(e==NULL)
        return NULL;
    
    e->nome = (char*) malloc(sizeof(char)*(strlen(nome)+1));
    if(e->nome==NULL){
        free(e);
        return NULL;
    }
    strcpy(e->nome,nome);

    e->login = (char*) malloc(sizeof(char)*(strlen(login)+1));
    if(e->login==NULL){
        free(e->nome);
        free(e);
        return NULL;
    }
    strcpy(e->login,login);

    e->universidade = (char*) malloc(sizeof(char)*(strlen(universidade)+1));
    if(e->universidade==NULL){
        free(e->login);
        free(e->nome);
        free(e);
        return NULL;
    }
    strcpy(e->universidade,universidade);

    e->localidade = (char*) malloc(sizeof(char)*(strlen(localidade)+1));
    if(e->localidade==NULL){
        free(e->universidade);
        free(e->login);
        free(e->nome);
        free(e);
        return NULL;
    }
    strcpy(e->localidade,localidade);

    e->idade = idade;
    e->nrCandidaturas = 0;

    return e;
}

void destroiEstudante (estudante e){
    free(e->nome); free(e->login); free(e->universidade); free(e->localidade); free(e);
}

void destroiGenEstudante (void * e){
    destroiEstudante(e);
}

char *nomeEstudante(estudante e){
    return e->nome;
}

char *loginEstudante(estudante e){
    return e->login;
}

char *universidadeEstudante(estudante e){
    return e->universidade;
}

char *localidadeEstudante(estudante e){
    return e->localidade;
}

int idadeEstudante(estudante e){
    return e->idade;
}

int nrCandidaturasEstudante(estudante e){
    return e->nrCandidaturas;
}

int registaCandidaturaEstudante(estudante e, quarto q){
    if(e->nrCandidaturas<10 && !estudanteTemCandidaturaQuarto(e,q))
        e->candidaturas[e->nrCandidaturas++] = q;
    return 0;
}

void retiraCandidaturaEstudante(estudante e, quarto q){
    for(int i=0;i<e->nrCandidaturas;i++)
        if(codigoQuarto(q)==codigoQuarto(e->candidaturas[i]))
            for(int j=0;j<e->nrCandidaturas;j++)
                e->candidaturas[j+1]=e->candidaturas[j];    
}

int estudanteTemCandidaturaQuarto(estudante e, quarto q){
    for(int i=0; i<e->nrCandidaturas;i++)
        if(codigoQuarto(q)==codigoQuarto(e->candidaturas[i]))
            return 1;
    return 0;
}