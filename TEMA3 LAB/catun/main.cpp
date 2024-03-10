#include <bits/stdc++.h>

using namespace std;

ifstream fin ("catun.in");
ofstream fout ("catun.out");

const int N=36001;
const int oo=1e9;

vector <pair<int,int>> G[N];
int n,m,k; ///k=nr fortarete
bool fort[N];

int d[N]; ///d[x] = dist minima de la sursa la x
int tata[N];
bool viz[N];
priority_queue<pair<int,int> , vector<pair<int,int>> , greater<pair<int,int>> > Q;
///(cost,nod)


void Citire()
{ int x,y,c;
  fin>>n>>m>>k;
  for(int i=1; i<=k; i++)
    fin>>x, fort[x]=1;
  for(int i=1; i<=m; i++)
     {fin>>x>>y>>c;
      G[x].push_back({y,c});
      G[y].push_back({x,c});
     }

}

void Dijkstra()
{ ///initilizari


  for(int i=1; i<=n; i++)
    if(fort[i]==1)
      {d[i]=0;
       tata[i]=i;
       Q.push({0,i});
      }
    else d[i]=oo;



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
             tata[node.first]=tata[x]; ///se va aproviziona de la aceeasi fortareata ca si x
             Q.push({d[node.first],node.first});

           }
         else if(d[x]+node.second==d[node.first])
            tata[node.first]=min(tata[node.first],tata[x]);

    }

}

void Afisare()
{for(int i=1; i<=n; i++)
   if(fort[i]==1 || d[i]==oo)
       fout<<0<<" ";
   else fout<<tata[i]<<" ";

}

int main()
{
    Citire();
    Dijkstra();
    Afisare();
    return 0;
}
