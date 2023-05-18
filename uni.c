#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dicionario.h"
#include "uni.h"
#include "quarto.h"
#include "gerente.h"
#include "estudante.h"


#define MAXQUARTOS 10000
#define MAXESTUDANTES 20000
#define MAXGERENTES 1000

struct _unibedrooms{
    dicionario quartos;
    dicionario estudantes;
    dicionario gerentes;
};

unibedrooms criaUniBedrooms(){

    unibedrooms ub = (unibedrooms) malloc(sizeof(struct _unibedrooms));
    if(ub==NULL)
        return NULL;
    ub->quartos = criaDicionario(MAXQUARTOS,1);
    if(ub->quartos==NULL){
        free(ub);
        return NULL;
    }
    
    ub->estudantes = criaDicionario(MAXESTUDANTES,1);
    if(ub->estudantes==NULL){
        free(ub);
        return NULL;
    }

    ub->gerentes = criaDicionario(MAXGERENTES,1);
    if(ub->gerentes==NULL){
        free(ub);
        return NULL;
    }

    return ub;
}

int existeEstudante(unibedrooms ub, char *login){

    return existeElemDicionario(ub->estudantes,login);

}
int existeQuarto(unibedrooms ub, char *codigo){

    return existeElemDicionario(ub->quartos,codigo);

}
int existeGerente(unibedrooms ub, char *login){

    return existeElemDicionario(ub->gerentes,login);

}

int adicionaEstudante(unibedrooms ub, char *login,char *nome,int idade,char *localidade,char *universidade){

    estudante e = criaEstudante(login,nome,idade,localidade,universidade);
    return adicionaElemDicionario(ub->estudantes, login, e);

}
int adicionaGerente(unibedrooms ub, char *login, char*nome, char *universidade){

    gerente g = criaGerente(login,nome,universidade);
    return adicionaElemDicionario(ub->gerentes,(char*) login, (gerente) g);

}
int adicionaQuarto(unibedrooms ub, char *codigo, char*login, char *nome, char *universidade, char *localidade, char *descricao, int andar){

    quarto q = (quarto) criaQuarto(codigo,login,nome,universidade,localidade,descricao,andar);
    return adicionaElemDicionario(ub->quartos,(char*) codigo, (quarto) q);

}

estudante daEstudanteUniBedrooms(unibedrooms ub, char *login){

    if(existeElemDicionario(ub->estudantes, login))
        return elementoDicionario(ub->estudantes, login);
    return NULL;

}
gerente daGerenteUniBedrooms(unibedrooms ub, char *login){

    if(existeElemDicionario(ub->gerentes, login))
        return elementoDicionario(ub->gerentes, login);
    return NULL;

}
quarto daQuartoUniBedrooms(unibedrooms ub, char *codigo){
    
    if(existeElemDicionario(ub->quartos, codigo))
        return elementoDicionario(ub->quartos, codigo);
    return NULL;

}

void mudaEstadoQuartoUni(unibedrooms ub, char *codigo, char *estado){

    quarto q = daQuartoUniBedrooms(ub,codigo);
    mudaEstadoQuarto(q,estado);

}

void insereCandidaturaUni(unibedrooms ub, char *codigo, char *login){

    quarto q = daQuartoUniBedrooms(ub,codigo);
    estudante e = daEstudanteUniBedrooms(ub,login);

    criaCandidaturaQuarto(q,e);
    registaCandidaturaEstudante(e,q);

}

int temCandidaturasAtivas(unibedrooms ub, quarto q){

    return existeCandidaturasQuarto(q);

}

/*int existeLoginEstudante(unibedrooms ub,char *login){

    printf("Entrei no existeLogin\n\n");
    return existeElemDicionario()

}*/

void destroiTudoUb(unibedrooms ub){

    destroiDicEElems(ub->estudantes,(void*) destroiGenEstudante);
    destroiDicEElems(ub->gerentes,(void*) destroiGenGerente);
    destroiDicEElems(ub->quartos,(void*) destroiGenquarto);

    free(ub);

}