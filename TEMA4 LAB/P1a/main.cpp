#include <bits/stdc++.h>

using namespace std;

ifstream fin ("retea.in");
ofstream fout ("retea.out");

const int NMAX=105;
int n,m;
int s,t;
int C[NMAX][NMAX]; ///capacitatea fiecarui arc
int F[NMAX][NMAX]; ///fluxul fiecarui arc
vector <pair<int,int>> G[NMAX]; ///1.vecin si 2.sensul (1 direct, -1 invers)

queue<int> Q;
bool viz[NMAX];
int tata[NMAX];
int I; ///capacitatea reziduala a lantului nesaturat

void Citire()
{
    fin>>n>>s>>t>>m;
    for(int i=1; i<=m; i++)
      {int x,y,c,f;
       fin>>x>>y>>c>>f;
       C[x][y]=c;
       F[x][y]=f;
       G[x].push_back({y,1});
       G[y].push_back({x,-1});
      }
}


void PunctulA()
{   bool ok=1; ///conditia de marginire
    for(int i=1; i<=n && ok; i++)
        for(int j=1; j<=n && ok; j++)
          if(F[i][j]<0 || F[i][j]>C[i][j])
             ok=0;
    if(ok==0) {cout<<"NU\n"; return;}

    ///conditia de conservare
    for(int i=1; i<=n && ok; i++)
      if(i!=s && i!=t)
       { int s1=0, s2=0;
         for(int j=1; j<=n; j++)
            s1+=F[i][j], s2+=F[j][i];
         if(s1!=s2) ok=0;
       }
    if(ok==0) {cout<<"NU"<<"\n"; return;}
    cout<<"DA"<<"\n";
}

bool ConstruiesteLantNesaturat()
{ /// initializari pentru fiecare BFS
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

///   1 -> 2 -> 3  <- 4 -> 5
///   1   2   3   4    5
///   0   1   2  -3    4

///   v=5   4   3
///   u=4  -3   2

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

void PunctulB()
{ int flux=0;
  /// flux maxim
  for(int j=1; j<=n; j++)
    flux=flux+F[s][j];
  cout<<flux<<"\n";
  for(int i=1; i<=n; i++)
    {for(int j=1; j<=n; j++)
       if(C[i][j]>0) cout<<i<<" "<<j<<" "<<F[i][j]<<"\n";
    }
  /// taietura minima -- muchiile pe care le eliminam -> nu mai sunt legate S-T
  int K=0;
  for(int i=1; i<=n; i++)
     if(viz[i]==1)
        for(auto node: G[i])
          if(node.second==1 && viz[node.first]==0)
            K+=F[i][node.first];
  cout<<K<<"\n";

   for(int i=1; i<=n; i++)
     if(viz[i]==1)
        for(auto node: G[i])
          if(node.second==1 && viz[node.first]==0)
            cout<<i<<" "<<node.first<<"\n";


}

int main()
{
    Citire();
    PunctulA();
    EdmondKarp();
    PunctulB();

    return 0;
}
