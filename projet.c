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

}plateau;


bloc* creerBloc(char n,char e,char s,char o)
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

void setN(bloc* b,char n){
    b->nord=n;
}

void setE(bloc* b,char n){
    b->est=n;
}

void setO(bloc* b,char n){
    b->ouest=n;
}

void setS(bloc* b,char n){
    b->sud=n;
}

int verifBloc(bloc* a,bloc* b,int cote)
{
	int erreur=0;
	if(cote==1)
	{
		if((getN(a)!=getS(b)))
		{
			erreur++;
		}
	}
	else
	{
		if((getE(a)!=getO(b)))
		{
			erreur++;
		}
	}

	return erreur;
}

int verifPlateau(plateau* p)
{
	int erreur=0;
	for(int i=0;i<p->taille;i++)
	{
		for(int j=0;j<p->l->taille;j++)
		{
			if(i==0)
			{
				if(!(j==p->l->taille-1))
				{
					erreur+=verifBloc(&(p->l[i].rangee[j]),&(p->l[i].rangee[j+1]),0);
				}
			}
			else
			{
				if(i==p->taille-1)
				{

					if(!(j==p->l->taille-1))
					{
						erreur+=verifBloc(&(p->l[i].rangee[j]),&(p->l[i].rangee[j+1]),0);
						erreur+=verifBloc(&(p->l[i].rangee[j]),&(p->l[i-1].rangee[j]),1);
					}
					else
					{
						erreur+=verifBloc(&(p->l[i].rangee[j]),&(p->l[i-1].rangee[j]),1);
					}
				}
				else
				{
					if(!(j==p->l->taille-1))
					{
						erreur+=verifBloc(&(p->l[i].rangee[j]),&(p->l[i].rangee[j+1]),0);
						erreur+=verifBloc(&(p->l[i].rangee[j]),&(p->l[i-1].rangee[j]),1);
					}
					else
					{
						erreur+=verifBloc(&(p->l[i].rangee[j]),&(p->l[i-1].rangee[j]),1);
					}
				}

			}
		}
	}
	return erreur;
}

void affectBloc(ligne* r,bloc* b,int pos)
{
	r->rangee[pos]=*b;
}

void gener(plateau* p)
{
	for(int i=0;i<p->taille;i++)
	{
		for(int j=0;j<p->l->taille;j++)
		{
			bloc* b=creerBloc('A','B','C','D');
			affectBloc(&(p->l[i]),b,j);
		}
	}
}

void dessin(plateau* p)
{
    int r=p->taille;
    printf("   ");
    for(int i=0;i<r;i++)
    {
        char a='1'+i;
        printf("  %c  ",a);
    }
    printf("\n");
    printf("\n");

    for(int k=0;k<r;k++)
    {
		printf("   ");
		for(int i=0;i<r;i++)
        {
            char n=getN(&(p->l[k].rangee[i]));
            printf("  %c  ",n);
        }
        printf("\n");
        char q='a'+k;
        printf("%c  ",q);
        for(int i=0;i<r;i++)
        {
            char o=getO(&(p->l[k].rangee[i]));
            char e=getE(&(p->l[k].rangee[i]));
            printf("%c # %c",o,e);
        }
        printf("\n");
        printf("   ");
        for(int i=0;i<r;i++)
        {
            char s=getS(&(p->l[k].rangee[i]));
            printf("  %c  ",s);
        }
        printf("\n");
    }




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
	for(int i=0;i<t;i++)
	{
		initLigne(&(p->l[i]),t);
	}
}

void freeL(ligne* l)
{
	freeB(l->rangee);
	free(l);
}

void swapBloc(bloc* a,bloc* b)
{
	bloc* c=creerBloc(getN(a),getE(a),getS(a),getO(a));
	setN(a,getN(b));
	setE(a,getE(b));
	setS(a,getS(b));
	setO(a,getO(b));
	setN(b,getN(c));
	setE(b,getE(c));
	setS(b,getS(c));
	setO(b,getO(c));
}

bloc LireD(plateau* p,char* e)
{
	int l=0;
	int k=0;
	for(int i=0;i<p->taille;i++){
		if(e[0]=='a'+i){ l=i;}
	}
	for(int i=0;i<p->taille;i++){
		if(e[1]==i+'1') { k=i;}
	}

	return p->l[l].rangee[k];

}

bloc LireF(plateau* p,char* e)
{
	int l=0;
	int k=0;
	for(int i=0;i<p->taille;i++){
		if(e[2]=='a'+i){ l=i;}
	}
	for(int i=0;i<p->taille;i++){
		if(e[3]==i+'1') { k=i;}
	}
	return p->l[l].rangee[k];

}

void setLigne(plateau* p,ligne l,int pos)
{
		p->l[pos]=l;
}


void freeP(plateau* p)
{
	freeL(p->l);
	free(p);
}


void rotaBloc(plateau* p,char* c)
{
	int l=0;
	int k=0;
	for(int i=0;i<p->taille;i++)
	{
		if(c[0]=='a'+i){ l=i;}
	}
	for(int i=0;i<p->taille;i++)
	{
		if(c[1]==i+'1') { k=i;}
	}

	bloc b=p->l[l].rangee[k];
	char n=getN(&b);
	char e=getE(&b);
	char s=getS(&b);
	char o=getO(&b);
	bloc* b2=creerBloc(o,n,e,s);
	p->l[l].rangee[k]=*b2;
}

int main()
{
	bloc* b=creerBloc('A','D','C','C');
	printf("au nord %c au sud %c à l'est %c à l'ouest %c\n",getN(b),getS(b),getE(b),getO(b));
	bloc* c=creerBloc('A','D','C','C');
	plateau* p=(plateau*)malloc(sizeof(plateau));
	initPlateau(p,4);
	gener(p);
	dessin(p);
	char* co="a4";
	rotaBloc(p,co);
	dessin(p);
	bloc av=LireD(p,"a4d1");
	bloc ap=LireF(p,"a4d1");
	swapBloc(&av,&ap);
	dessin(p);
	printf("au nord %c au sud %c à l'est %c à l'ouest %c\n",getN(&p->l[0].rangee[3]),getS(&p->l[0].rangee[3]),getE(&p->l[0].rangee[3]),getO(&p->l[0].rangee[3]));
	printf("au nord %c au sud %c à l'est %c à l'ouest %c\n",getN(&p->l[3].rangee[0]),getS(&p->l[3].rangee[0]),getE(&p->l[3].rangee[0]),getO(&p->l[3].rangee[0]));
	printf("\n c'est la vérif du plateau %d",verifPlateau(p));


	freeP(p);





}
