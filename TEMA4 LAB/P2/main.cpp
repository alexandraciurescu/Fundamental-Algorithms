#include <bits/stdc++.h>

using namespace std;

ifstream fin ("graf.in");

const int NMAX=100;
int n,m;
int s,t;
int C[NMAX][NMAX]; ///capacitatea fiecarui arc
int F[NMAX][NMAX]; ///fluxul fiecarui arc
vector <int> H[NMAX];
queue<int> Q;
bool viz[NMAX];
int tata[NMAX];
int I; ///capacitatea reziduala a lantului nesaturat

///pt graf bipartit
int S[NMAX]; ///1 sau 2 (multimea din care face parte fiecare vf)
bool vis[NMAX];
bool bipartit=1;
int Tata[NMAX];
int nod;


///pt cuplaj
vector <pair<int,int>> G[NMAX];

void Citire()
{
    fin>>n>>m;
    for(int i=1; i<=m; i++)
      {int x,y;
       fin>>x>>y;
       H[x].push_back(y);
       H[y].push_back(x);
      }
}

void DFS(int x, int mult)
{S[x]=mult; ///nodul x se adauga la multimea mult
 vis[x]=1;
 for(auto next: H[x])
    if(vis[next]==0)
        Tata[next]=x,DFS(next,3-mult); ///next se adauga la multimea complementara vecinului sau
    else if(S[x]==S[next]) ///daca next a fost vizitat verificam daca face parte din
            {nod=next; bipartit=0;}    ///multimea in care este si x => nu este bipartit
}

/*
void AfisCiclu()
{ int x=nod;
  cout<<x<<" ";
  while(Tata[x]!=nod)
    {cout<<Tata[x]<<" "; x=Tata[x];}
}
*/


void Bipartit()
{int i;
 for(i=1; i<=n; i++) ///pt fiecare nod nevizitat il punem in multimea 1
    if(vis[i]==0)
      DFS(i,1);
}

void Initializari()
{ s=n+1;
  t=n+2;
  S[s]=1,S[t]=2;
  ///liste de adiacenta graf orientat
  for(int i=1; i<=n; i++)
    if(S[i]==1)
      for(auto node: H[i])
           {G[i].push_back({node,1}), G[node].push_back({i,-1});
            C[i][node]=1;
           }
  for(int i=1; i<=n; i++)
     if(S[i]==1) {G[s].push_back({i,1}), G[i].push_back({s,-1}); C[s][i]=1;}

  for(int i=1; i<=n; i++)
     if(S[i]==2) {G[t].push_back({i,-1}), G[i].push_back({t,1}); C[i][t]=1;}
  n=n+2;
}


bool ConstruiesteLantNesaturat()
{ /// initializari pentru fiecafre BFS
  for(int i=1; i<=n; i++)
    viz[i]=tata[i]=0;
  while(!Q.empty()) Q.pop(); /// golim coada de la apelul anterior
  I=1e9;

  Q.push(s);
  viz[s]=1;
  while(!Q.empty())
   {int u=Q.front();
    Q.pop();
    for(auto node: G[u])
        if(viz[node.first]==0)
         { int v=node.first;
           int sens=node.second;
           if(sens==1)
             {if(C[u][v]-F[u][v]>0)
                {viz[v]=1; Q.push(v); tata[v]=u;
                 I=min(I,C[u][v]-F[u][v]);
                 if(v==t) return 1;
                }
             }
            else {
                if(F[v][u]>0)
                    {viz[v]=1; Q.push(v); tata[v]=-u;
                     I=min(I,F[v][u]);
                     if(v==t) return 1;
                    }
                 }
         }

   }
   return 0;
}



void RevizuiesteLant()
{ int v=t;
  while(v!=s)
    { int u=tata[v]; ///avem arcul (u,v) sau arcul (v,-u)
      if(u>0)
        F[u][v]+=I;
      else F[v][-u]-=I;
      v=abs(u);
    }

}

void EdmondKarp()  ///lanturi nesaturate de lg minima
{
  while(ConstruiesteLantNesaturat())
     RevizuiesteLant();
}

void Cuplaj()
{n-=2;
  for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
       if(F[i][j]==1) cout<<i<<" "<<j<<"\n";


}

int main()
{
    Citire();
    Bipartit();
    if(bipartit==0) cout<<"Nu este bipartit"<<"\n"; //AfisCiclu();}
    else Initializari(), EdmondKarp(), Cuplaj();

    return 0;
}
