#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "iterador.h"
#include "dicionario.h"
#include "estudante.h"
#include "gerente.h"
#include "quarto.h"
#include "uni.h"


#define MAX_LINHA 50
#define MAX_COMANDO 3
#define MAX50 50
#define MAX_DESCRICAO 200


void interpretador(unibedrooms ub);
char *para_maisculas(char* linha);

void insereEstudante(unibedrooms ub, char *linha);
void consultaDadosEstudante(unibedrooms ub, char *linha);
void insereGerente(unibedrooms ub, char *linha);
void consultaDadosGerente(unibedrooms ub, char *linha);
void insereQUarto(unibedrooms ub, char *linha);
void consultaDadosQuarto(unibedrooms ub, char *linha);
void modificaEstadoQuarto(unibedrooms ub, char *linha);
void insereCandidatura(unibedrooms ub, char *linha);

void destroiUb(unibedrooms ub);


int main(void)
{
    unibedrooms ub = criaUniBedrooms();
	interpretador(ub);
	destroiUb(ub);
	return 0;

}
void interpretador(unibedrooms ub){
    char linha[MAX_LINHA];
    char cmd[MAX_COMANDO];

    printf("> ");
    fgets(linha, MAX_LINHA, stdin);
    sscanf(linha, "%2s", cmd);
    //strcpy(cmd, para_maisculas(cmd));

    while(strcmp(cmd, "XS")){
        if (strcmp(cmd, "IE") == 0) {
            insereEstudante(ub,linha);

        } else if (strcmp(cmd, "DE") == 0) {
            consultaDadosEstudante(ub,linha);
            
        } else if(strcmp(cmd, "IG") == 0){
            insereGerente(ub,linha);
            
        } else if(strcmp(cmd, "DG") == 0){
            consultaDadosGerente(ub,linha);
            
        } else if(strcmp(cmd, "IQ") == 0){
            insereQUarto(ub,linha);
            
        } else if(strcmp(cmd, "DQ") == 0){
            consultaDadosQuarto(ub,linha); 

        }else if(strcmp(cmd, "MQ") == 0){
            modificaEstadoQuarto(ub,linha);   

        }else if(strcmp(cmd, "IC") == 0){
            insereCandidatura(ub,linha);            
        }
        else {
            printf("Código invalido.\n\n");
        }

        //printf("> ");
        fgets(linha, MAX_LINHA, stdin);
        sscanf(linha, "%2s", cmd);
        
        //strcpy(cmd, para_maisculas(cmd));
    }
}

char* para_maisculas(char* linha){
    int i=0;

    for(i=0;i<(strlen(linha));i++)
        linha[i] = toupper(linha[i]);
    return linha;
}

 void insereEstudante(unibedrooms ub, char *linha){

    char nome[50], comando[MAX_COMANDO], login[20], localidade[50], universidade[30];
    int idade=0;
    char buffer[50];

    sscanf(linha, "%s %s %s[^\n]", comando, login, nome);
    nome[strlen(nome)] = '\0';
    login[strlen(login)] = '\0';
    fgets(buffer, 50, stdin);
    sscanf(buffer, "%d %s[^\n]", &idade, localidade);
    localidade[strlen(localidade)] = '\0';
    fgets(buffer, 50, stdin);
    sscanf(buffer, "%s[^\n]", universidade);
    universidade[strlen(universidade)] = '\0';

    printf("\n\nLi isto: %s:%s:%s:%d:%s:%ss\n",comando,login,nome,idade,localidade,universidade);
    if(existeEstudante(ub,login) || existeGerente(ub,login))
        printf("> Utilizador ja existente.\n\n");

    else if(adicionaEstudante(ub,login,nome,idade,localidade,universidade))
        printf("> Registo de estudante executado.\n\n");  
    
} 


void consultaDadosEstudante(unibedrooms ub, char *linha){

    char comando[MAX_COMANDO], login[20];

    sscanf(linha, "%s %[^\n]", comando, login);

    //printf("%s:%s",login,loginEstudante(daEstudanteUniBedrooms(ub,login)));

    if(!existeEstudante(ub,login))
        printf("> Inexistencia do estudante referido\n\n");
    else{
        estudante e = daEstudanteUniBedrooms(ub,login);
        printf("> %s, %s, %d anos, %s\n%s\n\n",loginEstudante(e), nomeEstudante(e), idadeEstudante(e), localidadeEstudante(e), universidadeEstudante(e));
    }
}

void insereGerente(unibedrooms ub, char *linha){

    char comando[MAX_COMANDO], login[20], nome[50], universidade[40];
    char buffer[30];

    if(sscanf(linha, "%s %s %[^\n]", comando, login, nome) != 3)
        printf("> Comando errado\n");
    fgets(buffer, 50, stdin);
    sscanf(buffer, "%[^\n]", universidade);
    if(existeGerente(ub,login) || existeEstudante(ub,login)){   
        printf("> Utilizador ja existente.\n\n");
    }
    else{  
        if(adicionaGerente(ub,login,nome,universidade))
            printf("> Registo de gerente executado.\n\n");
    }
}

