#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ncurses.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <string.h>

#define FIFO_SERV "sss"

#define MAXX 100
#define MAXY 100

#define CHAR 30
#define TAM 8
char str[1024];

typedef struct labirinto labi; 
typedef struct 	PLAYER play;


struct labirinto 
{
  int largura, altura; 
 // char bloco[100];//DESTRUTIVEL 
 // char parede[100] ;//INDESTRUTIVEL 
  char lab[MAXX][MAXY];
 int bloco[MAXX][MAXY];
};

typedef struct{
	
	int num;
	int humano;
	int tempo;
	char cara;
	int fim;
	
labi l;


}JOGADOR;

typedef struct{
	int x, y;
}POSICAO;

struct PLAYER
{
 char nome[30];
 char passw[30]; 
 int check;
 int pid;
 int ch;
 int num;
 int jog;
int bomba;
int superbomba;

};

typedef struct{
	int num, x, y, jog;
	int bomb,superb;
	labi a;
	POSICAO pos[5];

}RESPOSTA;

JOGADOR j[4] = {{0,0, 5000000, 'A',0}, {1,0, 5000000, 'B',0}, {2,0, 5000000, 'C',0}, {3,0, 5000000, 'D',0}};

// Guarda Clientes
 play clientes[TAM];
//int cliente[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
void imprime(labi x);
void iniciatab(labi *x, int alt, int larg );
void leinfo( char *nomefich);
void guardainfo(char *nomefich, play *p);
int verificainfo(char *nomefich, play p);
int verificainfologin(char *nomefich, play p);
int contapalavras(char *nome);
void login( char* comando,play *p) ;
play * inicialogin(play *p);
