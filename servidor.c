#include "labirinto.h"
POSICAO ele[4] = {{7,4}, {12,6}, {13, 10}, {16,15}};
//int bloco[MAXX][MAXY];

void *mover(void *info)
{
	int ch;
	//labi a;
	JOGADOR *j;
	j = (JOGADOR *) info;


		
	do
	{
		if(!j->humano){
			ch = rand () % 5;

		switch(ch){
			case 0:
				ele[j->num].y--;
				if((j->l.bloco[(ele[j->num].x)-6][(ele[j->num].y)-3] !=0))
					ele[j->num].y++	;
				
				break;
			case 1:
				ele[j->num].y++;
				if((j->l.bloco[(ele[j->num].x)-6][(ele[j->num].y)-3] !=0))
					ele[j->num].y--;
				break;
			case 2:
				ele[j->num].x--;
				if((j->l.bloco[(ele[j->num].x)-6][(ele[j->num].y)-3] !=0))
					ele[j->num].x++;
				break;
			case 3:
				ele[j->num].x++;
				if((j->l.bloco[(ele[j->num].x)-6][(ele[j->num].y)-3] !=0))
					ele[j->num].x--;
				break;
				
			}
		printf(" %d",j[1].l.bloco[(ele[j[1].num].x)-6][(ele[j[1].num].y)-3]);
}	
	sleep(1);
} 
while(!j->fim);
pthread_exit(0);

}
void sinal_shutdown(int sinal){
	int i;

	printf("Recebi o sinal %d (crtl+c), vou desligar...\n", sinal);
	
        for(i=0;i<TAM;i++){
            if(clientes[i].pid!=0)
                kill(clientes[i].pid, SIGUSR1);
        }
	unlink(FIFO_SERV);
	sleep(2);
	exit(1);
}

void iniciatab(labi *x, int alt, int larg )// PREENCHE O LABIRINTO!!!
{

 x->largura = larg; 
 x->altura = alt; 

 for (int i = 0 ; i < alt ; i++ )
	{
		for ( int j = 0 ; j < larg ; j++ )  	
		{
			if(j == 0 || j == larg-1 || i == 0 || i == alt-1)
			{
				x->lab[j][i] = '#'; // Bloco Indestrutivel
				x->bloco[j][i] = 1;
			}else
				if(i >= 2 && i < alt-2 && j >= 2 && j < larg-2 && i%2 != 1 && j%2 != 1)
				{
					x->lab[j][i] = '#'; // Bloco Indestrutivel Interior
					x->bloco[j][i] = 1;				
				}else
					if(rand() % 100 < 30 && (i > 2 || j > 3))// 80%
					{
						x->lab[j][i] = '1'; //Bloco Destrutivel
						x->bloco[j][i] = 2;
						
					}else
			{
			x->lab[j][i] = ' '; //Passagem
			x->bloco[j][i] = 0;
			}
		}
	}
j->l = *x;

}

void leinfo( char *nomefich)
{
	FILE *f;
	char teste1[CHAR];
	char teste2[100];
	int conta;
	f= fopen( nomefich , "rt");


	if(f==NULL)
	{
	   printf("Erro ao abrir ficheiro %s ", nomefich);
	fclose(f) ;
	}	
while(fscanf(f,"%s %s\n",teste1, teste2)==2)
		{
			printf(" NOME %s PASS %s\n",teste1,teste2);	
		}

fclose(f);
}


void guardainfo(char *nomefich, play *p)	//Acrescenta novo Jogador 
{
	FILE *f;
	char nome[100];
	char pass[100];
	int teste;
	f= fopen( nomefich , "at");
		
	if(f==NULL)
	{
	   printf("Erro ao abrir ficheiro %s ", nomefich);
	fclose(f) ;
	}		

	fprintf(f,"%s %s\n",p->nome, p->passw);

	fclose(f);
	
	

}


int verificainfo(char *nomefich, play p)
{
	FILE *f; 
	f =fopen ( nomefich ,"rt");
	char nome[100];
	char passw[100];	
	if(f== NULL ) 
	{
		printf("Ficheiro Inexistente.\n Criando  ficheiro %s",nomefich);
		return 1;
	}
	
	while(fscanf(f,"%s %[^\n]",nome,passw)==2)
		{
			if((strcmp(nome,p.nome) == 0))
			{
				return 0;			
			}			
		}

fclose(f);
return 1 ;
}


int verificainfologin(char *nomefich, play p)
{
	FILE *f; 
	f =fopen ( nomefich ,"rt");
	char nome[100];
	char passw[100];	
	if(f== NULL ) 
	{
		printf(" Erro ao abrir ficheiro %s \n",nomefich);
		return 1;
	}
	
	while(fscanf(f,"%s %[^\n]",nome,passw)==2)
		{
			 
			if((strcmp(nome,p.nome)) == 0 && (strcmp(passw,p.passw))== 0)
			{
				printf("\n DADOS INTRODUZIDOS CORRECTOS ! \n" );
				return 0;			
			}
		
		}

	fclose(f);
	return 1 ;
}