void consultaDadosGerente(unibedrooms ub, char *linha){

    char comando[MAX_COMANDO], login[50];

    if(sscanf(linha, "%s %[^\n]", comando, login) != 2){
        printf("> Comando errado\n");
    }
    else if(!existeGerente(ub,login))
        printf("> Inexistencia do gerente referido\n\n");
        else{
            gerente g = daGerenteUniBedrooms(ub,login);
            printf("%s, %s\n%s\n\n",loginGerente(g), nomeGerente(g),universidadeGerente(g));
        }
}

void insereQUarto(unibedrooms ub, char *linha){

    char nome[50], comando[MAX_COMANDO], login[50], localidade[50], universidade[50],descricao[200],codigo[50];
    int andar=0;
    char buffer[50];

    if(sscanf(linha, "%s %s %[^\n]", comando, codigo, login)!=3)
        printf("> Comando errado\n\n");
    fgets(buffer, 50, stdin);
    sscanf(buffer, "%[^\n]", nome);
    fgets(buffer, 50, stdin);
    sscanf(buffer, "%[^\n]", universidade);
    fgets(buffer, 50, stdin);
    sscanf(buffer, "%[^\n]", localidade);
    fgets(buffer, 50, stdin);
    sscanf(buffer, "%d", &andar);
    fgets(buffer, 200, stdin);
    sscanf(buffer, "%[^\n]", descricao);

    if(existeQuarto(ub,codigo))
        printf("> Quarto existente.\n\n");
    else if(!existeQuarto(ub,codigo) && !existeGerente(ub,login))
        printf("> Inexistencia do gerente referido.\n\n");
    else if(!existeQuarto(ub,codigo) && strcmp(universidade,universidadeGerente(daGerenteUniBedrooms(ub,login))))
        printf("> Operacao nao autorizada.\n\n");
    else {
        adicionaQuarto(ub,codigo,login,nome,universidade,localidade,descricao,andar);
        printf("> Registo de quarto executado.\n\n");
    }
}

void consultaDadosQuarto(unibedrooms ub, char *linha){

    char comando[MAX_COMANDO], codigo[50];

    if(sscanf(linha, "%s %[^\n]", comando, codigo) != 2){
        printf("> Comando errado\n");
    }
    else if(!existeQuarto(ub,codigo))
        printf("> Inexistencia do quarto referido.\n\n");
        else{
            quarto q = daQuartoUniBedrooms(ub,codigo);
            printf("%s, %s\n%s\n%s\n%d\n%s\n%s\n\n",codigoQuarto(q), nomeQuarto(q), universidadeQuarto(q), localidadeQuarto(q), andarQuarto(q), descricaoQuarto(q), estadoQuarto(q));
        }
}

void modificaEstadoQuarto(unibedrooms ub, char *linha){

    char comando[MAX_COMANDO], codigo[50], login[50], estado[10];

    if(sscanf(linha, "%s %s %s %[^\n]", comando, codigo,login,estado) != 4){
        printf("> Comando errado\n");
    }
    else
        mudaEstadoQuartoUni(ub,codigo,estado);

}

void removeQuarto(unibedrooms ub, char *linha){

    char comando[MAX_COMANDO], codigo[50], login[50];

    if(sscanf(linha, "%s %s %[^\n]", comando, codigo,login) != 3){
        printf("> Comando errado\n");
    }
    if(!existeQuarto(ub,codigo))
        printf("> Inexistencia do quarto referido.\n\n");
    else{
        gerente g = daGerenteUniBedrooms(ub,codigo);
        if(strcmp(login,loginGerente(g)))
            printf("Operacao nao autorizada.\n\n");
        else{
            quarto q = daQuartoUniBedrooms(ub,codigo);
            if(temCandidaturasAtivas(ub,q))
            printf("Candidaturas activas.\n\n");
        }
    }
}

void insereCandidatura(unibedrooms ub, char *linha){

    char comando[MAX_COMANDO], codigo[50], login[50];

    if(sscanf(linha, "%s %s %[^\n]", comando, login, codigo) != 3){
        printf("> Comando errado\n");
    }
    else{
        estudante e = daEstudanteUniBedrooms(ub,login);
        quarto q = daQuartoUniBedrooms(ub,codigo);
        if(!existeEstudante(ub,login))
            printf("Inexistencia do estudante referido.\n\n");
        else if (nrCandidaturasEstudante(e)>10)
            printf("Operacao nao autorizada.\n\n");
        else if(!existeQuarto(ub,codigo))
            printf("Inexistencia do quarto referido.\n\n");
        else if(strcmp(estadoQuarto(q),"ocupado"))
            printf("Quarto ocupado");
        else if(temCandidaturaEstudanteQuarto(q,e))
            printf("Candidatura existente\n\n");
        else{
            insereCandidaturaUni(ub,codigo,login);
            printf("Registo de candidatura executado.\n\n");
        }
    }
}


void destroiUb(unibedrooms ub){

    destroiTudoUb(ub);

}