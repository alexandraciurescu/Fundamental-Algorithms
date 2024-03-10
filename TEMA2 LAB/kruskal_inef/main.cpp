///KRUSKAL - O(m*log n + n^2)

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

int R[N]; ///R[i]=componenta conexa din care face parte nodul i

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
    R[i]=i;
}

int Reprez(int x)
{
    return R[x];
}

void Reuneste(int rx, int ry)
{
    for(int i=1; i<=n; i++)
        if(R[i]==rx)
           R[i]=ry;
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
           Reuneste(rx,ry);
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
