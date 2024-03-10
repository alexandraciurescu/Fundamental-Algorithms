///KRUSKAL - O(m*log n) - structuri de multimi disjuncte



#include <bits/stdc++.h>
using namespace std;

const int N=200001;
const int M=400001;

ifstream fin ("apm.in");
ofstream fout ("apm.out");

struct muchie
{   int x,y,cost;
    bool selectat;
};

vector <muchie> G;  ///reprez grafului cu vector de muchii
int n,m;

int costAPM; ///costul arborelui partial de cost minim

int tata[N]; ///memorarea comp conexe folosind vectorul de tati
int h[N]; ///inaltimea fiecarui arbore

void Citire()
{
    fin>>n>>m;
    for(int i=1; i<=m ; i++)
      {
        muchie e;
        fin>>e.x>>e.y>>e.cost;
        e.selectat=0;
        G.push_back(e);
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
{   int ct=0; ///cate muchii am selectat in apm
    Initializare();
    for(int i=0; i<m && ct<n-1; i++)
      { int rx=Reprez(G[i].x);
        int ry=Reprez(G[i].y);
        if(rx!=ry)
          {ct++;
           G[i].selectat=1;
           costAPM+=G[i].cost;
           Reuneste(G[i].x,G[i].y);
          }

      }
}


void Afisare()
{
    fout<<costAPM<<"\n";
    fout<<n-1<<"\n";
    for(int i=0; i<m; i++)
       if(G[i].selectat==1)
         fout<<G[i].x<<" "<<G[i].y<<"\n";
}


int main()
{
    Citire();
    sort(G.begin(),G.end(),cmp);
    Kruskal();
    Afisare();
    return 0;
}
