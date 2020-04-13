#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
* Projet Info4A variante J 2020
* Auteur : Thomas Eguienta & Azeddine Assaghir
*/


typedef struct //structure qui représente un bloc avec ses 4 cotés et un tableau qui représente les erreurs qu'il a avec les blocs autour de lui
{
	char nord,est,ouest,sud;
	int cote[4]; //NESO
}bloc;


typedef struct //structure qui représente une ligne qui est composé de blocs
{
	int taille;
	bloc** rangee;
}ligne;


typedef struct //structure qui représente le plateau qui est composé de plusieurs lignes
{
	int taille;
	ligne** l;
}plateau;

bloc* creerBloc(char n,char e,char s,char o) //méthode pour créer un bloc en spécifiant les lettres
{
		bloc* b=(bloc*)malloc(sizeof(bloc));
		b->nord=n;
		b->est=e;
		b->ouest=o;
		b->sud=s;

		return b;
}


//accesseur des coordonnés du blocs
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

int verifBloc(bloc* a,bloc* b,int cote) //verifie s'il y une erreur entre les deux blocs donnés en paramètre en fonction du coté donné, renvoie 1 s'il y a une erreur et 0 sinon
{
	int erreur=0;
	if (cote==2)
	{
		if((getS(a)!=getN(b)))
			{
				erreur++;
			}

	}
	if (cote==3)
	{
		if((getO(a)!=getE(b)))
			{
				erreur++;
			}

	}
	if(cote==0)
	{
		if((getN(a)!=getS(b)))
			{
				erreur++;
			}
	}
	if(cote==1)
	{
		if((getE(a)!=getO(b)))
		{
		erreur++;
		}
	}

	return erreur;
}

int verifPlateau(plateau* p) //méthode qui renvoie le nombre d'erreur total dans le plateau
{
	int erreur=0;
	for(int i=0;i<p->taille;i++)
	{
		for(int j=0;j<p->taille;j++)
		{
			if(i==0)
			{
				erreur+=verifBloc(p->l[i]->rangee[j],p->l[p->taille-1]->rangee[j],0);
				if(!(j==p->taille-1))
				{
					erreur+=verifBloc(p->l[i]->rangee[j],p->l[i]->rangee[j+1],1);
				}
				else
				{
					erreur+=verifBloc(p->l[i]->rangee[j],p->l[i]->rangee[0],1);
				}
			}
			else
			{
				if(!(j==p->taille-1))
				{
					erreur+=verifBloc(p->l[i]->rangee[j],p->l[i]->rangee[j+1],1);
					erreur+=verifBloc(p->l[i]->rangee[j],p->l[i-1]->rangee[j],0);
				}
				else
				{
					erreur+=verifBloc(p->l[i]->rangee[j],p->l[i-1]->rangee[j],0);
					erreur+=verifBloc(p->l[i]->rangee[j],p->l[i]->rangee[0],1);
				}
			}
		}
	}
	if(erreur==0)
  {
		printf("Solution trouvée\n");
	}

	return erreur;
}

void affectBloc(plateau* p,bloc* b,int x,int y) //méthode qui affecte au bloc en position x,y du plateau les valeurs du bloc b
{
	p->l[x]->rangee[y]=b;
}


int verifRound(plateau* p,int x,int y)//renvoie le nombre d'erreurs que le bloc en x,y a avec les blocs autour de lui (max 4) et remplit le tableau cote du bloc qui correspond aux erreurs éventuelles
{
	bloc* b=p->l[x]->rangee[y];
	int erreur=0;


	if(y==0)
	{
		if(verifBloc(b,p->l[x]->rangee[p->taille-1],3))
		{
			erreur++;
			b->cote[3]=1;
		}
		else
		{
			b->cote[3]=0;
		}
		if(verifBloc(b,p->l[x]->rangee[y+1],1))
		{
			erreur++;
			b->cote[1]=1;
		}
		else
		{
			b->cote[1]=0;
		}
	 }
	if(y==p->taille-1)
	{
		if(verifBloc(b,p->l[x]->rangee[0],1))
		{
			erreur++;
			b->cote[1]=1;
		}
		else
		{
			b->cote[1]=0;
		}
		if(verifBloc(b,p->l[x]->rangee[y-1],1))
		{
			erreur++;
			b->cote[3]=1;
		}
		else
		{
			b->cote[3]=0;
		}
	}
	if(y!=0 && y!=p->taille-1)
	{
		if(verifBloc(b,p->l[x]->rangee[y+1],0))
		{
			erreur++;
			b->cote[0]=1;
		}
		else
		{
			b->cote[0]=0;
		}
		if(verifBloc(b,p->l[x]->rangee[y-1],3))
		{
			erreur++;
			b->cote[3]=1;
		}
		else
		{
			b->cote[3]=0;
		}
	}

	if(x==0)
	{
		if(verifBloc(b,p->l[p->taille-1]->rangee[y],0))
		{
			erreur++;
			b->cote[0]=1;
		}
		else
		{
			b->cote[0]=0;
		}
		if(verifBloc(b,p->l[x+1]->rangee[y],2))
		{
			erreur++;
			b->cote[2]=1;
		}
		else
		{
			b->cote[2]=0;
		}
	 }
 	if(x==p->taille-1)
	{
		if(verifBloc(b,p->l[x-1]->rangee[y],0))
	 	{
	 		erreur++;
	 		b->cote[0]=1;
		}
	 	else
	 	{
	 		b->cote[0]=0;
	 	}
	 	if(verifBloc(b,p->l[0]->rangee[y],2))
	 	{
	 		erreur++;
	 		b->cote[2]=1;
	 	}
	 	else
	 	{
	 		b->cote[2]=0;
	 	}
	}
 	if(x!=0 && x!=p->taille-1)
	{
		if(verifBloc(b,p->l[x-1]->rangee[y],0))
	 	{
	 		erreur++;
	 		b->cote[0]=1;
	 	}
	 	else
	 	{
	 		b->cote[0]=0;
	 	}
	 	if(verifBloc(b,p->l[x+1]->rangee[y],2))
	 	{
	 		erreur++;
	 		b->cote[2]=1;
	 	}
	 	else
	 	{
	 		b->cote[2]=0;
	 	}
	}

	return erreur;

}

