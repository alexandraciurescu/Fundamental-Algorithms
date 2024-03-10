/// Drum critic
/// Complexitate
///    - Citire O(n+m)
///    - Sortare topologica O(n+m)
///    - Relaxare O(m)
///   -------------------------
///      O(m+n)

#include <bits/stdc++.h>
using namespace std;
const int N=105;
const int oo=1e9;

ifstream fin("activitati.in");

int n,m;
vector <pair<int,int>> G[N];
int D[N]; /// durata activitatilor
int GradExt[N], GradInt[N];

stack <int> S; /// sortarea topologica
bool viz[N];

int d[N];  /// drum critic
int tata[N];

void Citire()
{  int i,x,y;
   fin>>n;
   for(i=1; i<=n; i++) fin>>D[i];
   fin>>m;
   for(i=1; i<=m; i++)
      { fin>>x>>y;
        G[x].push_back({y,D[x]}); /// liste de adiacenta
        GradExt[x]++;             /// calculam gradul intern/extern al fiecarui nod
        GradInt[y]++;             /// pentru a "trasa" arcele pentru S (0) si T(n+1)
      }
   for(int i=1; i<=n; i++)
      { if(GradInt[i]==0) /// arcele de la S la nodurile cu grad intern 0
             G[0].push_back({i,0});
        if(GradExt[i]==0) /// arcele de la nodurile cu grad extern 0 la T
             G[i].push_back({n+1,D[i]});
      }
}

void DFS(int x)
{ viz[x]=1;
  for(auto node:G[x])
      if(!viz[node.first]) DFS(node.first);
  S.push(x); /// memorarea nodurilor intr-o stiva pentru a le prelucra in ordinea inversa a timpilor de final
}

void SortareTopologica()
{ for(int i=1; i<=n+1; i++)
     if(!viz[i]) DFS(i);
}

void DrumCritic()
{ /// initializare
  for(int i=0; i<=n+1; i++) d[i]=-oo, tata[i]=0;
  SortareTopologica();
  for(auto node:G[0]) d[node.first]=0; /// toate nodurile x adiacente cu S au d[x]=0
  while(!S.empty()) /// prelucram nodurile conform sortarii topologice
    { int x=S.top(); S.pop();
      //cout<<x<<"\n";
      for(auto node:G[x])  /// relaxare muchii
         if(d[x]+node.second>d[node.first])
                 d[node.first]=d[x]+node.second, tata[node.first]=x;
    }
}

void Drum(int x)
{  if(tata[x]) Drum(tata[x]);
   if(x!=0 && x!=n+1) cout<<x<<" ";
}

void Afisare()
{ cout<<"Timp minim "<<d[n+1]<<"\n";
  cout<<"Activitati critice: "; Drum(n+1); cout<<"\n";
  for(int i=1; i<=n; i++)
     cout<<i<<":"<<d[i]<<" "<<d[i]+D[i]<<"\n";

}

int main()
{  Citire();
   DrumCritic();
   Afisare();
   return 0;
}
