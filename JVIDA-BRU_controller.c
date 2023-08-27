//controller.c
//Grupo Brumenau
//Vitor Assuncao
//Gabriel Souza
//Pedro Henrique  Saraiva
//David Miranda

#include "JVida-BRU_model.h"
#include "JVida-BRU_controller.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void tmundo()
 {
 
 int i,j;
 
 //cria matriz do mundo
 
   for(i=0; i< tmat; i++)        
        for(j=0; j< tmat; j++)  
    mundo[i][j] = '.';
    
    
}

void percorrer()
 {
 
 int i,j;
 
 //popula a matriz do mundo
 
   for(i=0; i< tmat; i++)        
        for(j=0; j< tmat; j++)  
    if (mundo[i][j]=='O') 
		{
     		 
	 		mundo[i][j] = 'O';   
      		carregavivo(i,j);
      		
      		CarregaVizinhos(i, j);
		}
    
    
}

//recebe o return do menu
void jogo(){
	
	int op;
	
	do{
		
		op= menu2();
		
		switch (op){
		
		
		case 1: 
			mostramatriz();
			break;
		
		case 2:
			mostramatriz();
			poscelula();
			break;
		
		case 3:
			tmundo();
			limpalistavivo();
			limpalistamorto();
			limpaM();
			break;
		case 4:
			ListaVivos();
			ListaMortos();
			ListaProx();
			break;
			
		case 5:
			mostravizinhos();
			mostramatriz();
			desmostravizinhos();
			break;
		
		case 0:
			sair();
			break;
		
		case 6:
			salvacel();
			break;
		
		case 7:
			limpalistavivo();
			limpalistamorto();
			tmundo();
			carregacel();
			percorrer();
		case 8:
			proxmorto();
			proxvivo();
			geradorgeracao();
			
			break;
		default:
			opInvalida();
			break;
		
		}
	}while (op!=0);
	
	
	
}


void carregavivo(int ii, int jj)
{
	TipoCel *aux = malloc(sizeof(TipoCel));   //alocacao dinamica
	if (aux == NULL)
	{	
	semesp();
	return;
	}
	
	aux->lin = ii;
	aux->col = jj;
	
	if(totvivo== 0)  //caso a lsita esteja vazia
	{
	pvivo = aux;
	pvivo->next = NULL;
	
	}
	else                //lista nao est vazia
	{
	aux->next = pvivo;
	pvivo = aux;  //o inicio da lista passa a ser a nova celula
	}
	totvivo++;
}

//funcao para que o usuario interaja tanto posicionando ou removendo celulas
void excluiLvivo(int ii, int jj)
{
	TipoCel *aux, *aux2;
	
	aux = pvivo;
	aux2 = aux;
	
	if (totvivo > 0)
	{
		while (aux->lin != ii || aux->col != jj)
		{
		aux2 = aux;
		aux = aux->next;
		}
		if (aux->lin == ii && aux->col == jj)
		{
			if (aux2 == aux)   // primeiro da lista
				pvivo = aux->next;
			else
				aux2->next = aux->next;
			free(aux);
				
		}totvivo--;
	}
}

//func para limpar matriz e a lista
void limpalistavivo()
{
    TipoCel *aux;
    
    
    aux = pvivo;
	
	if (totvivo>0){
	
    
    while(aux <= totvivo)
        {
        free(aux);
         aux = aux->next;
    	}
		
	totvivo=0;
    aux = aux->next;
    free(aux);
    

    pulalinha();
	}
	else 
		return 0;
    
}
//limpa a lista de vizinhos mortos
void limpalistamorto() 
{
    TipoCel *aux;

    
    aux = pmorto;
	
    if (totmorto>0){
	
    while(aux <= totmorto)
        {
        free(aux);
         aux = aux->next;
         
    	}
		totmorto=0;
	
    aux = aux->next;
    free(aux);
	

    pulalinha();
	}
}

void carregamorto(int lin, int col){
	
	if ((lin>=0 && lin<tmat) && (col>=0 && col<tmat) && (mundo[lin][col]!='O') ){
		if (comparador(lin,col) == 1)
		
			crialistamorto(lin,col);
		
		
		
	}
	
	
}



//funcao que carrega Mortos Vizinhos
void CarregaVizinhos(int ii, int jj) {
	
	limpalistamorto();
	
	TipoCel *aux= pvivo;
	
	while(aux->next != NULL)
		{
			
		carregamorto(aux->lin+1, aux->col+1);
		carregamorto(aux->lin+1, aux->col-1);
		carregamorto(aux->lin-1, aux->col+1);
		carregamorto(aux->lin+1, aux->col);
		carregamorto(aux->lin, aux->col+1);
		carregamorto(aux->lin-1, aux->col);
		carregamorto(aux->lin, aux->col-1);
		carregamorto(aux->lin-1, aux->col-1);	
			
		aux=aux->next;
		}
		carregamorto(aux->lin+1, aux->col+1);
		carregamorto(aux->lin+1, aux->col-1);
		carregamorto(aux->lin-1, aux->col+1);
		carregamorto(aux->lin+1, aux->col);
		carregamorto(aux->lin, aux->col+1);
		carregamorto(aux->lin-1, aux->col);
		carregamorto(aux->lin, aux->col-1);
		carregamorto(aux->lin-1, aux->col-1);
		
		
	

}