int contapalavras(char *nome)
{
int palavra =  0; 
for ( int i = 0 ; i < strlen(nome) ; i++) 
		{
			if ( nome[i] == ' ')
				palavra++;
		}	
return palavra;
}

void login( char* comando,play *p) 
{
char comandoo[100];
char nome[100];
int tam = 0;

		sscanf(comando,"%s %s %s",comandoo,p->nome,p->passw);
	
		tam = verificainfo("nometeste.txt", *p);
			

		if(tam!= 0 ) 
			if(strcmp(comandoo,"add")== 0)
		     {
			guardainfo("nometeste.txt",p);	
			printf("\n") ; 			
				
		     }
		else
			{
				printf("comando errado\n");
			       
			}
	strcpy(comando,nome);

}

RESPOSTA * inilogin(play p,RESPOSTA *r, int *joga)
{
	int tam = 0 ;

	tam = verificainfologin("nometeste.txt",p);
	
	if(tam== 0)
	
		{
			printf("\n Bem Vindo %s\n",p.nome);
			r->num=1;
			r->jog = *joga;
			j[*joga].humano = 1;
			r->bomb = 3;
			r->superb = 1;
			printf("joga = %d, res.jog = %d", *joga, j[*joga].humano);
			(*joga)++;	
		}
	else
		{
		printf("Credenciais Erradas \n" );
			r->num= 0 ;		
		}
}

