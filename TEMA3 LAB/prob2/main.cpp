#include <bits/stdc++.h>

using namespace std;

ifstream fin ("grafpond.in");
ofstream fout ("grafpond.out");

const int N=105;
const int oo=1e9;

vector <pair<int,int>> G[N];
int n,m;
int sursa;
int k; ///nr puncte de control
bool control[N]; ///control[x]=1 daca x e nod de control

int d[N]; ///d[x] = dist minima de la sursa la x
int tata[N];
bool viz[N];
priority_queue<pair<int,int> , vector<pair<int,int>> , greater<pair<int,int>> > Q;
///(cost,nod)


void Citire()
{ int x,y,c;
  fin>>n>>m;
  for(int i=1; i<=m; i++)
     {fin>>x>>y>>c;
      G[x].push_back({y,c});
      G[y].push_back({x,c});
     }
  fin>>k;
  for(int i=1; i<=k; i++)
    {fin>>x;
     control[x]=1;
    }
  fin>>sursa;
}

void Dijkstra()
{ ///initilizari

  for(int i=1; i<=n; i++)
    {d[i]=oo; Q.push({oo,i});}
  for(auto node: G[sursa])
    {d[node.first]=node.second;
     tata[node.first]=sursa;
     Q.push({node.second,node.first});
    }
  d[sursa]=0;
  viz[sursa]=0;

  while(!Q.empty())
    { int x = Q.top().second;
      Q.pop();

      if(viz[x]==1)
        continue; ///trecem la elem urmator
      viz[x]=1;
      ///relaxarea arcelor
      for(auto node: G[x])
        if(d[x]+node.second<d[node.first])
           { d[node.first]=d[x]+node.second;
             tata[node.first]=x;
             Q.push({d[node.first],node.first});

           }

    }

}


void Drum(int x)
{ if(tata[x]!=0) Drum(tata[x]);
  fout<<x<<" ";

}

void Afisare()
{int dmin=1e9,punct;
 for(int i=1; i<=n; i++)
   if(control[i]==1 && d[i]<dmin)
       punct=i, dmin=d[i];
 fout<<punct<<"\n";
 Drum(punct);

}

int main()
{
    Citire();
    Dijkstra();
    Afisare();
    return 0;
}
