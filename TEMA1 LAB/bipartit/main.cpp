#include <iostream>
#include <vector>
//1
using namespace std;

///Graf bipartit = multimea nodurilor poate fi partajata in doua multimi A si B
///                nevide si disjuncte si orice muchie sa aiba o extremitate in
///                multimea A si o extremitate in multimea B
///Solutie:
///Folosim DFS pe graful reprezentat cu liste de adiacenta. => O(n+m)

const int NMAX=100001;

vector <int> G[NMAX];
int n,m;

bool vis[NMAX];
int s[NMAX]; ///s[x]=1 daca x e in multimea 1, s[x]=2 daca x e in multimea 2
bool bipartit=1;

void CitireGraf()
{ int x,y;
  cin>>n>>m;
  for(int i=1; i<=m; i++)
    {cin>>x>>y;
     G[x].push_back(y);
     G[y].push_back(x);
    }
}

void DFS(int x, int mult)
{s[x]=mult; ///nodul x se adauga la multimea mult
 vis[x]=1;
 for(auto next: G[x])
    if(vis[next]==0)
        DFS(next,3-mult); ///next se adauga la multimea complementara vecinului sau
    else if(s[x]==s[next]) ///daca next a fost vizitat verificam daca face parte din
            bipartit=0;    ///multimea in care este si x => nu este bipartit
}


void Bipartit()
{int i;
 for(i=1; i<=n; i++) ///pt fiecare nod nevizitat il punem in multimea 1
    if(vis[i]==0)
      DFS(i,1);
}


void Afisare()
{ if(bipartit==1)
   for(int i=1; i<=n; i++)
        cout<<s[i]<<" ";
  else cout<<"IMPOSSIBLE";
}

int main()
{
    CitireGraf();
    Bipartit();
    Afisare();
    return 0;
}
