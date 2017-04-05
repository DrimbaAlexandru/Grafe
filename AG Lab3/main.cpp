#include <stdlib.h>
#include <iostream>
#include <fstream>
#define INFINIT -10000
using namespace std;

int** get_graf(char filename[], int &n, int &m)
{
    ifstream in(filename);
    in>>n>>m;
    int** gf=(int**)malloc(n*sizeof(int));
    int i;
    for(i=0;i<n;i++)
        gf[i]=(int*)malloc(n*sizeof(int));
    int vf1,vf2,val;
    int j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(i==j)
                gf[i][j]=0;
            else
                gf[i][j]=INFINIT;
    for(i=0;i<m;i++)
        {in>>vf1>>vf2>>val;
        gf[vf1-1][vf2-1]=val;
        }
    return gf;
}

void distruge_graf(int n, int** graf)
{
    int i;
    for(i=0;i<n;i++)
        free(graf[i]);
    free(graf);
}

void afisare_graf(int** gf, int n)
{
    int i,j;
    for(i=0;i<n;i++)
        {for(j=0;j<n;j++)
            cout<<gf[i][j]<<"  ";
        cout<<endl;}
    cout<<endl;
    cout<<endl;
}

void adauga_in_sir(int valoare, int &n, int a[])
{
    int i;
    for(i=0;i<n;i++)
        if(a[i]==valoare)
            return;
    n++;
    a[n-1]=valoare;
}

void elimina_din_sir(int valoare, int &n, int a[])
{
    int i,gasit=0;
    for(i=0;i<n;i++)
    {
        if(!gasit)
            if(a[i]==valoare)
                {gasit=1;
                n--;}
        if(gasit)
            a[i]=a[i+1];
    }
}

int get_gamma_plus(int** gf, int varf, int n, int gamma[])
{
    int i;
    int m=0;
    for(i=0;i<n;i++)
        if((gf[varf][i]!=INFINIT)&&(i!=varf))
            {gamma[m]=i;
            m++;}
    return m;
}

int main()
{
    int n,m;
    int** G=get_graf("graf.txt",n,m);
    int maxim;  if(n>m)maxim=n;
                else maxim=m;

    //afisare_graf(G,n);
    int i,j,k=0;
    int l[n];

    for(i=0;i<n;i++)
        l[i]=G[0][i];

    ///Multimea S de la Moore-Dijkstra
    int s[n];
    int ls=n;
    for(i=0;i<ls;i++)
        s[i]=i;

    ///Multimea gamma
    int gamma[n];
    int lg;

    while((ls!=0)&&(k<=maxim))
    {
        j=0;
        for(i=0;i<ls;i++)
            if(l[s[i]]>l[s[j]])
                j=i;

        j=s[j];
        k++;
        elimina_din_sir(j,ls,s);

        lg=get_gamma_plus(G,j,n,gamma);
        for(i=0;i<lg;i++)
            if(l[j]+G[j][gamma[i]]>l[gamma[i]])
            {
                l[gamma[i]]=l[j]+G[j][gamma[i]];
                adauga_in_sir(gamma[i],ls,s);
            }
    }

    /*cout<<"Timpurile cele mai devreme: ";
    for(i=1;i<n;i++)
        cout<<l[i]<<" ";
    cout<<endl;*/


    int minim;
    for(i=n-2;i>0;i--)
    {
        lg=get_gamma_plus(G,i,n,gamma);
        minim=l[gamma[0]];
        for(j=1;j<lg;j++)
            if(l[gamma[j]]<minim)
                {minim=l[gamma[j]];}
        l[i]=minim-G[i][gamma[0]];
    }


    cout<<"Timpurile cele mai tarzii: ";
    for(i=1;i<n;i++)
        cout<<l[i]<<" ";

    ///-----------------------------------------------------------
    distruge_graf(n,G);


    return 0;
}
