#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
	char nord,est,ouest,sud;
	int* cote; //NESW
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
		b->cote=(int*)calloc(4,sizeof(int));
		return b;
}





void freeB(bloc* b)
{
	free(b->cote);
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


int equalsBloc(plateau* p,bloc a,int bx,int by,int i)
{
	bloc b=p->l[bx].rangee[by];
	switch (i)
	{
	 	case 0:{ return getN(a)==getN(b);break; }
		case 1:{ return getE(a)==getE(b);break; }
		case 2:{ return getS(a)==getS(b);break; }
		case 3:{ return getO(a)==getO(b);break; }
		default :{printf("error");}
	 }
}

int verifBloc(bloc* a,bloc* b,int cote)
{
	int erreur=0;
	if (cote==3)
	{
		if((getS(a)!=getN(b)))
			{
				erreur++;
			}

	}
	if (cote==2)
	{
		if((getO(a)!=getE(b)))
			{
				erreur++;
			}

	}
	if(cote==1)
	{
		if((getN(a)!=getS(b)))
			{
				erreur++;
			}
	}
	if(cote==0)
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

int verifRound(plateau* p,int x,int y)
{
	bloc b =p->l[x].rangee[y];
	int erreur;
	if(x==1)
	{
		if(y==1)
		{
			erreur+=verifBloc(&b,p->l[x].rangee[y+1],0);
			if(verifBloc(&b,p->l[x].rangee[y+1],1)==1)
			{
					b.cote[1]=1;
					p->l[x].rangee[y+1].cote[3]=1;
			}
			erreur+=verifBloc(&b,p->l[x-1].rangee[y],3);
			if(verifBloc(&b,p->l[x-1].rangee[y],1)==1)
			{
					b.cote[2]=1;
					p->l[x-1].rangee[y].cote[0]=1;
			}
				return erreur;
		}
		else
		{
			if(y==p->taille)
			{
				erreur+=verifBloc(&b,l[x].rangee[y-1],2);
				if(verifBloc(&b,p->l[x].rangee[y-1],1)==1)
				{
						b.cote[3]=1;
						p->l[x].rangee[y-1].cote[1]=1;
				}
				erreur+=verifBloc(&b,l[x-1].rangee[y],3);
				if(verifBloc(&b,p->l[x-1].rangee[y],3)==1)
				{
						b.cote[2]=1;
						p->l[x-1].rangee[y].cote[0]=1
				}
				return erreur;

			}
			else
			{
				erreur+=verifBloc(&b,l[x-1].rangee[y],3);
				if(verifBloc(&b,p->l[x-1].rangee[y],1)==1)
				{
						b.cote[2]=1;
						p->l[x-1].rangee[y].cote[0]=1
				}
				erreur+=verifBloc(&b,l[x].rangee[y+1],0);
				if(verifBloc(&b,p->l[x].rangee[y+1],1)==1)
				{
						b.cote[1]=1;
						p->l[x].rangee[y+1].cote[3]=1
				}

				erreur+=verifBloc(&b,l[x].rangee[y-1],2);
				if(verifBloc(&b,p->l[x].rangee[y-1],1)==1)
				{
						b.cote[3]=1;
						p->l[x].rangee[y-1].cote[1]=1
				}
				return erreur;
			}

		}
	}
	else
	{
		if(x==p->taille)
		{
			if(y==1)
			{
					erreur+=verifBloc(&b,l[x].rangee[y+1],0);
					if(verifBloc(&b,p->l[x].rangee[y+1],1)==1)
					{
							b.cote[1]=1;
							p->l[x].rangee[y+1].cote[3]=1
					}
					erreur+=verifBloc(&b,l[x+1].rangee[y],1);
					if(verifBloc(&b,p->l[x+1].rangee[y],1)==1)
					{
							b.cote[0]=1;
							p->l[x+1].rangee[y].cote[2]=1
					}
					return erreur;
			}
			else
			{
				if(y==p->taille)
				{
					erreur+=verifBloc(&b,l[x].rangee[y-1],2);
					if(verifBloc(&b,p->l[x].rangee[y-1],1)==1)
					{
							b.cote[3]=1;
							p->l[x].rangee[y-1].cote[1]=1
					}
					erreur+=verifBloc(&b,l[x-1].rangee[y],3);
					if(verifBloc(&b,p->l[x-1].rangee[y],1)==1)
					{
							b.cote[2]=1;
							p->l[x-1].rangee[y].cote[0]=1
					}
					return erreur;

				}
				else
				{
					erreur+=verifBloc(&b,l[x-1].rangee[y],3);
					if(verifBloc(&b,p->l[x-1].rangee[y],1)==1)
					{
							b.cote[2]=1;
							p->l[x-1].rangee[y].cote[0]=1
					}
					erreur+=verifBloc(&b,l[x+1].rangee[y],1);
					if(verifBloc(&b,p->l[x+1].rangee[y],1)==1)
					{
							b.cote[0]=1;
							p->l[x+1].rangee[y].cote[2]=1
					}
					erreur+=verifBloc(&b,l[x].rangee[y-1],2);
					if(verifBloc(&b,p->l[x].rangee[y-1],1)==1)
					{
							b.cote[3]=1;
							p->l[x].rangee[y-1].cote[1]=1
					}
					return erreur;
				}
		}
	}
		else

		{
			erreur+=verifBloc(&b,l[x].rangee[y+1],0);
			if(verifBloc(&b,p->l[x].rangee[y+1],1)==1)
			{
					b.cote[1]=1;
					p->l[x+1].rangee[y].cote[3]=1
			}
			erreur+=verifBloc(&b,l[x-1].rangee[y],3);
			if(verifBloc(&b,p->l[x-1].rangee[y],1)==1)
			{
					b.cote[2]=1;
					p->l[x-1].rangee[y].cote[0]=1
			}
			erreur+=verifBloc(&b,l[x+1].rangee[y],1);
			if(verifBloc(&b,p->l[x+1].rangee[y],1)==1)
			{
					b.cote[0]=1;
					p->l[x+1].rangee[y].cote[2]=1
			}
			erreur+=verifBloc(&b,l[x].rangee[y-1],2);
			if(verifBloc(&b,p->l[x].rangee[y-1],1)==1)
			{
					b.cote[3]=1;
					p->l[x].rangee[y-1].cote[1]=1
			}
			return erreur;

		}

	}

	}

}


void cherchsub(plateau* p,int ax,int ay,int bx,int by,int s){   //tu dois récuperer le coté problématique entre a et b et avec verifRound et trouver un bloc qui peut se mettre pour réparer ce problème
	bloc top;
	bloc a=p->l[ax].rangee[ay];
	int n=1;
	int q=0;
	int r=0;
	for(int i=0;i<p->taille;i++)
	{
		for(int j=0;j<p->taille;j++)
		{
				if(n>=verifBloc(a,p->l[i].rangee[j],s))
				{
					n=verifBloc(a,p->l[i].rangee[j],s);
					top=p->l[i].rangee[j];
					if(n=0){
						q=verifRound(p,bx,by);
						for(int k=0;k<4;k++)
						{
							r=equalsBloc(p,a,bx,by,k) //comparer les NESW de top et de b pour voir le nombre d'erreur qu'il y aurait si on les swap, garder le nombre d'erreur mn
						}
					}

				}
		}
	}
	swapBloc(b,top);


}

void ordi(plateau* p){
	int n = verifPlateau(p);







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
	free(p->l);
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
	plateau* sf=(plateau*)malloc(sizeof(plateau));
	initPlateau(sf,p->taille);
	srand ( time(NULL) );
	for(int i=0;i<sf->taille;i++)
	{
		for(int j=0;j<sf->l->taille;j++)
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
					bloc* b=creerBloc(n,e,s,getE(&sf->l[i].rangee[j-1]));
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
					bloc* b=creerBloc(getS(&sf->l[i-1].rangee[j]),e,s,o);
					affectBloc(sf,b,i,j);
				}
				else
				{
					int c2=rand()%4;char e='A'+c2;
					int c3=rand()%4;char s='A'+c3;
					bloc* b=creerBloc(getS(&sf->l[i-1].rangee[j]),e,s,getE(&sf->l[i].rangee[j-1]));
					affectBloc(sf,b,i,j);
				}
			}
		}
	}

	dessin(sf);

	for(int i=0;i<sf->taille;i++)
	{
		for(int j=0;j<sf->l->taille;j++)
		{
			int rota=1+rand()%4;
			char m[3];
			m[0]='a'+i;
			m[1]='1'+j;
			m[2]='\0';
			for(int k=0;k<rota;k++)
			{
				rotaBloc(sf,m);
			}
		}
	}

	dessin(sf);

	//répartir aléatoirement dans plateau
	/*compteur de cases NULL
	tant que(compteur inf strict à nb bloc et bloc est null) :
		prendre bloc
		appliquer bloc dans p
		bloc dans sf devient null
		fin tant que*/

}

int main()
{
	plateau* p=(plateau*)malloc(sizeof(plateau));
	initPlateau(p,4);
	remplirPlateau(p);
	freeP(p);
}
