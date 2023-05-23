#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "iterador.h"
#include "dicionario.h"
#include "sequencia.h"
#include "estudante.h"
#include "gerente.h"
#include "quarto.h"

#define ESTADO 8
#define MAX_CANDIDATOS 20000

struct _quarto{
    sequencia candidatos; //alunos identificados pelo login
    char *codigo;
    int andar;
    char *nome;
    char *universidade;
    char *localidade;
    char *descricao;
    char *login; //prof disse para meter um apontador para gerente
    char *estado;
};

quarto criaQuarto(char *codigo, char *login, char *nome, char *universidade, char *localidade, char *descricao, int andar){

    quarto q = (quarto) malloc(sizeof(struct _quarto));
    if(q==NULL)
        return NULL;
    
    q->codigo = (char*) malloc(sizeof(char)*(strlen(codigo)+1));
    if(q->codigo==NULL){
        free(q);
        return NULL;
    }
    strcpy(q->codigo,codigo);

    q->nome = (char*) malloc(sizeof(char)*(strlen(nome)+1));
    if(q->nome==NULL){
        free(q->codigo);
        free(q);
        return NULL;
    }
    strcpy(q->nome,nome);
    
    q->universidade = (char*) malloc(sizeof(char)*(strlen(universidade)+1));
    if(q->universidade==NULL){
        free(q->nome);
        free(q->codigo);
        free(q);
        return NULL;
    }
    strcpy(q->universidade,universidade);

    q->localidade = (char*) malloc(sizeof(char)*(strlen(localidade)+1));
    if(q->localidade==NULL){
        free(q->universidade);
        free(q->nome);
        free(q->codigo);
        free(q);
        return NULL;
    }
    strcpy(q->localidade,localidade);

    q->descricao = (char*) malloc(sizeof(char)*(strlen(descricao)+1));
    if(q->descricao==NULL){
        free(localidade);
        free(q->universidade);
        free(q->nome);
        free(q->codigo);
        free(q);
        return NULL;
    }
    strcpy(q->descricao,descricao);

    q->andar = andar;

    q->estado = (char*) malloc(sizeof(char)*10);
    if(q->estado==NULL){
        free(q->descricao);
        free(localidade);
        free(q->universidade);
        free(q->nome);
        free(q->codigo);
        free(q);
        return NULL;
    }
    strcpy(q->estado,"livre");

    q->login = (char*) malloc(sizeof(char)*30);
    if(q->login==NULL){
        free(q->estado);
        free(q->descricao);
        free(localidade);
        free(q->universidade);
        free(q->nome);
        free(q->codigo);
        free(q);
        return NULL;
    }
    strcpy(q->login,login);

    q->candidatos = criaSequencia(MAX_CANDIDATOS);
    if(q->candidatos==NULL){
        free(q->login);
        free(q->estado);
        free(q->descricao);
        free(localidade);
        free(q->universidade);
        free(q->nome);
        free(q->codigo);
        free(q);
        return NULL;
    }

    return q;
}

void destroiQuarto (quarto q){
    free(q->login);free(q->estado); free(q->descricao);free(q->nome); free(q->codigo); free(q->universidade); free(q->localidade); destroiSequencia(q->candidatos);free(q);
}

void destroiGenquarto (void * q){
    destroiQuarto(q);
}

char *nomeQuarto(quarto q){
    return q->nome;
}

char *codigoQuarto(quarto q){
    return q->codigo;
}

char *universidadeQuarto(quarto q){
    return q->universidade;
}

char *localidadeQuarto(quarto q){
    return q->localidade;
}

char *descricaoQuarto(quarto q){
    return q->descricao;
}

char *estadoQuarto(quarto q){
    return q->estado;
}

char *loginQuarto(quarto q){
    return q->login;
}

int andarQuarto(quarto q){
    return q->andar;
}

void mudaEstadoQuarto(quarto q, char *estado){
    strcpy(q->estado,estado);
}

void criaCandidaturaQuarto(quarto q, estudante e){

    adicionaPosSequencia(q->candidatos,e,(tamanhoSequencia(q->candidatos)+1));
    //printf("NOOB:%s\n\n\n",nomeEstudante(elementoPosSequencia(q->candidatos,tamanhoSequencia(q->candidatos))));

}

int temCandidaturaEstudanteQuarto(quarto q, estudante e){

    //printf("1-%s\n",loginEstudante(e));
    //printf("%d",tamanhoSequencia(q->candidatos));
    for(int i=0; i<tamanhoSequencia(q->candidatos);i++){
        //printf("ENtrei no for\n\n");
        estudante aux = (estudante) elementoPosSequencia(q->candidatos,i+1);
        //printf("2-%s:%s\n",loginEstudante(e),loginEstudante(aux));
        if(!strcmp(loginEstudante(e),loginEstudante(aux)))
            return 1;
        else
            return 0;       
    }
    return 0;
}

int existeCandidaturasQuarto(quarto q){
    
    if(tamanhoSequencia(q->candidatos)>0)
        return 1;
    return 0;
}

void removeCandidaturasQuarto(quarto q){

    for(int i=0;i<tamanhoSequencia(q->candidatos);i++){
        removePosSequencia(q->candidatos,i);
    }

}

iterador daIteradorCandidaturasQuarto(quarto q){

    iterador myIt = iteradorSequencia(q->candidatos);

    return (myIt);
    
}

/*
estudante daOcupanteQuarto(quarto q){
    return q->ocupante;
}

void atribuiOcupanteQuarto(quarto q, estudante e){
    q->ocupante = e;
}

void retiraCandidaturasQuarto(quarto q){
    for(int i=0; i<tamanhoSequencia(q->candidatos); i++)
        removePosSequencia(q->candidatos,i);   
}

void registaCandidaturaEstudantequarto(quarto q, estudante e){
    adicionaPosSequencia(q->candidatos,(void*) e, tamanhoSequencia(q->candidatos));
}
*/
//iterador quartos