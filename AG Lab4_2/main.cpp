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
    arc(){
        i=-1;j=-1;}

    arc(int i,int j){
        this->i=i;this->j=j;}

    int get_i(){
        return i;}

    int get_j(){
        return j;}

    arc operator=(arc other){
        i=other.i;
        j=other.j;
        return *this;}

    int operator==(arc other){
        return((i==other.i)&&(j==other.j));}
};

template <typename elem>
class multime
{
private:
    elem v[100];
    int n;

public:
    multime(){
        n=0;}

    void goleste(){
        n=0;}

    int rem_last()
    {
        if(n==0)
            return -1;
        n--;
        return v[n];
    }

    int get_maxim()
    {
        if(n==0)
            return 0;
        int i,m=v[0];
        for(i=0;i<n;i++)
            if(m<v[i])
                m=v[i];
        return m;
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
    elem operator[](int poz){
        return v[poz];}

    elem* get_all(){
        return v;}

    int get_size(){
        return n;}

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

    multime<int> get_X(){
        return X;}

    multime<arc> get_U(){
        return U;}

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

    void adauga_varf(int v){
        X.add(v);}

    void adauga_arc(int i,int j){
        U.add(arc(i,j));}

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

    void elimina_arc(int i, int j){
        U.rem(arc(i,j));}

    int exista_arc(int v1, int v2)
    {
        int i;
        arc a=arc(v1,v2);
        for(i=0;i<U.get_size();i++)
            if(U[i]==a)
                return 1;
        return 0;
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
int este_MES(multime<int> T,graf G)
{
    multime<int> XmT=G.get_X();
    int i,j,ok;
    for(i=0;i<T.get_size();i++)
        XmT.rem(T[i]);

    for(i=0;i<XmT.get_size();i++)
    {
        ok=0;
        for(j=0;j<T.get_size();j++)
            if(G.exista_arc(XmT[i],T[j]))
                {ok=1;
                break;}
        if(!ok)
            return 0;
    }
    return 1;
}
int main()
{
    int n,m;
    graf G;
    ifstream in("graf.txt");
    in>>n>>m;
    int i,v1,v2;
    for(i=0;i<n;i++)
    {
        G.adauga_varf(i+1);
    }
    for(i=0;i<m;i++)
    {
        in>>v1>>v2;
        G.adauga_arc(v1,v2);

    }
    multime<int> T;

    int len,
        gasit=0,
        ult=0,
        urm=0,
        s=G.get_X().get_size();

    for(len=1;len<=G.get_X().get_size();len++)
    {
        ult=0;
        do
        {
            if(ult==0) ///Nu s-a eliminat niciun element la pasul anterior
            {
                urm=T.get_maxim()+1;
                if(urm>s)
                    ult=T.rem_last();
                else
                    if(T.get_size()<len)
                        {T.add(T.get_maxim()+1);
                        ult=0;}
                    else
                        ult=T.rem_last();
            }
            else
            {
                if(ult!=s)
                    {T.add(ult+1);
                    ult=0;}
                else
                    ult=T.rem_last();
            }
            if(T.get_size()==len)
            {
                if(este_MES(T,G))
                    {gasit=1;
                    break;}
            }
        }
        while(ult!=-1);
        if(gasit)
            break;
    }

    for(i=0;i<T.get_size();i++)
    {
        cout<<T[i]<<" ";
    }

    return 0;
}