//funcao para adicionar seres mortos vizinhos
void crialistamorto(int ii, int jj)
{
	
	TipoCel *aux = malloc(sizeof(TipoCel));   
	if (aux == NULL)
	{	
	semesp();
	return;
	}

	aux->lin = ii;
	aux->col = jj;

	if(totmorto== 0)  
	{
	pmorto = aux;
	pmorto->next = NULL;
	
	}
	else                
	{
	aux->next = pmorto;
	pmorto = aux;  
	}
	totmorto++;
}

//funcao para encontrar espacos livres proximos a uma celula viva
int comparador(int lin, int col){
	
	TipoCel *aux= pmorto;
	
	if(totmorto==0)
	return 1;
	
	else{
	
	
	while(aux->next != NULL)
	{
		if ((aux->col == col) && (aux->lin == lin))
			return 0;
			
		aux=aux->next;
		
	}
	if ((aux->col == col) && (aux->lin == lin))
		return 0;
	
	else 
		return 1;
	}
}

void salvacel()
{
	int i, j;

	FILE *fp;

	if ((fp = fopen("CONFIG_INIC", "w")) == NULL)
	{
		errosalva();
	}

	for (i = 0; i < tmat; i++)
	{
		for (j = 0; j < tmat; j++)
		{
			if (fwrite(&mundo[i][j], sizeof(mundo), 1, fp) != 1)
			{
				errosalva();
				break;
			}
		}
	}

	fclose(fp);

	if ((fp = fopen("tmat", "w")) == NULL)
	{
		errosalva();
	}

	if (fwrite(&tmat, sizeof(tmat), 1, fp) != 1)
	{
		errosalva();
		return 1;
	}
}

void carregacel()
{
	int i, j;

	if(manso==1)
	{
	tmundo();
	limpalistavivo();
	limpalistamorto();
	}

	FILE *fp;

	if ((fp = fopen("tmat", "r")) == NULL)
	{
		errocarrega();
	}

	if (fread(&tmat, sizeof(tmat), 1, fp) != 1)
	{
		errocarrega();
	}
	fclose(fp);

	if ((fp = fopen("CONFIG_INIC", "r")) == NULL)
	{
		errocarrega();
	}

	for (i = 0; i < tmat; i++)
	{
		for (j = 0; j < tmat; j++)
		{
			if (fread(&mundo[i][j], sizeof(mundo), 1, fp) != 1)
			{
				errocarrega();
				break;
			}
		}
	}

	fclose(fp);

	for (i = 0; i < tmat; i++)
	{
		for (j = 0; j < tmat; j++)
		{
			if (mundo[i][j] == "O")
			{
				carregavivo(i, j);
				CarregaVizinhos(i, j);
			}
		}
	}
}



//verificamos os espaços ocupados por seres vivos para inicializar 
//um contador que atenda as condições de sobrevivência das gerações futuras
void rulesofsurvival(int lin, int col){
	
	if ((lin>=0 && lin<tmat) && (col>=0 && col<tmat) && (mundo[lin][col] == 'O') )
			neymar+=1;

}


//testamos as regras de sobrevivência
void proxmorto(){
	


	TipoCel *aux;	
	aux = pmorto;	
	if (totmorto > 0)
	{
		pulalinha();
		
	while(aux->next != NULL)
		{
			
		neymar=0;	
		
		rulesofsurvival(aux->lin+1, aux->col+1);
		rulesofsurvival(aux->lin+1, aux->col-1);
		rulesofsurvival(aux->lin-1, aux->col+1);
		rulesofsurvival(aux->lin+1, aux->col);
		rulesofsurvival(aux->lin, aux->col+1);
		rulesofsurvival(aux->lin-1, aux->col);
		rulesofsurvival(aux->lin, aux->col-1);
		rulesofsurvival(aux->lin-1, aux->col-1);	
		
		if (neymar == 3)
			listaaux(aux->lin, aux->col);
			
	
			
		aux = aux->next;	
		
		
		}
		
		neymar=0;	
		
		rulesofsurvival(aux->lin+1, aux->col+1);
		rulesofsurvival(aux->lin+1, aux->col-1);
		rulesofsurvival(aux->lin-1, aux->col+1);
		rulesofsurvival(aux->lin+1, aux->col);
		rulesofsurvival(aux->lin, aux->col+1);
		rulesofsurvival(aux->lin-1, aux->col);
		rulesofsurvival(aux->lin, aux->col-1);
		rulesofsurvival(aux->lin-1, aux->col-1);	
		
		if (neymar == 3)
			listaaux(aux->lin, aux->col);
			
	

		
		
	
	}
	
}

