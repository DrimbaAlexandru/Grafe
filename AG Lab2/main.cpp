#include <stdlib.h>
#include <iostream>
#include <fstream>
#define INFINIT -1000000
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

void permutare_varf(int** gf,int n,int varf)
{
    int i,j;
    int* aux;
    for(j=0;j<varf-1;j++)
        for(i=0;i<n-1;i++)
        {
            aux=gf[i];
            gf[i]=gf[(i+1)%n];
            gf[(i+1)%n]=aux;
        }

    int aux2,k;
    for(k=0;k<varf-1;k++)
        for(i=0;i<n;i++)
            for(j=0;j<n-1;j++)
            {
                aux2=gf[i][j];
                gf[i][j]=gf[i][(j+1)%n];
                gf[i][(j+1)%n]=aux2;
            }
}
void afisare_graf(int** gf, int n)
{
    int i,j;
    for(i=0;i<n;i++)
        {for(j=0;j<n;j++)
            cout<<gf[i][j]<<"   ";
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
    int p,q;
    int maxim;
    if(n<m)
        maxim=n;
    else maxim=m;
    cout<<"Varful din care porneste drumul: ";cin>>p;
    cout<<"Varful terminal al drumului: ";cin>>q;
    //afisare_graf(G,n);
    permutare_varf(G,n,p);
    //afisare_graf(G,n);
    int i,j,k=0;
    int l[n];
    int lungime[n];
    int prec[n];
    for(i=0;i<n;i++)
        {l[i]=G[0][i];
        lungime[i]=G[0][i];
        if((l[i]!=INFINIT)&&(i!=0))
            lungime[i]=1;
        prec[i]=0;
        if((G[0][i]!=INFINIT)&&(i!=0))
            prec[i]=1;
        }

    int s[n];
    int ls=n;
    for(i=0;i<ls;i++)
        s[i]=i;

    int gamma[n];
    int lg;

    while((ls!=0)&&(k<=maxim))
    {
        j=0;
        for(i=0;i<ls;i++)
        {
            if(l[s[i]]>l[s[j]])
                j=i;
        }

        j=s[j];
        k++;
        elimina_din_sir(j,ls,s);

        lg=get_gamma_plus(G,j,n,gamma);
        for(i=0;i<lg;i++)
        {
            if(l[j]+G[j][gamma[i]]>l[gamma[i]])
            {
                prec[gamma[i]]=j+1;
                l[gamma[i]]=l[j]+G[j][gamma[i]];
                lungime[gamma[i]]=lungime[j]+1;
                adauga_in_sir(gamma[i],ls,s);

            }
        }
    }

    int drum[n];

    k=lungime[(q+n-p)%n];
    if(k==INFINIT)
        {cout<<"NU EXISTA DRUM";
        return 0;}
    int cost_min=l[(q+n-p)%n];
    cout<<"Cost minim:"<<cost_min<<endl;

    q=(q-p+1+n)%n;
    if(q==0)
        q=n;
    int vf=q-1;

    for(i=0;i<k;i++)
    {
        drum[k-i]=vf;
        vf=prec[vf]-1;
    }

    drum[0]=0;
    for(i=0;i<=k;i++)
    {
        vf=(drum[i]+p-1+n)%n+1;
        if(i!=k)
            cout<<vf<<"->";
        else
            cout<<vf;
    }

    distruge_graf(n,G);
    return 0;
}
