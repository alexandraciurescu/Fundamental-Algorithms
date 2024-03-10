#include <bits/stdc++.h>

using namespace std;

ifstream fin("secvente.in");

const int NMAX=100;
int n,m;
int s,t;
int C[NMAX][NMAX]; ///capacitatea fiecarui arc
int F[NMAX][NMAX]; ///fluxul fiecarui arc
vector <pair<int,int>> G[NMAX];

queue<int> Q;
bool viz[NMAX];
int tata[NMAX];
int I; ///capacitatea reziduala a lantului nesaturat

int s1[NMAX],s2[NMAX];


void Citire()
{
    fin>>n;
    for(int i=1; i<=n; i++)
        fin>>s1[i];
    for(int i=1; i<=n; i++)
        fin>>s2[i];

}


void Initializari()
{ s=2*n+1;
  t=2*n+2;

  for(int i=1; i<=n; i++)
    for(int j=n+1; j<=2*n; j++)
      if(j!=n+i)
          {G[i].push_back({j,1});
           G[j].push_back({i,-1});
           C[i][j]=1;
          }

  for(int i=1; i<=n; i++)
     {G[s].push_back({i,1});
      G[i].push_back({s,-1});
      C[s][i]=s1[i];
     }
  for(int i=n+1; i<=2*n; i++)
     {G[i].push_back({t,1});
      G[t].push_back({i,-1});
      C[i][t]=s2[i-n];
     }
}


bool ConstruiesteLantNesaturat()
{ /// initializari pentru fiecare BFS
  for(int i=1; i<=2*n+2; i++)
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

void Afis()
{
    int flux=0;
  /// flux maxim
  for(int j=1; j<=n; j++)
    flux=flux+F[s][j];
  int suma=0;
  for(int i=1; i<=n; i++)
    suma+=s1[i];
  if(flux!=suma) cout<<"NU";
  else
    { for(int i=1; i<=n; i++)
        for(auto node: G[i])
           if(F[i][node.first]==1 && node.second==1)
             cout<<i<<" "<<node.first-n<<"\n";

    }
}

int main()
{
    Citire();
    Initializari();
    EdmondKarp();
    Afis();

    return 0;
}