//testamos as regras da sobrevivencia
void proxvivo(){
	
	TipoCel *aux;	
	aux = pvivo;	
	if (totvivo > 0)
	{
		pulalinha();
		
	while(aux->next != NULL)
		{
			
		neymar=0;	
		
		rulesofsurvival(aux->lin+1, aux->col+1);
		rulesofsurvival(aux->lin+1, aux->col-1);
		rulesofsurvival(aux->lin-1, aux->col+1);
		rulesofsurvival(aux->lin+1, aux->col);
		rulesofsurvival(aux->lin, aux->col+1);
		rulesofsurvival(aux->lin-1, aux->col);
		rulesofsurvival(aux->lin, aux->col-1);
		rulesofsurvival(aux->lin-1, aux->col-1);	
		
		if ((neymar == 2) || (neymar ==3))
			listaaux(aux->lin, aux->col);
			
	
			
			
		aux = aux->next;
		}
		
		neymar=0;	
		
		rulesofsurvival(aux->lin+1, aux->col+1);
		rulesofsurvival(aux->lin+1, aux->col-1);
		rulesofsurvival(aux->lin-1, aux->col+1);
		rulesofsurvival(aux->lin+1, aux->col);
		rulesofsurvival(aux->lin, aux->col+1);
		rulesofsurvival(aux->lin-1, aux->col);
		rulesofsurvival(aux->lin, aux->col-1);
		rulesofsurvival(aux->lin-1, aux->col-1);	
		
		if ((neymar == 2) || (neymar ==3))
			listaaux(aux->lin, aux->col);
		
		
	
	}
	
			
	
}	
	
//timer para passar geracao
void timer(int spd){
	
	time_t lt1, lt2;
	lt1= time(NULL);
	lt2=lt1;
	while(difftime(lt2,lt1) < spd)
         lt2=time(NULL);
         
}


//funcao para passar a lista principal para auxiliar
void geradorgeracao(){
	
	bala=crono(); 
		
	
	
	if (bala==0){
	
	
		do{
	
			vamp=nova();
	
			if (vamp==0)
			break;
	
			tmundo();
			limpalistavivo();
			limpalistamorto();	
			
			TipoCel *aux;	
			aux = pvivoprox;	
			if (totvivoprox > 0)
			{
			pulalinha();
		
				while(aux->next != NULL)
				{
				
			
				carregavivo(aux->lin, aux->col);	
				CarregaVizinhos(aux->lin, aux->col);
			
			
		
				mundo[aux->lin][aux->col] = 'O';
				percorrer();
				
				proxmorto();
				proxvivo();
				
				
				aux = aux->next;
				
				
				}
			
				carregavivo(aux->lin, aux->col);
				mundo[aux->lin][aux->col] = 'O';
				CarregaVizinhos(aux->lin, aux->col);
			
				
			
				
			}
		limpalista();
		proxmorto();
		proxvivo();
		
			
		mostramatriz();	
		
		
		}while(vamp!=0);
	}
	
	else
	{
		
		int contime=0;
		int repeat = tiims();
		do
		{
			crono(bala);
			tmundo();
			limpalistavivo();
			limpalistamorto();	
			
	
			
	
	
			TipoCel *aux;	
			aux = pvivoprox;	
			if (totvivoprox > 0)
			{
			pulalinha();
		
				while(aux->next != NULL)
				{
				
			
				carregavivo(aux->lin, aux->col);	
				CarregaVizinhos(aux->lin, aux->col);
			
			
		
				mundo[aux->lin][aux->col] = 'O';
				percorrer();
				
				proxmorto();
				proxvivo();
				
				
				aux = aux->next;
				
				
				}
			
			
				carregavivo(aux->lin, aux->col);
				mundo[aux->lin][aux->col] = 'O';
				CarregaVizinhos(aux->lin, aux->col);
			
				
			
				
			}
		limpalista();
		proxmorto();
		proxvivo();
		
			
		mostramatriz();	
		
		contime+=1;
		
		} while (contime<repeat);
	}
	
}

//cria lista auxiliar para nova geracao
void listaaux(int ii, int jj){

	TipoCel *aux = malloc(sizeof(TipoCel));   
	if (aux == NULL)
	{	
	semesp();
	return;
	}
	
	aux->lin = ii;
	aux->col = jj;
	
	if(totvivoprox== 0)  //se a lista está vazia
	{
	pvivoprox = aux;
	pvivoprox->next = NULL;
	
	}
	else                //lista nao vazia
	{
	aux->next = pvivoprox;
	pvivoprox = aux;  //o inicio da lista passa a ser a nova celula
	}
	totvivoprox++;

	
}

void limpalista() 
{
    TipoCel *aux;

    
    aux = pvivoprox;
	
    if (totvivoprox>0){
	
    while(aux <= totvivoprox)
        {
        free(aux);
         aux = aux->next;
         
    	}
		totvivoprox=0;
	
    aux = aux->next;
    free(aux);
	

    printf("\n");
	}else
	
	return 0;
}

