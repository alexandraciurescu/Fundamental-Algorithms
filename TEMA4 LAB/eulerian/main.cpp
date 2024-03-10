#include <bits/stdc++.h>

using namespace std;

ifstream fin("graf.in");
ofstream fout("graf.out");


const int NMAX=1000;
vector <int> G[NMAX];
vector <int> C;
int n,m;
bool viz[NMAX];

vector <pair<int,int>> M;
bool elimina[NMAX];
vector <int> L[NMAX]; ///L[x]=lista muchiilor cu care este incident nodul x

void Citire()
{ fin>>n>>m;
  for(int i=1; i<=m; i++)
  {int x,y;
   fin>>x>>y;
   G[x].push_back(y);
   G[y].push_back(x);
   M.push_back({x,y});
   L[x].push_back(i-1);
   L[y].push_back(i-1);
  }

}

void DFS(int x)
{ viz[x]=1;
  for(auto node: G[x])
    if(viz[node]==0)
      DFS(node);

}

bool Eulerian()
{
    bool ok=1;
    for(int i=1; i<=n; i++)
        if(G[i].size()%2!=0)
            {ok=0;
             break;
            }
    DFS(1);
    for(int i=1; i<=n; i++)
        if(viz[i]==0)
          {ok=0; break;}
    return ok;
}

void Euler(int x)
{ for(auto k: L[x])  ///nodul x este incidednt cu muchia k
     if(elimina[k]==0)  ///daca nu a fost eliminata adaugam muchia la ciclu
        {elimina[k]=1;
         int y;
         if(M[k].first==x) y=M[k].second; ///cealalta extremitate a muchiei
         else y=M[k].first;
         Euler(y);  ///continuam constructia ciclului de la nodul y
        }
  C.push_back(x);
}


int main()
{
    Citire();
    bool eulerian=Eulerian();
    if(eulerian==0) fout<<"Nu este eulerian!";
    else {Euler(1); for(auto x: C) fout<<x<<" ";}
    return 0;
}
