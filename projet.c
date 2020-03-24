#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void setN(bloc* b,char n)
{
    b->nord=n;
}

void setE(bloc* b,char n)
{
    b->est=n;
}

void setO(bloc* b,char n)
{
    b->ouest=n;
}

void setS(bloc* b,char n)
{
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

void affectBloc(plateau* p,bloc* b,int x,int y)
{
	p->l[x].rangee[y]=*b;
}

void gener(plateau* p)//à suppr plus tard
{
	for(int i=0;i<p->taille;i++)
	{
		for(int j=0;j<p->l->taille;j++)
		{
			bloc* b=creerBloc('A','B','C','D');
			affectBloc(p,b,i,j);
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

void swapBloc(plateau* p,int ax,int ay,int bx,int by)
{
	bloc a =p->l[ax].rangee[ay];
	bloc b = p->l[bx].rangee[by];
	bloc temp=a;

	p->l[ax].rangee[ay]=b;
	p->l[bx].rangee[by]=temp;
}

int LireDX(plateau* p,char* e)
{

	int l;
	for(int i=0;i<p->taille;i++){
		if(e[0]=='a'+i){ l=i;}
	}

	return l;

}

int LireDY(plateau* p,char* e)
{
	int k;
	for(int i=0;i<p->taille;i++){
		if(e[1]==i+'1') { k=i;}
	}
	return k;

}

int LireFX(plateau* p,char* e)
{

	int l;
	for(int i=0;i<p->taille;i++){
		if(e[2]=='a'+i){ l=i;}
	}

	return l;

}

int LireFY(plateau* p,char* e)
{
	int k;
	for(int i=0;i<p->taille;i++){
		if(e[3]==i+'1') { k=i;}
	}
	return k;

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

void remplirPlateau(plateau* p)
{
	plateau* sf;
	initPlateau(sf,p->taille);
	srand ( time(NULL) );
	for(int i=0;i<p->taille;i++)
	{
		for(int j=0;j<p->l->taille;j++)
		{
			if(i==0)
			{
				if(j==0)
				{
					int c1=rand()%4;char n='A'+c1;
					int c2=rand()%4;char e='A'+c2;
					int c3=rand()%4;char s='A'+c3;
					int c4=rand()%4;char o='A'+c4;
					bloc* b=creerBloc(n,e,s,o);
					affectBloc(sf,b,i,j);
				}
				else
				{
					int c1=rand()%4;char n='A'+c1;
					int c2=rand()%4;char e='A'+c2;
					int c3=rand()%4;char s='A'+c3;
					bloc* b=creerBloc(n,e,s,getE(&p->l[i].rangee[j-1]));
					affectBloc(sf,b,i,j);
				}
			}
			else
			{
				if(j==0)
				{
					int c2=rand()%4;char e='A'+c2;
					int c3=rand()%4;char s='A'+c3;
					int c4=rand()%4;char o='A'+c4;
					bloc* b=creerBloc(getS(&p->l[i-1].rangee[j]),e,s,o);
					affectBloc(sf,b,i,j);
				}
				else
				{
					int c2=rand()%4;char e='A'+c2;
					int c3=rand()%4;char s='A'+c3;
					bloc* b=creerBloc(getS(&p->l[i-1].rangee[j]),e,s,getE(&p->l[i].rangee[j-1]));
					affectBloc(sf,b,i,j);
				}
			}
		}
	}








}

int main()
{
	bloc* b=creerBloc('A','D','C','C');
	printf("au nord %c au sud %c à l'est %c à l'ouest %c\n",getN(b),getS(b),getE(b),getO(b));
	bloc* c=creerBloc('A','D','C','C');
	plateau* p=(plateau*)malloc(sizeof(plateau));
	initPlateau(p,4);
	remplirPlateau(p);
	dessin(p);
	char* co="a4";
	printf("\n c'est la vérif du plateau %d\n",verifPlateau(p));
	rotaBloc(p,co);
	dessin(p);
	char* mess="a4d1";
	int ax=LireDX(p,mess);
	int ay=LireDY(p,mess);
	int bx=LireFX(p,mess);
	int by=LireFY(p,mess);
	swapBloc(p,ax,ay,bx,by);
	dessin(p);
	printf("au nord %c au sud %c à l'est %c à l'ouest %c\n",getN(&p->l[0].rangee[3]),getS(&p->l[0].rangee[3]),getE(&p->l[0].rangee[3]),getO(&p->l[0].rangee[3]));
	printf("au nord %c au sud %c à l'est %c à l'ouest %c\n",getN(&p->l[3].rangee[0]),getS(&p->l[3].rangee[0]),getE(&p->l[3].rangee[0]),getO(&p->l[3].rangee[0]));
	printf("\n c'est la vérif du plateau %d",verifPlateau(p));


	freeP(p);





}
