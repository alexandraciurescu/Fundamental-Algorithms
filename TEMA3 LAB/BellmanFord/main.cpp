#include <bits/stdc++.h>

///ALG. BELLMAN FORD
///complexitate: O(n*m)

using namespace std;

ifstream fin ("grafpond.in");
ofstream fout ("grafpond.out");

const int NMAX=1000;
const int oo=1e9;

int n,m;
vector <pair<int,int>> G[NMAX];

int s; //nodul de start
int d[NMAX];
int tata[NMAX];

queue<int> Q;
bool in_q[NMAX];

int niv[NMAX];

void Citire()
{ fin>>n>>m;
  for(int i=1; i<=m; i++)
    {int x,y,c;
     fin>>x>>y>>c;
     G[x].push_back({y,c});
    }
 fin>>s;
}

int BellmanFord()
{ for(int i=1; i<=n; i++)
    d[i]=oo, tata[i]=0, niv[i]=0;
  d[s]=tata[s]=0;
  Q.push(s);
  in_q[s]=1;
  while(!Q.empty())
    {int u=Q.front();
     Q.pop();
     in_q[u]=0;
     for(auto node: G[u])
        if(d[u]<oo && d[u]+node.second<d[node.first])
         { d[node.first]=d[u]+node.second;
           tata[node.first]=u;
           Q.push(node.first);
           in_q[node.first]=1;
           niv[node.first]=niv[u]+1;
           if(niv[node.first]>n-1)
            return node.first;
         }
    }
return 0;

}

void Drum(int x)
{
    if(tata[x]!=0) Drum(tata[x]);
    fout<<x<<" ";
}

void Afisare1()
{ for(int i=1; i<=n; i++)
   if(i!=s)
   {
       fout<<"Drum: ";
       Drum(i);
       fout<<"Cost: "<<d[i]<<"\n";
   }

}

void Drum2(int x, int y)
{
    if(tata[y]!=x) Drum2(x,tata[y]);
    fout<<y<<" ";

}


void Afisare2(int x)
{ for(int i=1; i<=n && tata[x]!=0; i++)
    x=tata[x];
 fout<<"Circuit de cost negativ:\n";
 Drum2(x,x);

}

int main()
{
    Citire();
    int i=BellmanFord();
    if(i==0) Afisare1();
    else Afisare2(i);
    return 0;
}
