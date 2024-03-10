/// Graf dinamic:
///        - https://www.infoarena.ro/problema/apm2


/// Raspundem la query-uri in timpul constructiei APM-ului initial astfel:
///     - de fiecare data cand unim 2 componente conexe (adaugam o muchie in APM),
///       verificam pentru fiecare muchie de query daca acum are capetele in aceeasi componenta
///       si in caz afirmativ, raspunsul este costul muchiei adaugate - 1.



#include <bits/stdc++.h>
using namespace std;

const int N=10001;
const int M=100001;

ifstream fin ("apm2.in");
ofstream fout ("apm2.out");

struct muchie
{   int x,y,cost;
    bool selectat;
};

vector <muchie> G;  ///reprez grafului cu vector de muchii
vector <muchie> Q; ///muchiile de adaugat
int n,m,q;

int costAPM; ///costul arborelui partial de cost minim

int tata[N]; ///memorarea comp conexe folosind vectorul de tati
int h[N]; ///inaltimea fiecarui arbore

void Citire()
{
    fin>>n>>m>>q;
    for(int i=1; i<=m ; i++)
      {
        muchie e;
        fin>>e.x>>e.y>>e.cost;
        //e.selectat=0;
        G.push_back(e);
      }

    for(int i=1; i<=q ; i++)
      {
        muchie e;
        fin>>e.x>>e.y;
        e.cost=-1;  ///nu i-am stabilit inca costul
        //e.selectat=0;
        Q.push_back(e);
      }
}

bool cmp(muchie a, muchie b)
{
    return a.cost<b.cost;
}

///initial se pleaca de la n componente conexe, fiecare reprezentata de un nod
void Initializare()
{ for(int i=1; i<=n; i++)
    tata[i]=h[i]=0;
}


///returneaza radacina arborelui din care face parte nodul x cu compresia caii
int Reprez(int x)
{
    if(tata[x]==0) return x;
    tata[x]=Reprez(tata[x]);
    return tata[x];
}

/// radacina unui arbore devine fiu al radacinii celuilalt arbore
/// arborele cu inaltime mai mica devine subarbore al arborelui cu inaltime mai mare
/// daca cei doi arbori au inaltime egala dupa reuniune inaltimea arborelui creste cu 1
void Reuneste(int x, int y)
{
    int rx=Reprez(x);
    int ry=Reprez(y);
    if (h[rx]>h[ry]) tata[ry]=rx;
    else
        { tata[rx]=ry;
          if(h[rx]==h[ry]) h[rx]=h[rx]+1;
        }
}

void Kruskal()
{
    Initializare();
    for(int i=0; i<m; i++)
      { int rx=Reprez(G[i].x);
        int ry=Reprez(G[i].y);
        if(rx!=ry)
          { Reuneste(G[i].x,G[i].y);
            for(int j=0; j<q; j++) ///pt fiecare muchie care trb sa apara in APM
                if(Reprez(Q[j].x)==Reprez(Q[j].y) && Q[j].cost==-1) ///verific daca cele doua
                                    ///extremitati fac parte din aceeasi comp conexa dupa adaugarea
                                    ///muchiei i
                   Q[j].cost=G[i].cost-1;  ///ca sa fie selectat muchia j in loc de i
          }

      }
}


void Afisare()
{
    for(auto q: Q)
        fout<<q.cost<<"\n";
}


int main()
{
    Citire();
    sort(G.begin(),G.end(),cmp);
    Kruskal();
    Afisare();
    return 0;
}
