//view.c
//Grupo Brumenau
//Vitor Assuncao
//Gabriel Souza
//Pedro Henrique  Saraiva
//David Miranda
#include "JVida-BRU_model.h"
#include "JVida-BRU_controller.h"
#include <stdio.h>
//menu que sempre e repitido durante o jogo
int menu2()
{
	
	int op;
	
		printf("\n Jogo da Vida BRU");
		printf("\n 1) Mostrar mundo");
        printf("\n 2) posicionar celulas");
        printf("\n 3) Limpar o mundo");
        printf("\n 4) Mostrar lista de vivos e mortos");
        printf("\n 5) Mostrar as celulas mortas-vizinhas");
        printf("\n 6) salvar mundo");
        printf("\n 7) carregar mundo");
        printf("\n 8) iniciar processo");
        printf("\n 0) Sair\n");
        scanf("%d",&op);
	
	return(op);
}

//menu que perunta tamanho da matriz mundo
void menu1()
{
		
	manso = 0;	
	do{
	
	printf("digite o tamanho do mundo (min:10, max:60 )\n");
	scanf("%d", &tmat);
	
	
	
	if (tmat<10 || tmat>60) { 
        	printf("digite um numero entre 10 e 60\n"); 
        	continue;
    }
    else
    	tmundo();
	
	}while (tmat<10 || tmat>60);
}

void poscelula()
{
	
	int i, j;
	int apg;
	
	do 
	{

    	printf("\nDigite a coordenada desejada,ex(-1,-1 para sair): ");
    	scanf("%d,%d", &i, &j); 
    
    	if (i!=-1 && j!=-1){
    		
    		if (i<0 || i>=tmat || j<0 || j>=tmat){ 
        	printf("A cooredenada digitada nao existe\n"); 
        	continue;
        	}
		} else 
		break;
    
    	
    
    	
      	if (mundo[i][j]=='O') 
		{
     		 printf("Ja existe uma celula nessa posicao, quer exclui-la? (0 nao, 1 sim) \n");
     		 scanf("%d", &apg);
     		 
     		 if (apg==1)
			 {
			 mundo[i][j]='.';
     		 excluiLvivo(i, j);
     		 mostramatriz();
     		 }
			 	
		}else{
	 		mundo[i][j] = 'O';   
      		printf("Individuo posicionado\n");
      		carregavivo(i,j);
      		mostramatriz();
      		CarregaVizinhos(i, j);
		}
   
	}
	while (i!=-1 || j!=-1);
    
} 	

//funcao para imprimir a matriz
void mostramatriz()
{
	
	int i,j;
	
	
	printf("        ");
    for(j = 0; j < tmat; j++)
        printf("%2d ",j);
    printf("\n\n");

    for(i=0; i < tmat ; i++)
    {
    printf("%2d :\t",i);
    for(j=0; j < tmat; j++)
        printf(" %c ",mundo[i][j]);
    printf("\n");
    }


}

void sair()
{
	
	printf("adeus \n");
	
}

void limpaM()
{
	printf("Mundo limpo \n");
}

void opInvalida()
{
	printf("Opcao invalida \n");
}

void semesp()
{
	printf("sem espaco parar posicionar celulas\n");
}


void ListaVivos()
{
	TipoCel *aux;	//ponteiro auxiliar
	aux = pvivo;	//inicializa ponteiro auxiliar
	if (totvivo > 0)
	{
		printf("Lista de vivos:");
		printf("\n");
		
	while(aux->next != NULL)
		{
		printf("%d,%d   ", aux->lin, aux->col);
		aux = aux->next;	//vai para proximo ponteiro
		}
		printf("%d,%d   ", aux->lin, aux->col);//mostra a ultima celula
	}
		
		printf("\n");
}

void ListaMortos()
{
	
	TipoCel *aux;	
	aux = pmorto;	
	if (totmorto > 0)
	{
		printf("Lista de mortos:");
		printf("\n");	
		
	while(aux->next != NULL)
		{
		printf("%d,%d   ", aux->lin, aux->col);
		aux = aux->next;	
		}
		printf("%d,%d   ", aux->lin, aux->col);
	}
		
		printf("\n");
}

void mostravizinhos()
{
		
	TipoCel *aux;	
	aux = pmorto;	
	if (totmorto > 0)
	{
	while(aux->next != NULL)
		{
		mundo[aux->lin][aux->col] = '+';
		aux = aux->next;	
		}
		mundo[aux->lin][aux->col] = '+';
	}
		
		printf("\n");
}

void desmostravizinhos()
{
		
	TipoCel *aux;	
	aux = pmorto;	
	if (totmorto > 0)
	{
	while(aux->next != NULL)
		{
		mundo[aux->lin][aux->col] = '.';
		aux = aux->next;	
		}
		mundo[aux->lin][aux->col] = '.';
	}
		
		printf("\n");
}


void pulalinha()
{
	printf("\n");
}

void errosalva()
{
	printf("\nerro no salvamento");
}

void errocarrega()
{
	printf("\nerro no carregamento");
}

int crono(){
	
	int op;
	
	printf("Digite o tempo em segundos (0 para fazer passo a passo)\n");
	scanf("%d",&op);

	return op;
	
}

int tiims(){
	
	int op;
	
	printf("Digite a quantidade de vezes para serem executadas na simulacao \n");
	scanf("%d",&op);
	
	
	
	return op;
	
}

int nova(){
	
	int op;
	bala=0;
	
	do{
		printf("ir para proxima geracao? (1 p/sim e 0 p/nao)\n");
		scanf("%d",&op);
		
	}while(op!=1 && op!=0);
	return op;
		
		

	
	
}

void ListaProx()
{
	TipoCel *aux;	//define um ponteiro auxiliar
	aux = pvivoprox;	//inicializa esse ponteiro auxiliar
	if (totvivoprox > 0)
	{
		printf("Lista dos proximos:");
		pulalinha();
		
	while(aux->next != NULL)
		{
		printf("%d,%d   ", aux->lin, aux->col);
		aux = aux->next;	//caminha para o proximo ponteiro
		}
		printf("%d,%d   ", aux->lin, aux->col);//mostra a ultima celula
	}
		
		printf("\n");
}


