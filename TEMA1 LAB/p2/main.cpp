#include <iostream>
#include <vector>
#include <stack>
//2
using namespace std;


///Solutie:
/// Folosim DFS pe graful reprezentat cu liste de adiacenta. => O(n+m)
/// Vom memora intr-o stiva nodurile in ordinea momentului de final
/// Momentul de final al nodului x = momentul in care am terminat de verificat vecinii sai (nodul devine negru)
/// Sortarea topologica se obtine afisand nodurile in ordinea inversa a momentului de
/// final (de aceea le memoram intr-o stiva)
/// Verificam si daca graful nu contine circuite si anume daca nu contine arce de intoarcere


const int NMAX=100001;

vector <int> G[NMAX];
int n,m;

bool vis[NMAX];
stack <int> S;
bool fin[NMAX]; /// fin[x]=1 daca nodul x este negru
bool sorttop=1;

void CitireGraf()
{ int x,y;
  cin>>n>>m;
  for(int i=1; i<=m; i++)
    {cin>>x>>y;
     G[x].push_back(y);
    }
}

void DFS(int x)
{
 vis[x]=1;
 for(auto next: G[x])
    if(vis[next]==0)
        DFS(next);
    else if(fin[next]==0) /// avem arcul (x,next) si next este gri ==> este arc de intoarcere
               sorttop=0; /// => avem un circuit

 /// am terminat de parcurs vecinii lui x, deci il putem adauga in stiva
 fin[x]=1; /// x este negru
 S.push(x);
}


void SortareTopologica()
{int i;
 for(i=1; i<=n; i++)
    if(vis[i]==0)
      DFS(i);
}

void Afisare()
{ if(sorttop)
      { while(!S.empty())
          {cout<<S.top()<<" ";
          S.pop();}
      }
  else cout<<"IMPOSSIBLE";
}

int main()
{
    CitireGraf();
    SortareTopologica();
    Afisare();
    return 0;
}
