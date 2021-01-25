#include "labirinto.h"

void imprime(labi x) // IMPRIME O LABIRINTO!
{	
	int i , j;
	for ( i  = 3 ; i < x.altura + 3 ; i++)
	{
		for( j = 6 ; j <  x.largura + 6 ; j++) 
			{			
				mvaddch(i, j,x.lab[j-6][i-3]);
			}
	}
}
RESPOSTA res;
void sinal(int sinal){
	clear();
	endwin();
	printf("Foste expulso da sessao\n");
	unlink(str);
	sleep(1);
	exit(1);
}

void sinal_shutdown(int sinal){
	
	clear();
	endwin();
	printf("A sair...\n");
	unlink(str);
	sleep(1);		        	
	exit(1);
	
}

play * inicialogin(play *b)
{
 
	int tam = 0 ;

	printf("Usernome:\n") ;
	scanf("%s",b->nome);
	printf("\nPassword: \n"  ); 
	scanf(" %s",b->passw) ;
return b;
}

int main(){

	int fd, i, fd_resp, num,ret;
	
	play p;
	labi a;
	pthread_t le;
	fd_set rfds;
	struct timeval tv;
	//verifica se já existe um servidor a correr
	if(access(FIFO_SERV, F_OK)!=0)
	{
		printf("O servidor nao esta a correr...\n");
		return 1;
	}
	
	p.pid = getpid();
	printf("%d\n",p.pid);
	sprintf(str, "ccc%d", p.pid);
	mkfifo(str, 0600);

	//abrir fifo do servidor
	fd = open(FIFO_SERV, O_WRONLY);

	signal(SIGUSR1, sinal);
	signal(SIGINT, sinal_shutdown); // ctrl + c

	//----------------Login-----------------------------------------------------------------
	do{
		
		inicialogin(&p);
		//printf("\ncheck = %d\n", p.check);
		printf("\n%s %s \n" , p.nome, p.passw);
		//enviar pedido ao servidor...
       	 	write(fd, &p, sizeof(p));
		// Recebe Resposta...
		fd_resp=open(str, O_RDONLY);
		read(fd_resp, &res, sizeof(res));
		p.check = res.num;
		
		//close(fd_resp);	
		}while(p.check == 0);

	//--------------------------------------------------------------------------------------
	p.check = res.num;
	p.bomba = res.bomb;
	p.superbomba = res.superb;
	
	initscr();
		
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_GREEN);
	init_pair(2, COLOR_RED, COLOR_GREEN);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	
	p.jog = res.jog;
	
	do{
	
	FD_ZERO(&rfds);
	FD_SET(0,&rfds);
	FD_SET(fd_resp,&rfds);
	//tv.tv_sec = 1 ;
	//tv.tv_usec = 5000;			
	
	ret  = select ( fd_resp+1, &rfds , NULL, NULL , &tv ) ;

	
	attron(COLOR_PAIR(3));
	mvaddch(res.pos[p.jog].y, res.pos[p.jog].x, ' ');
	
	attron(COLOR_PAIR(1));
	// Grava a tecla	
	if(ret >0)
	{	
	if(FD_ISSET(0,&rfds))	
	{	
	p.ch = getchar();
	
	//enviar pedido ao servidor...
        write(fd, &p, sizeof(p));

	
	}
	}
	
	if(FD_ISSET(fd_resp,&rfds))
	{
	
	// Recebe Resposta...
	read(fd_resp, &res, sizeof(res));
	//p.jog = res.jog;
	
	imprime(res.a);	
	//close(fd_resp);
		
	attron(COLOR_PAIR(2));
	for(i = 0; i < 4; i++){			
		mvaddch(res.pos[i].y ,res.pos[i].x, j[i].cara);
	}
	refresh();
	}
	}while(1);
	// fechar fifo do servidor
	close(fd);
	close(fd_resp);	
	unlink(str);
	pthread_join(le,NULL);
	endwin();
	return 0;
}
