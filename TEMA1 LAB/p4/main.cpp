#include <iostream>
#include <vector>
#include <stack>
//4
using namespace std;
///Alg. lui Kosaraju
/// - la citirea datelor de intrare construim listele de adiacenta
///   pentru graful G si graful transpus GT
/// - aplicam DFS pe graful G si memoram nodurile in ordinea momentului
///   de final
/// - aplicam DFS pe graful GT luand in considerare nodurile in ordinea
///   inversa a momentului de final

///Complexitate: O(n+m)

const int NMAX=100001;
int n,m;
vector <int> G[NMAX];
vector <int> GT[NMAX];
bool vis[NMAX],visT[NMAX];
stack <int> S;
int nrc;
int C[NMAX]; ///C[x]=nr comp tare conexa din care face parte x

void CitireGraf()
{int x,y,i;
 cin>>n>>m;
 for(i=1; i<=m; i++)
    {cin>>x>>y;
     G[x].push_back(y);
     GT[y].push_back(x);
    }

}

void DFS(int x)
{ vis[x]=1;
  for(auto next: G[x])
    if(vis[next]==0)
       DFS(next);
  S.push(x);
}

void TimpiFinali()
{for(int i=1; i<=n; i++)
   if(vis[i]==0)
     DFS(i);
}

void DFST(int x)
{ visT[x]=1;
  C[x]=nrc;
  for(auto next: GT[x])
    if(visT[next]==0)
       DFST(next);
}

void Kosaraju()
{ while(!S.empty())
    { int x=S.top();
      S.pop();
      if(visT[x]==0)
        {nrc++;
         DFST(x);
        }

    }

}

void Afisare()
{cout<<nrc<<"\n";
 for(int i=1; i<=n; i++)
    cout<<C[i]<<" ";

}
int main()
{
    CitireGraf();
    TimpiFinali();
    Kosaraju();
    Afisare();
    return 0;
}
