#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream in("graf.txt");
    int n,m;
    //Se citesc din fisier numerele n si m reprezentand numarul de varfuri respectiv numarul de muchii ale grafului
    in>>n>>m;
    int ma[n][m];
    int i,j;
    //Se citeste matricea de incidenta
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            in>>ma[i][j];

    int alpha[n+1],beta[m];
    alpha[0]=0;
    int grad;
    int k;

    //construim listele alpha si beta
    for(i=0;i<n;i++)
    {
        grad=0;
        for(j=0;j<m;j++)
            if(ma[i][j]==-1)
                {for(k=0;k<n;k++)
                    if(ma[k][j]==1)
                        beta[alpha[i]+grad]=k+1;
                grad++;}
        alpha[i+1]=alpha[i]+grad;
    }


    cout<<"Lista alpha: ";
    for(i=0;i<n+1;i++)
        cout<<alpha[i]<<" ";
    cout<<"\nLista beta : ";
    for(i=0;i<m;i++)
        cout<<beta[i]<<" ";

    return 0;
}