void swapBloc(plateau* p,int ax,int ay,int bx,int by)//méthode qui permet d'échanger la position de deux blocs
	{
		bloc* a =p->l[ax]->rangee[ay];
		bloc* b = p->l[bx]->rangee[by];
		bloc* temp=a;

		p->l[ax]->rangee[ay]=b;
		p->l[bx]->rangee[by]=temp;
	}



void cherchsub(plateau* p,int ax,int ay) //méthode qui permet à l'IA de trouver un bloc qui n'a pas de problème le bloc dont ses coordonnées sont en paramètre
{
	bloc* a=p->l[ax]->rangee[ay];
	int bx;
	int by;
		for(int m=0;m<4;m++)
		{
			int e=a->cote[m]; //NESW
			int pb;
			if(e)
			{
				switch(m)
				{
					case 0:
					{
            if(ax==0)
            {
              bx=p->taille-1;
            }
            else
            {
              bx=ax-1;
            }
            by=ay;
						pb=0;
						break;
					}
					case 1:
					{
						if(ay==p->taille-1)
            {
              by=0;
            }
            else
            {
              by=ay+1;
            }
            bx=ax;
						pb=1;
						break;
					}
					case 2:
					{
						if(ax==p->taille-1)
            {
              bx=0;
            }
            else
            {
						  bx=ax+1;
            }
            by=ay;
						pb=2;
						break;
					}
					case 3:
					{
						if(ay==0)
            {
              by=p->taille-1;
            }
            else
            {
						  by=ay-1;
            }
            bx=ax;
						pb=3;
						break;
					}
				}

	for(int i=0;i<p->taille;i++)
	{
		for(int j=0;j<p->taille;j++)
		{
			 int z=verifBloc(a,p->l[i]->rangee[j],pb);
			 if(z==0)
			 {
				 int av=verifPlateau(p);
				 swapBloc(p,bx,by,i,j);
				 int ap=verifPlateau(p);
				 if(av<ap)
				 {
					 swapBloc(p,bx,by,i,j);
				 }
			 	}
			}
		}
	}
}


}







void dessin(plateau* p) //méthode qui dessine le plateau à l'écran et le nombre d'erreur présente dans le plateau
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
            char n=getN(p->l[k]->rangee[i]);
            printf("  %c  ",n);
        }
        printf("\n");
        char q='a'+k;
        printf("%c  ",q);
        for(int i=0;i<r;i++)
        {
            char o=getO(p->l[k]->rangee[i]);
            char e=getE(p->l[k]->rangee[i]);
            printf("%c # %c",o,e);
        }
        printf("\n");
        printf("   ");
        for(int i=0;i<r;i++)
        {
            char s=getS(p->l[k]->rangee[i]);
            printf("  %c  ",s);
        }
        printf("\n");
    }
		printf("\n");
		printf("\n");
		int x=verifPlateau(p);
		printf("Il y a %d fautes\n",x);

}

void initLigne(ligne* l,int t) //méthode qui initialise une structure de type ligne
{
  l->taille=t;
	l->rangee=(bloc**)malloc(t*sizeof(bloc*));
  for(int i=0;i<t;i++)
  {
    l->rangee[i]=(bloc*)malloc(sizeof(bloc));
  }
}

