#include <stdlib.h>
#include <iostream>
#include <fstream>
#define INFINIT -10000
using namespace std;

class arc
{
private:
    int i,j;

public:
    arc()
    {
        i=-1;
        j=-1;
    }
    arc(int i,int j)
    {
        this->i=i;
        this->j=j;
    }

    int get_i()
    {
        return i;
    }

    int get_j()
    {
        return j;
    }

    arc operator=(arc other)
    {
        i=other.i;
        j=other.j;
        return *this;
    }

    int operator==(arc other)
    {
        return((i==other.i)&&(j==other.j));
    }

};

template <typename elem>
class multime
{
private:
    elem v[100];
    int n;

public:
    multime()
    {
        n=0;
    }

    void goleste()
    {
        n=0;
    }
    void reuneste(multime other)
    {
        int n=other.get_size();
        int i;
        for(i=0;i<n;i++)
            this->add(other[i]);
    }
    multime operator=(multime other)
    {
        int i;
        for(i=0;i<other.get_size();i++)
            v[i]=other.v[i];
        n=other.get_size();
        return *this;
    }
    void add(elem e)
    {
        int i;
        for(i=0;i<n;i++)
            if(v[i]==e)
                return;
        v[n]=e;
        n++;
    }

    void rem(elem e)
    {
        int i,gasit=0;
        for(i=0;i<n;i++)
        {
            if(v[i]==e)
            {
                if(!gasit)
                    n--;
                gasit=1;
            }
            if(gasit)
                v[i]=v[i+1];
        }
    }
    elem operator[](int poz)
    {
        return v[poz];
    }

    elem* get_all()
    {
        return v;
    }

    int get_size()
    {
        return n;
    }

};

class graf
{
private:
    multime<int> X;
    multime<arc> U;

public:
    graf()
    {;
    }

    multime<int> get_X()
    {
        return X;
    }

    multime<arc> get_U()
    {
        return U;
    }

    multime<int> get_gamma_minus(int varf)
    {
        multime<int> gm;
        int i,m=U.get_size();
        for(i=0;i<m;i++)
        {
            if(U[i].get_j()==varf)
                gm.add(U[i].get_i());
        }
        return gm;
    }

    multime<int> get_gamma_plus(int varf)
    {
        multime<int> gm;
        int i,m=U.get_size();
        for(i=0;i<m;i++)
        {
            if(U[i].get_i()==varf)
                gm.add(U[i].get_j());
        }
        return gm;
    }

    void adauga_varf(int v)
    {
        X.add(v);
    }

    void adauga_arc(int i,int j)
    {
        U.add(arc(i,j));
    }

    void elimina_varf(int v)
    {
        int i;
        for(i=0;i<U.get_size();i++)
        {
            if((U[i].get_i()==v)||(U[i].get_j()==v))
            {
                U.rem(arc(U[i].get_i(),U[i].get_j()));
                i--;
            }
        }
        X.rem(v);
    }

    void elimina_arc(int i, int j)
    {
        U.rem(arc(i,j));
    }

    void afiseaza()
    {
        int n=X.get_size();
        int m=U.get_size();
        int i;
        int* varfuri=X.get_all();
        arc* arce=U.get_all();
        cout<<"X={";
        for(i=0;i<n-1;i++)
            cout<<varfuri[i]<<", ";
        cout<<varfuri[n-1]<<"}"<<endl;

        cout<<"U={";
        for(i=0;i<m-1;i++)
            cout<<"("<<arce[i].get_i()<<","<<arce[i].get_j()<<"),";
        cout<<"("<<arce[i].get_i()<<","<<arce[i].get_j()<<")}"<<endl;
    }
};

multime<int> get_Xp(graf Gp)
{
    multime<int> r=Gp.get_X();
    int i;
    for(i=0;i<r.get_size();i++)
    {
        if(r[i]<100)
            {r.rem(r[i]);
            i--;}
    }
    return r;

}
void reducere(graf &Gp, multime<int> &T)
{
    cout<<"\n\nRedus\n";
    while(1)
    {
        int i,j;
        int gasit=-1;
        multime<int> delta_m;
        multime<int> Xp=get_Xp(Gp);
        int n=Xp.get_size();
        for(j=0;j<n;j++)
        {
            delta_m=Gp.get_gamma_minus(Xp[j]);
            for(i=0;i<delta_m.get_size();i++)
                cout<<delta_m[i]<< " " ;
            if(delta_m.get_size()==1)
            {
                gasit=Xp[j];
                cout<<gasit;
                break;
            }
        }

        if(gasit==-1)
            return;

        delta_m=Gp.get_gamma_minus(gasit);
        T.reuneste(delta_m);
        j=delta_m[0];
        delta_m=Gp.get_gamma_plus(j);
        delta_m.add(j);
        for(i=0;i<delta_m.get_size();i++)
            Gp.elimina_varf(delta_m[i]);


        Gp.afiseaza();

    }
}
int main()
{
    int n,m;
    graf G;
    graf Gp;
    ifstream in("graf.txt");
    in>>n>>m;
    int i,v1,v2,j;
    for(i=0;i<n;i++)
    {
        G.adauga_varf(i+1);
        Gp.adauga_varf(i+1);
        Gp.adauga_varf(i+101);
    }
    for(i=0;i<m;i++)
    {
        in>>v1>>v2;
        G.adauga_arc(v1,v2);
    }

    multime<int> gm;
    for(i=1;i<=n;i++)
    {
        gm=G.get_gamma_minus(i);
        Gp.adauga_arc(i,i+100);
        for(j=0;j<gm.get_size();j++)
            Gp.adauga_arc(i,gm[j]+100);
    }

    multime<int> T;
    multime<int> X;
    multime<int> aux;
    G.afiseaza();


    while(G.get_X().get_size()!=0)
    {
        Gp.afiseaza();cout<<endl;

        i=G.get_X()[0];
        aux.goleste();
        T.add(i);
        aux.add(i);
        aux.reuneste(Gp.get_gamma_plus(i));
        for(j=0;j<aux.get_size();j++)
            Gp.elimina_varf(aux[j]);
        Gp.afiseaza();cout<<endl;cout<<endl;
        for(i=0;i<G.get_X().get_size();i++)
            if(G.get_gamma_plus(G.get_X()[i]).get_size()==0)
                {G.elimina_varf(G.get_X()[i]);
                Gp.elimina_varf(G.get_X()[i]);
                i--;}
        Gp.afiseaza();cout<<endl;cout<<endl;
        reducere(Gp,T);
        Gp.afiseaza();cout<<endl;cout<<endl;
        for(i=0;i<T.get_size();i++)
        {
            cout<<T[i]<< " ";
        }
        cout<<endl;
    }




    return 0;
}