RESPOSTA * actualizadados(RESPOSTA *res,labi *a, play p)
{
//int *jogaa   = joga;
 
for(int  z=  0 ; z < 4; z++){
	for (int i = 0 ; i < a->altura ; i++ )
	{
		for ( int c = 0 ; c < a->largura; c++ )  	
		{
			res->a.lab[c][i] = a->lab[c][i];
		 	
			j[z].l.lab[c][i] = a->lab[c][i];
			j[z].l.bloco[c][i]  = a->bloco[c][i];	
			 
			}
		}
	}
		res->a.altura = a->altura;
		res->a.largura = a->largura;
		j->l.altura = a->altura;
		j->l.largura = a->largura;
	//j[*joga].num=0;

	switch(p.ch){
			case 'w':
				ele[p.jog].y--;
				if((a->bloco[(ele[p.jog].x)-6][(ele[p.jog].y)-3] !=0))
					ele[p.jog].y++	;
				
				break;
			case 's':
				ele[p.jog].y++;
				if((a->bloco[(ele[p.jog].x)-6][(ele[p.jog].y)-3] !=0))
					ele[p.jog].y--;
				break;
			case 'a':
				ele[p.jog].x--;
				if((a->bloco[(ele[p.jog].x)-6][(ele[p.jog].y)-3] !=0))
					ele[p.jog].x++;
				break;
			case 'd':
				ele[p.jog].x++;
				if((a->bloco[(ele[p.jog].x)-6][(ele[p.jog].y)-3] !=0))
					ele[p.jog].x--;
				break;
			case 'h':
					if(res->bomb > 0 ){
				a->lab[(ele[p.jog].x)-6][(ele[p.jog].y)-3]='B';
				res->bomb--;
			//	res->ready=1;
					}
				else 				
					break;
	}
	
//	printf("bloco %d , x = %d, y = %d , bomb = %d", a->bloco[(ele[p.jog].y)-6][(ele[p.jog].x)-3], ele[p.jog].y-3, ele[p.jog].x-6,res->bomb);
	
	for(int i = 0; i < 4; i++){
		res->pos[i].x = ele[i].x;
		res->pos[i].y = ele[i].y;
	}

	return res;

}
labi a;
int main(){

	RESPOSTA res;
	//JOGADOR jo ;
	int tam;
	play p;
	//labi a;
	int conta = 0  ;
	int joga = 0;
	int palavra= 0;
	char comando[100];
	char nome[100]; 
	char comandoo[100];
	char controlo[100];
	int fd, fd_resp, cli = 0, ret, i;
	char cmd[20];
	pthread_t tarefa[4];
	
	fd_set rfds;
        struct timeval tv;

	//Garantir que só existe um servidor
        if(access(FIFO_SERV, F_OK)==0){
		printf("Ja existe um servidor a correr...\n");
		exit(1);
	}

	signal(SIGINT, sinal_shutdown); // ctrl + c
	
	mkfifo(FIFO_SERV, 0600);

	fd = open(FIFO_SERV, O_RDWR);

	

	do{	setbuf(stdout,NULL);
            	FD_ZERO(&rfds);
            	FD_SET(0, &rfds); // toma atenção ao teclado
            	FD_SET(fd, &rfds); // toma atenção ao fifo
            	tv.tv_sec = 0.05; // tempo de espera!
            	tv.tv_usec = 0; 

            	ret = select(fd+1, &rfds, NULL, NULL, &tv); // espera
            	if(ret == 0)
		{ 
				
			//Envio Automático para o Cliente
			for(i=0; i<TAM; i++)
			{
            		if(clientes[i].pid!=0){
					//printf("\nCliente: %d", clientes[i].pid);
					sprintf(str, "ccc%d", clientes[i].pid);	
					fd_resp=open(str, O_WRONLY);

					for(int x= 0; x < 4; x++)
						res.pos[x] = ele[x];
					
					// Envio da Resposta ao Cliente
        				write(fd_resp, &res, sizeof(res));
        				close(fd_resp);
					//printf("\nCliente : %d", clientes[i].pid);
				}
			}
                	//printf(".");
                	fflush(stdout);
           	}else 
		if(ret > 0)
		{
                	if (FD_ISSET(0, &rfds))
			{
                		//Ler dados do teclado
                		scanf( " %[^\n]s",comando);
			if ( (palavra = contapalavras(comando) ) == 2)
			{	
				sscanf(comando,"%s",comandoo);
			
				if(strcmp(comandoo,"add")==0)
				{			
					login(comando,&p);
					p.pid= getpid();
				}else printf("COMANDO ERRADO\n" );				
			}else		
			if((palavra = contapalavras(comando) ) == 0)
			{	
			
			if((strcmp(comando,"listar")) == 0)
				{	
					leinfo("nometeste.txt");
				}else
			if((strcmp(comando,"users")) == 0)
				{	
					for(int c=0; c<TAM; c++)
                        			printf("%s %d\n", clientes[c].nome, clientes[c].pid);
				}
			else
			if((strcmp(comando,"shutdown")) == 0)
				strcpy(cmd,comando);
				else printf("COMANDO ERRADO\n" );
			
			}else

			if((palavra =contapalavras(comando) ) == 1)
			{
				sscanf(comando,"%s %s ",comandoo,controlo);
				
			if((strcmp(comandoo,"inicia")) == 0 &&(strcmp(controlo,"mapa")) == 0)
				{
					iniciatab(&a, 15 ,60);
					sleep(1);					
					//j->l = a; // Constroi mapa
					//for(int j = 0; j < a.altura; j++)
					//		for(int z = 0; z < a.largura; z++)
					//			bloco[z][j] = a.bloco[z][j];					
					for(i = 0; i < 4; i++){	
						pthread_create(&tarefa[i], NULL, mover, (void *) &j[i]);
					}
					printf("\n\nInicio");
				}else
			if((strcmp(comandoo,"kick")) == 0 )
				{	for(i = 0 ; i < TAM ; i++)
					if(strcmp(clientes[i].nome,controlo)==0)
		                		{
							kill(clientes[i].pid, SIGUSR1);
							clientes[i].pid= 0 ;						
							strcpy(clientes[i].nome , "" );						
													
						}
				}else printf("COMANDO ERRADO\n" );
			}else
				printf("COMANDO ERRADO\n" );
		}
		 	
			if(FD_ISSET(fd, &rfds))
			{
	              	  //Ler dados do FIFO...
				i=read(fd, &p, sizeof(p));
				if(i==sizeof(p))
				{		
					if(p.check == 0){
						inilogin(p,&res, &joga);
					}
					else{			
		
						// Apresenta Dados no Servidor
						printf("Chegou um pedido [%d] bytes)\n",i);
						//printf("\n%s %s \n;" , p.nome, p.passw);
						//Guarda Cliente no Servidor            	 			
							int existe = 0;
              	 			int livre = -1;
               				for(i=0; i<TAM; i++)
					{
                    			if(clientes[i].pid == 0 && livre == -1)
                     				 livre = i;
                    			if(clientes[i].pid == p.pid)
                        			{existe = 1;
						clientes[i].pid =p.pid ;
						strcpy(clientes[i].nome,p.nome);
						printf(" %d %s \n",clientes[i].pid,clientes[i].nome);
						}               				 
					}
                			if(!existe && livre >=0)
					{
                    				clientes[livre].pid = p.pid;
						strcpy(clientes[livre].nome,p.nome);
						cli++;
					}

					 	actualizadados(&res,&a, p);
						}
	
					sprintf(str, "ccc%d", p.pid);	
					fd_resp=open(str, O_WRONLY);
					
				// Envio da Resposta ao Cliente
        				write(fd_resp, &res, sizeof(res));
					//printf(" %d ", getpid());
					//printf("%d",res.num);
        				close(fd_resp);
				
				}
                			
            			}
			}	
		}while(strcmp(cmd,"shutdown")!= 0);

	for(i=0; i<4; i++){
                j[i].fim = 1;
		pthread_join(tarefa[i], NULL);
	}
	
	for(i=0; i<TAM; i++)
		{
            		if(clientes[i].pid!=0)
                		kill(clientes[i].pid, SIGUSR1);
				
        	}

		close(fd);
		printf("\nA ENCERRAR ...\n");
		unlink(FIFO_SERV);
		iniciatab(&a, 15 ,60);
}







