#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char nord,est,ouest,sud;
}bloc;

typedef struct
{
	int taille;
	bloc* rangee;
	
}ligne;


typedef struct
{
	int taille;
	ligne* l;

}plateau;



bloc* creerBloc(char n,char e,char o,char s)
{
		bloc* b=(bloc*)malloc(sizeof(bloc));
		b->nord=n;
		b->est=e;
		b->ouest=o;
		b->sud=s;
		
		return b;	
}

void freeB(bloc* b)
{
    free(b);
}

char getN(bloc* b)
{
    return b->nord;
}

char getE(bloc* b)
{
    return b->est;
}

char getO(bloc* b)
{
    return b->ouest;
}

char getS(bloc* b)
{
    return b->sud;
}


void initLigne(ligne* l,int t)
{
	l->rangee=(bloc*)malloc(t*sizeof(bloc));
	l->taille=t;	
}

void initPlateau(plateau* p, int t)
{
	p->l=(ligne*)malloc(t*sizeof(ligne));
	p->taille=t;
	initLigne(p->l,t);
}


void setBloc(ligne* r,bloc b,int pos)
{
	r->rangee[pos]= b;
}

void freeL(ligne* l)
{
	free(l->rangee);
	free(l);
}

void swapBloc(bloc* a,bloc* b)
{
	bloc* c; c=a; a=b; b=c;
}

bloc* LireD(plateau* p,char* e)
{
	int l,k;
	for(int i=0;i<p->taille;i++){
		if(e[0]='a'+i){ l=i+1;}
	}
	for(int i=0;i<p->taille;i++){
		if(e[1]=i+1) { k=i+1;}
	}
	return &(p->l[l].rangee[k]);
	
}

bloc* LireF(plateau* p,char* e)
{
	int l,k;
	for(int i=0;i<p->taille;i++){
		if(e[2]='a'+i){ l=i+1;}
	}
	for(int i=0;i<p->taille;i++){
		if(e[3]=i+1) { k=i+1;}
	}
	return &(p->l[l].rangee[k]);
	
}

void setLigne(plateau* p,ligne l,int pos)
{
		p->l[pos]=l;
}


void freeP(plateau* p)
{
	free(p->l);
	free(p);
}



int main(){
	
	bloc* b=creerBloc('A','D','C','C');
	printf("au nord %c au sud %c à l'est %c à l'ouest %c",getN(b),getS(b),getE(b),getO(b));
	freeB(b);
	

}