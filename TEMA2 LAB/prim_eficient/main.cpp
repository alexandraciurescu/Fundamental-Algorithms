///algoritmul lui Prim O(m*log n)

#include <bits/stdc++.h>

using namespace std;

ifstream fin ("apm.in");
ofstream fout ("apm.out");

const int N=200001;
const int M=400001;
const int oo=1e9;

int n,m;
vector <pair<int,int>> G[N]; ///liste de adiacenta
int costAPM;


int d[N]; /// d[i]=distanta minima de la nodul i la unul dintre nodurile
          /// adaugate deja la apm

priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;


bool vis[N];
int tata[N];

void Citire()
{   int x,y,cost;
    fin>>n>>m;
    for(int i=1; i<=m; i++)
        {fin>>x>>y>>cost;
         G[x].push_back({y,cost});
         G[y].push_back({x,cost});
        }

}

///initializam vectorul de dist minime cu cea mai mare val posibila (oo)
void Initializare()
{
    for(int i=1; i<=n; i++)
        d[i]=oo;
}

void Prim()
{ Initializare();
  d[1]=0; ///nodul de start este 1
  pq.push({0,1});
  while(!pq.empty())
    { /// extragem primul element
      int node=pq.top().second;
      int dmin=pq.top().first;
      pq.pop();

      if(vis[node]==1) continue;

      vis[node]=1;
      costAPM+=dmin;
      /// reactualizam vectorul d pt nodurile neselectate folosind noul nod adaugat
      for(auto x : G[node])
        if(vis[x.first]==0 && d[x.first]>x.second)
              { d[x.first]=x.second;
                tata[x.first]=node;
                pq.push({x.second,x.first});
              }
    }
}

void Afisare()
{
    fout<<costAPM<<"\n";
    fout<<n-1<<"\n";
    for(int i=2; i<=n; i++)
        fout<<i<<" "<<tata[i]<<"\n";
}
int main()
{
    Citire();
    Prim();
    Afisare();
    return 0;
}
