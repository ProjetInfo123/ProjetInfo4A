#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	bloc a;
	bloc b;
	int cote;
}couple;

typedef struct
{
	int taille;
	ligne* l;
	couple* cpl;

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


void setC1(couple c,bloc a){
	c.a=a;
}

void setC2(couple c,bloc b){
	c.a=b;
}

void setCote(couple c,int x){
		c.cote=x;

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



bloc cloneBloc(plateau* p,int x,int y)
{
	bloc c;
	bloc* a=&(p->l[x].rangee[y]);
	char n=getN(a);
	char o=getO(a);
	char e=getE(a);
	char s=getS(a);
	c=*(creerBloc(n,e,s,o));
	return c;
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
					setC1(p,p->l[i].rangee[j]); setC2(p,p->l[i].rangee[j+1]);
					setCote(p->cplt[erreur],0);

				}
			}
				else
				{
					if(i==p->taille-1)
					{

						if(!(j==p->l->taille-1))
						{
							erreur+=verifBloc(&(p->l[i].rangee[j]),&(p->l[i].rangee[j+1]),0);
							setC1(p,p->l[i].rangee[j]); setC2(p,p->l[i].rangee[j+1]);
							setCote(p->cplt[erreur],0);
							erreur+=verifBloc(&(p->l[i].rangee[j]),&(p->l[i-1].rangee[j]),1);
							setC1(p,p->l[i].rangee[j]); setC2(p,p->l[i-1].rangee[j]);
							setCote(p->cplt[erreur],1);
						}
						else
						{
					erreur+=verifBloc(&(p->l[i].rangee[j]),&(p->l[i-1].rangee[j]),1);
					setC1(p,p->l[i].rangee[j]); setC2(p,p->l[i-1].rangee[j]);
					setCote(p->cplt[erreur],1);
						}
				}
			else
			{
			if(!(j==p->l->taille-1))
			{
erreur+=verifBloc(&(p->l[i].rangee[j]),&(p->l[i].rangee[j+1]),0);
setC1(p,p->l[i].rangee[j]); setC2(p,p->l[i].rangee[j+1]);
setCote(p->cplt[erreur],0);
erreur+=verifBloc(&(p->l[i].rangee[j]),&(p->l[i-1].rangee[j]),1);
setC1(p,p->l[i].rangee[j]); setC2(p,p->l[i-1].rangee[j]);
setCote(p->cplt[erreur],1);
}
else
{
erreur+=verifBloc(&(p->l[i].rangee[j]),&(p->l[i-1].rangee[j]),1);
p->cpl[erreur].setC1(p->l[i].rangee[j]); p->cpl[erreur].setC2(p->l[i-1].rangee[j])
p->cplt[erreur].setCote(1);
}
}

}
}
}
return erreur;
}

void affectBloc(ligne* r,bloc* b,int pos)
{
	r->rangee[pos]= *b;
}
void gener(plateau* p)
{
	for(int i=0;i<p->taille;i++)
	{
		for(int j=0;j<p->l->taille;j++)
		{
			if(j!=p->l->taille-1){
			bloc* b=creerBloc('B','B','B','B');
			affectBloc(&(p->l[i]),b,j);	}
			else{
				bloc* b=creerBloc('A','A','A','A');
			affectBloc(&(p->l[i]),b,j);	}


		}

	}
}

void cherchsub(plateau* p,couple c){



}

void ordi(plateau* p){
	int n = verifPlateau(p);








}





void dessin(plateau* p){
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
    {	printf("   ");
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
	p->cpl=(couple*)malloc((t*t*4)*sizeof(couple));
}




void freeL(ligne* l)
{
	free(l->rangee);
	free(l);
}

void swapBloc(plateau* p,int ax,int ay,int bx,int by)
{
	bloc a =p->l[ax].rangee[ay];
	bloc b = p->l[bx].rangee[by];

	p->l[ax].rangee[ay]=b;
	p->l[bx].rangee[by]=a;


}




int LireDX(plateau* p,char* e)
{

	int m;
	for(int i=0;i<p->taille;i++){
		if(e[0]=='a'+i){ m=i;}
	}

	return m;

}

int LireDY(plateau* p,char* e)
{
	int k;
	for(int i=0;i<p->taille;i++){
		if(e[1]==i+1) { k=i+1;}
	}
	return k;

}

int LireFX(plateau* p,char* e)
{

	int m;
	for(int i=0;i<p->taille;i++){
		if(e[2]=='a'+i){ m=i;}
	}

	return m;

}

int LireFY(plateau* p,char* e)
{
	int k;
	for(int i=0;i<p->taille;i++){
		if(e[3]==i+1) { k=i+1;}
	}
	return k;

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

int main()
{
	bloc* b=creerBloc('A','D','C','C');
	printf("au nord %c au sud %c à l'est %c à l'ouest %c\n",getN(b),getS(b),getE(b),getO(b));
	bloc* c=creerBloc('A','D','C','C');
	printf("alors %d\n",verifBloc(b,c));
	plateau* p=(plateau*)malloc(sizeof(plateau));
	initPlateau(p,4);
	gener(p);
	dessin(p);
	printf("bob");
	printf("\n");
	printf("\n");
	printf("\n");
	char* bb[5];
	scanf("%s", bb);
	printf("euh");
	printf("%s",bb);
	printf("\n");
	int ax=LireDX(p,bb);
	int ay=LireDY(p,bb);
	int bx=LireFX(p,bb);
	int by=LireFY(p,bb);
	swapBloc(p,ax,ay,bx,by);
	//rotaBloc(dd);
	dessin(p);



	freeB(b);
	freeB(c);





}
