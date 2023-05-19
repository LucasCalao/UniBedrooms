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
void removeQuarto(unibedrooms ub, char *linha);
void aceitaCandidatura(unibedrooms ub, char *linha);

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


    while(1){
        printf("> ");
        fgets(linha, MAX_LINHA, stdin);
        sscanf(linha, "%2s", cmd);

        if(strcmp(cmd, "XS") == 0){
            break;
        }
        else if (strcmp(cmd, "IE") == 0) {
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

        }else if(strcmp(cmd, "RQ") == 0){
            removeQuarto(ub,linha);    

        }else if(strcmp(cmd, "AC") == 0){
            aceitaCandidatura(ub,linha);    

        }
        else{
            if(cmd[0]=='\0')
                putchar('\n');
            printf("Comando invalido.\n\n");
        }
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

    sscanf(linha, "%s %s %[^\n]", comando, login, nome);
    nome[strlen(nome)-1] = '\0';
    login[strlen(login)] = '\0';
    fgets(buffer, 50, stdin);
    sscanf(buffer, "%d %[^\n]", &idade, localidade);
    localidade[strlen(localidade)-1] = '\0';
    fgets(buffer, 50, stdin);
    sscanf(buffer, "%[^\n]", universidade);
    universidade[strlen(universidade)-1] = '\0';

    //printf("\n\nLi isto: %s:%s:%s:%d:%s:%s\n",comando,login,nome,idade,localidade,universidade);
    if(existeEstudante(ub,login) || existeGerente(ub,login))
        printf("Utilizador ja existente.\n\n");

    else if(adicionaEstudante(ub,login,nome,idade,localidade,universidade))
        printf("Registo de estudante executado.\n\n");  
    
} 


void consultaDadosEstudante(unibedrooms ub, char *linha){

    char comando[MAX_COMANDO], login[20];

    sscanf(linha, "%s %s", comando, login);
    login[strlen(login)] = '\0';
    //printf("login dados:%s:",login);

    //printf("%s:%s",login,loginEstudante(daEstudanteUniBedrooms(ub,login)));

    if(!existeEstudante(ub,login))
        printf("Inexistencia do estudante referido.\n\n");
    else{
        estudante e = daEstudanteUniBedrooms(ub,login);
        printf("%s, %s, %d anos, %s\n%s\n\n",loginEstudante(e), nomeEstudante(e), idadeEstudante(e), localidadeEstudante(e), universidadeEstudante(e));
    }
}

void insereGerente(unibedrooms ub, char *linha){

    char comando[MAX_COMANDO], login[20], nome[50], universidade[40];
    char buffer[30];

    sscanf(linha, "%s %s %[^\n]", comando, login, nome);
    nome[strlen(nome)-1] = '\0';
    login[strlen(login)] = '\0';
    fgets(buffer, 50, stdin);
    sscanf(buffer, "%[^\n]", universidade);
    universidade[strlen(universidade)-1] = '\0';
    if(existeGerente(ub,login) || existeEstudante(ub,login)){   
        printf("Utilizador ja existente.\n\n");
    }
    else{  
        if(adicionaGerente(ub,login,nome,universidade))
            printf("Registo de gerente executado.\n\n");
    }
}

void consultaDadosGerente(unibedrooms ub, char *linha){

    char comando[MAX_COMANDO], login[50];

    sscanf(linha, "%s %s", comando, login);
    login[strlen(login)] = '\0';

    if(!existeGerente(ub,login))
        printf("Inexistencia do gerente referido.\n\n");
        else{
            gerente g = daGerenteUniBedrooms(ub,login);
            printf("%s, %s\n%s\n\n",loginGerente(g), nomeGerente(g),universidadeGerente(g));
        }
}

void insereQUarto(unibedrooms ub, char *linha){

    char nome[50], comando[MAX_COMANDO], login[50], localidade[50], universidade[50],descricao[200],codigo[50];
    int andar=0;
    char buffer[200];

    sscanf(linha, "%s %s %[^\n]", comando, codigo, login);
    codigo[strlen(codigo)] = '\0';
    login[strlen(login)-1] = '\0';

    fgets(buffer, 50, stdin);
    sscanf(buffer, "%[^\n]", nome);
    nome[strlen(nome)-1] = '\0';

    fgets(buffer, 50, stdin);
    sscanf(buffer, "%[^\n]", universidade);
    universidade[strlen(universidade)-1] = '\0';

    fgets(buffer, 50, stdin);
    sscanf(buffer, "%[^\n]", localidade);
    localidade[strlen(localidade)-1] = '\0';

    fgets(buffer, 50, stdin);
    sscanf(buffer, "%d", &andar);

    fgets(buffer, 200, stdin);
    sscanf(buffer, "%[^\n]", descricao);
    descricao[strlen(descricao)-1] = '\0';

    //printf("\n\n\nDados lidos do quarto:%s:%s:%s:%s:%s:%d:%s:",codigo,login,nome,universidade,localidade,andar,descricao);

    if(existeQuarto(ub,codigo))
        printf("Quarto existente.\n\n");
    else if(!existeQuarto(ub,codigo) && !existeGerente(ub,login))
        printf("Inexistencia do gerente referido.\n\n");
    else if(!existeQuarto(ub,codigo) && strcmp(universidade,universidadeGerente(daGerenteUniBedrooms(ub,login))))
        printf("Operacao nao autorizada.\n\n");
    else {
        adicionaQuarto(ub,codigo,login,nome,universidade,localidade,descricao,andar);
        printf("Registo de quarto executado.\n\n");
    }
}

