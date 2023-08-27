//model.h
//Grupo Brumenau
//Vitor Assuncao
//Gabriel Souza
//Pedro Henrique  Saraiva
//David Miranda
char mundo[60][60];

int tmat;
int manso;

typedef struct cel
{
int lin, col;
struct cel *next;   //ponteiro que calcula tipo de celula
}TipoCel;
	
	
TipoCel *pvivo, *pmorto, *pvivoprox;//3 tipos de celulas  
int totvivo, totmorto, totvivoprox;

int neymar,vamp,bala;