void initPlateau(plateau* p, int t) //méthode qui initialise une structure de type plateau
{
	p->l=(ligne**)malloc(t*sizeof(ligne*));
	p->taille=t;
	for(int i=0;i<t;i++)
	{
    p->l[i]=(ligne*)malloc(sizeof(ligne));
		initLigne(p->l[i],t);
	}
}

void freeB(bloc* b) //méthode qui permet de libérer en mémoire une structure de type bloc
{
	free(b);
}

void freeL(ligne* l) //méthode qui permet de libérer en mémoire une structure de type ligne
{
	for(int i=0;i<l->taille;i++)
	{
		freeB(l->rangee[i]);
	}
	free(l);
}

void freeP(plateau* p) //méthode qui permet de libérer en mémoire une structure de type plateau
{
	for(int i=0;i<p->taille;i++)
	{
		freeL(p->l[i]);
	}
	free(p);
}


// 4 méthodes qui permettent de récuperer les coordonnées que l'utilisateur peut entrer avec par exemple b2c4
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


void rotaBloc(plateau* p,char* c) //méthode qui permet de faire pivoter un bloc d'un quart de tour vers la droite à partir de sa position entrée par l'utilisateur comme b2
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

	bloc* b=p->l[l]->rangee[k];
	char n=getN(b);
	char e=getE(b);
	char s=getS(b);
	char o=getO(b);
	bloc* b2=creerBloc(o,n,e,s);
	affectBloc(p,b2,l,k);
}

void remplirPlateau(plateau* p) //méthode qui va créer une solution fixe puis répartir de manière aléatoire les blocs de cette solution
{

	//dans un premier temps, on créé la solution fixe avec le code ci-dessous
	plateau* sf=(plateau*)malloc(sizeof(plateau));
	initPlateau(sf,p->taille);
	srand ( time(NULL) );
	for(int i=0;i<sf->taille;i++)
	{
		for(int j=0;j<sf->taille;j++)
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
					if(j==sf->taille-1)
					{
						int c1=rand()%4;char n='A'+c1;
						int c3=rand()%4;char s='A'+c3;
						bloc* b=creerBloc(n,getO(sf->l[i]->rangee[0]),s,getE(sf->l[i]->rangee[j-1]));
						affectBloc(sf,b,i,j);
					}
					else
					{
						int c1=rand()%4;char n='A'+c1;
						int c2=rand()%4;char e='A'+c2;
						int c3=rand()%4;char s='A'+c3;
						bloc* b=creerBloc(n,e,s,getE(sf->l[i]->rangee[j-1]));
						affectBloc(sf,b,i,j);
					}
				}
			}
			else
			{
				if(i==sf->taille-1)
				{
					if(j==0)
					{
						int c2=rand()%4;char e='A'+c2;
						int c4=rand()%4;char o='A'+c4;
						bloc* b=creerBloc(getS(sf->l[i-1]->rangee[j]),e,getN(sf->l[0]->rangee[j]),o);
						affectBloc(sf,b,i,j);
					}
					else
					{
						if(j==sf->taille-1)
						{
							bloc* b=creerBloc(getS(sf->l[i-1]->rangee[j]),getO(sf->l[i]->rangee[0]),getN(sf->l[0]->rangee[j]),getE(sf->l[i]->rangee[j-1]));
							affectBloc(sf,b,i,j);
						}
						else
						{
							int c2=rand()%4;char e='A'+c2;
							bloc* b=creerBloc(getS(sf->l[i-1]->rangee[j]),e,getN(sf->l[0]->rangee[j]),getE(sf->l[i]->rangee[j-1]));
							affectBloc(sf,b,i,j);
						}
					}
				}
				else
				{
					if(j==0)
					{
						int c2=rand()%4;char e='A'+c2;
						int c3=rand()%4;char s='A'+c3;
						int c4=rand()%4;char o='A'+c4;
						bloc* b=creerBloc(getS(sf->l[i-1]->rangee[j]),e,s,o);
						affectBloc(sf,b,i,j);
					}
					else
					{
						if(j==sf->taille-1)
						{
							int c3=rand()%4;char s='A'+c3;
							bloc* b=creerBloc(getS(sf->l[i-1]->rangee[j]),getO(sf->l[i]->rangee[0]),s,getE(sf->l[i]->rangee[j-1]));
							affectBloc(sf,b,i,j);
						}
						else
						{
							int c2=rand()%4;char e='A'+c2;
							int c3=rand()%4;char s='A'+c3;
							bloc* b=creerBloc(getS(sf->l[i-1]->rangee[j]),e,s,getE(sf->l[i]->rangee[j-1]));
							affectBloc(sf,b,i,j);
						}
					}
				}
			}
		}
	}



	//ensuite, les blocs sont pivotés avec un nombre aléatoire de quart de tour
	for(int i=0;i<sf->taille;i++)
	{
		for(int j=0;j<sf->taille;j++)
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

	//enfin, les blocs pivotés sont placés à une position aléatoire dans la plateau en cours
	int k,l;
	int** tab;
	tab=(int**)malloc(p->taille*sizeof(int*));
	for(int i=0;i<p->taille;i++)
	{
		tab[i]=(int*)calloc(p->taille,sizeof(int));
	}
	for(int i=0;i<p->taille;i++)
	{
		for(int j=0;j<p->taille;j++)
		{
			do
			{
				k=rand()%sf->taille;
				l=rand()%sf->taille;
			}while(tab[k][l]);
			p->l[i]->rangee[j]=sf->l[k]->rangee[l];
			tab[k][l]=1;
		}
	}

}