void consultaDadosQuarto(unibedrooms ub, char *linha){

    char comando[MAX_COMANDO], codigo[50];

    sscanf(linha, "%s %[^\n]", comando, codigo);
    codigo[strlen(codigo)-1] = '\0';

    //printf("\n\nLi:%s:",codigo);

    if(!existeQuarto(ub,codigo))
        printf("Inexistencia do quarto referido.\n\n");
        else{
            quarto q = daQuartoUniBedrooms(ub,codigo);
            printf("%s, %s\n%s\n%s\n%d\n%s\n%s\n\n",codigoQuarto(q), nomeQuarto(q), universidadeQuarto(q), localidadeQuarto(q), andarQuarto(q), descricaoQuarto(q), estadoQuarto(q));
        }
}

void modificaEstadoQuarto(unibedrooms ub, char *linha){

    char comando[MAX_COMANDO], codigo[50], login[50], estado[10];

    sscanf(linha, "%s %s %s %[^\n]", comando, codigo,login,estado);
    codigo[strlen(codigo)] = '\0';
    login[strlen(login)] = '\0';
    estado[strlen(estado)-1] = '\0';

    if (!existeQuarto(ub,codigo))
        printf("Inexistencia do quarto referido.\n\n");
    else if(strcmp(login,loginGerenteUni(ub,login)))
            printf("Operacao nao autorizada.\n\n");
    else if(temCandidaturasAtivas(ub,codigo) && !strcmp(estado,"ocupado"))
        printf("Candidaturas ativas.\n\n");
    else{
        mudaEstadoQuartoUni(ub,codigo,estado);
        printf("Estado de quarto atualizado.\n\n");
    }

}

void removeQuarto(unibedrooms ub, char *linha){

    char comando[MAX_COMANDO], codigo[50], login[50];

    sscanf(linha, "%s %s %[^\n]", comando, codigo,login);
    codigo[strlen(codigo)] = '\0';
    login[strlen(login)-1] = '\0';

    if(!existeQuarto(ub,codigo))
        printf("Inexistencia do quarto referido.\n\n");
    else{
        gerente g = daGerenteUniBedrooms(ub,codigo);
        if(strcmp(login,loginGerente(g)))
            printf("Operacao nao autorizada.\n\n");
        else if(temCandidaturasAtivas(ub,codigo))
            printf("Candidaturas activas.\n\n");
        else
            removeQuartoUni(ub,codigo);
    }
}

void insereCandidatura(unibedrooms ub, char *linha){

    char comando[MAX_COMANDO], codigo[50], login[50];

    sscanf(linha, "%s %s %[^\n]", comando, login, codigo);
    codigo[strlen(codigo)-1] = '\0';
    login[strlen(login)] = '\0';

    estudante e = daEstudanteUniBedrooms(ub,login);
    quarto q = daQuartoUniBedrooms(ub,codigo);
    if(!existeEstudante(ub,login))
        printf("Inexistencia do estudante referido.\n\n");
    else if (nrCandidaturasEstudante(e)>10)
        printf("Operacao nao autorizada.\n\n");
    else if(!existeQuarto(ub,codigo))
        printf("Inexistencia do quarto referido.\n\n");
    else if(!strcmp(estadoQuarto(q),"ocupado"))
        printf("Quarto ocupado.\n\n");
    else if(temCandidaturaEstudanteQuarto(q,e))
        printf("Candidatura existente.\n\n");
    else{
        insereCandidaturaUni(ub,codigo,login);
        printf("Registo de candidatura executado.\n\n");
    }
}

void aceitaCandidatura(unibedrooms ub, char *linha){

    char comando[MAX_COMANDO], codigo[50], loginGerente[50], loginEstudante[50];

    sscanf(linha, "%s %s %s %[^\n]", comando,  codigo,loginGerente,loginEstudante);
    loginGerente[strlen(loginGerente)] = '\0';
    codigo[strlen(codigo)] = '\0';
    loginEstudante[strlen(loginEstudante)-1] = '\0';


    //printf("\n\nLi:%s base de dados:%s",codigo,codigoQuartoUni(ub,codigo));
    //estudante e = daEstudanteUniBedrooms(ub,loginGerente);
    //quarto q = daQuartoUniBedrooms(ub,codigo);
    //printf("\n\nLi:%s base de dados:%s",codigo,codigoQuarto(q));
    if(!existeQuarto(ub,codigo)){
        printf("Inexistencia do quarto referido.\n\n");
    }
    else if(strcmp(loginGerente,loginGerenteUni(ub,loginGerente))){
        printf("Operacao nao autorizada.\n\n");
    }
    else {
        estudante e = daEstudanteUniBedrooms(ub,loginEstudante);
        quarto q = daQuartoUniBedrooms(ub,codigo);
        if(!temCandidaturaEstudanteQuarto(q,e))
            printf("Inexistencia da candidatura referida.\n\n");
    }
    /*else {
        mudaEstadoQuartoUni(ub,codigo,"ocupado");
        eliminaCandidaturasEstudante(e,q);
        removeCandidaturasQuarto(q);
        retiraCandidaturaEstudante(e,q);
    }*/
}


void destroiUb(unibedrooms ub){

    destroiTudoUb(ub);

}