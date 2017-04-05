#include <stdlib.h>
#include <iostream>
#include <fstream>
#define INFINIT 100000
using namespace std;


class arc
{
private:
    int i,j,val;

public:
    arc(){
        i=-1;j=-1;val=0;}

    arc(int i,int j, int val){
        this->i=i;this->j=j;this->val=val;}

    int get_i(){
        return i;}

    int get_j(){
        return j;}

    int get_val(){
        return val;}

    arc operator=(arc other){
        i=other.i;
        j=other.j;
        val=other.val;
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

    int exista(elem x)
    {
        int i;
        for(i=0;i<n;i++)
            if(x==v[i])
                return 1;
        return 0;
    }
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

    void adauga_arc(int i,int j,int val){
        U.add(arc(i,j,val));}

    void elimina_varf(int v)
    {
        int i;
        for(i=0;i<U.get_size();i++)
        {
            if((U[i].get_i()==v)||(U[i].get_j()==v))
            {
                U.rem(arc(U[i].get_i(),U[i].get_j(),0));
                i--;
            }
        }
        X.rem(v);
    }

    void elimina_arc(int i, int j){
        U.rem(arc(i,j,0));}

    arc exista_arc(int v1, int v2)
    {
        int i;
        arc a=arc(v1,v2,0);
        for(i=0;i<U.get_size();i++)
            if(U[i]==a)
                return U[i];
        return arc(0,0,0);
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

void afis_arc(arc a)
{
    cout<<a.get_i()<<" "<<a.get_j()<<" "<<a.get_val()<<endl;
}

multime<arc> get_omega_plus(graf G,multime<int> A)
{
    multime<arc> omega;
    multime<int> gamma;
    int i,j;
    for(i=0;i<A.get_size();i++)
    {
        gamma=G.get_gamma_plus(A[i]);
        for(j=0;j<gamma.get_size();j++)
        {
            if(!(A.exista(gamma[j])))
            {
                omega.add(arc(A[i],gamma[j],G.exista_arc(A[i],gamma[j]).get_val()));
            }
        }
    }
    return omega;
}

int main()
{
    int n,m;
    graf G;
    ifstream in("graf.txt");
    in>>n>>m;
    int i,v1,v2,val,j;
    for(i=0;i<n;i++)
    {
        G.adauga_varf(i+1);
    }
    for(i=0;i<m;i++)
    {
        in>>v1>>v2>>val;
        G.adauga_arc(v1,v2,val);
        //G.adauga_arc(v2,v1,val);
    }


    // s este varful 1, t este varful n
    unsigned char is_in[n];
    multime<int> A;
    multime<arc> O;
    int cap,cap_min=INFINIT;

    for(i=0;i<n;i++)
        is_in[i]=0;
    is_in[0]=1;

    while(is_in[n-1]!=1)
    {
        for(i=0;i<n;i++)
        {
            if(is_in[i]==1)
                A.add(i+1);
            else
                A.rem(i+1);
        }
        O=get_omega_plus(G,A);
        cap=0;
        for(i=0;i<O.get_size();i++)
        {
            cap+=O[i].get_val();
        }
        if(cap<cap_min)
        {
            cap_min=cap;
        }

        is_in[1]++;
        for(i=1;i<n-1;i++)
        {
            if(is_in[i]==2)
            {
                is_in[i]=0;
                is_in[i+1]++;
            }
        }
    }

    cout<<"Capacitate minima: "<<cap_min<<endl;
    for(i=0;i<n;i++)
        is_in[i]=0;
    is_in[0]=1;

    while(is_in[n-1]!=1)
    {
        for(i=0;i<n;i++)
        {
            if(is_in[i]==1)
                A.add(i+1);
            else
                A.rem(i+1);
        }
        O=get_omega_plus(G,A);
        cap=0;
        for(i=0;i<O.get_size();i++)
        {
            cap+=O[i].get_val();
        }
        if(cap==cap_min)
        {
            cout<<"\n--------------\n";
            cout<<"A= ";
            for(i=0;i<A.get_size();i++)
                cout<<A[i]<<" ";
            cout<<"\n\n";
            for(i=0;i<O.get_size();i++)
                afis_arc(O[i]);

        }

        is_in[1]++;
        for(i=1;i<n-1;i++)
        {
            if(is_in[i]==2)
            {
                is_in[i]=0;
                is_in[i+1]++;
            }
        }
    }

    return 0;
}
