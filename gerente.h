#ifndef _H_gerente

#define _H_gerente

typedef struct _gerente * gerente;

gerente criaGerente(char *login, char *nome, char *universidade);

void destroiGerente (gerente g);

void destroiGenGerente (void * g);

char *nomeGerente(gerente g);

char *loginGerente(gerente g);

char *universidadeGerente(gerente g);

#endif // _H_gerente