void ordi(plateau* p) //méthode qui permet la résolution du puzzle par l'IA
{
	//dans cette partie du code, la fonction va appeler la méthode "cherchsub" pour chaque bloc du plateau
	while(verifPlateau(p)!=0)
	{
		int n;
		int m;
		do{
			dessin(p);
			n= verifPlateau(p);
			for(int i=0;i<p->taille;i++)
			{
				for(int j=0;j<p->taille;j++)
				{
					cherchsub(p,i,j);
				}
			}
			m=verifPlateau(p);
		}while(n!=m);

		//ici, on lance une procédure de rotation des blocs si le code au-dessus ne change pas les erreurs présentes dans le plateau
		for(int i=0;i<p->taille;i++)
		{
			for(int j=0;j<p->taille;j++)
			{
				for(int k=0;k<4;k++)
				{
					int n = verifPlateau(p);
					char c[3];
		      c[0]='a'+i;
			    c[1]='1'+j;
		      c[2]='\0';
					rotaBloc(p,c);
					int m = verifPlateau(p);
					if(n<m)
					{
						for(int l=0;l<4-k;l++)
						{
							rotaBloc(p,c);
						}
					}
				}
			}
		}
		dessin(p);
	}
}


void joueur(plateau* p)// méthode qui permet de gérer une partie pour un utilisateur et appliquer les choix faits par celui-ci
{
	int nbechange=0;
	while(verifPlateau(p)!=0)
	{
		nbechange++;
		dessin(p);
		printf("Taper 1 pour échanger deux blocs ou 2 pour faire tourner en bloc : ");
		int q;
    int r=p->taille-1;
		scanf("%d",&q);
		printf("\n");
		if(q==1)
		{
			printf("Donner les deux blocs à échanger :");
			char s[4];
			scanf("%s",s);
			printf("\n");
		  if(strlen(s)==4 && s[0]>='a' && s[0]<='a'+r && s[2]>='a' && s[2]<='a'+r && s[1]>='1' && s[1]<='1'+r && s[3]>='1' && s[3]<='1'+r )
		{
				int s1,s2,s3,s4;
				s1=LireDX(p,s);
				s2=LireDY(p,s);
				s3=LireFX(p,s);
				s4=LireFY(p,s);
				swapBloc(p,s1,s2,s3,s4);
			}
			else{
				printf("erreur\n");
			}

		}
		else
		{
			if(q==2)
			{
				printf("Donner le bloc à pivoter :");
				char s[2];
				scanf("%s",s);
				printf("\n");
				int x;
				printf("Donner le nombre de quarts de tour a faire :");
				scanf("%d",&x);
				printf("\n");
				if(strlen(s)==2 && s[0]>='a' && s[0]<='a'+r && s[1]>='1' && s[1]<='1'+r)
				{
					for(int i=0;i<x;i++)
					{
						rotaBloc(p,s);
					}
				}
				if(q!=1 && q!=2)
				{
					printf(" erreur \n");
				}
			}
			else
			{
				printf("Vous n'avez pas écrit 1 ou 2\n");
			}

		}
	}
	dessin(p);
	printf("La partie a été résolue en %d échanges\n",nbechange);
}





int main()
{
	plateau* p=(plateau*)malloc(sizeof(plateau));
	printf(" Donner la dimension du plateau entre 4 et 7 :\n" );
	int z,x;
	scanf("%d",&z);
	printf("\n");
	if(z>=4 && z<=7){
	printf("\n");
	initPlateau(p,z);
	remplirPlateau(p);



	printf("Taper 1 pour joueur, 2 pour IA \n");
	scanf("%d",&x);
	printf("\n");
	if(x==1){
		joueur(p);
		printf("Partie terminée\n");
	}
	if(x==2)
		{
			ordi(p);
		}
	if(x!=1 || x!=2)
	{
		printf("erreur\n");
	}
}
else{
	printf("Dimension incorrecte\n");
}


	freeP(p);



	return 0;
}
