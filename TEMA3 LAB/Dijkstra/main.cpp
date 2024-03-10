#include <bits/stdc++.h>

using namespace std;

ifstream fin ("grafpond.in");
ofstream fout ("grafpond.out");

const int N=105;
const int oo=1e9;

vector <pair<int,int>> G[N];
int n,m;
int sursa;

int d[N]; ///d[x] = dist minima de la sursa la x
int tata[N];
bool viz[N];
priority_queue<pair<int,int> , vector<pair<int,int>> , greater<pair<int,int>> > Q; ///min heap
///(d[u],u)


void Citire()
{ int x,y,c;
  fin>>n>>m;
  for(int i=1; i<=m; i++)
     {fin>>x>>y>>c;
      G[x].push_back({y,c});
      //G[y].push_back({x,c});
     }
  fin>>sursa;
}

void Dijkstra()
{ ///initilizari

  for(int i=1; i<=n ; i++)
    if(i!=sursa){d[i]=oo; Q.push({oo,i});}
  /*for(auto node: G[sursa])
    {d[node.first]=node.second;
     tata[node.first]=sursa;
     Q.push({node.second,node.first});
    }*/
  d[sursa]=0;
  viz[sursa]=0;
  Q.push({0,sursa});

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

void Afisare()
{for(int i=1; i<=n; i++)
   fout<<d[i]<<" ";

}

int main()
{
    Citire();
    Dijkstra();
    Afisare();
    return 0;
}
