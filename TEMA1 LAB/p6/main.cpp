/// 6. Distante si drumuri minime
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;

ifstream fin("graf.in");
ofstream fout("graf.out");

///Solutie:
/// Folosim BFS pe graful reprezentat cu liste de adiacenta
/// deoarece problema presupune determinarea drumurilor de lungime minima
/// dar vom adauga de la inceput in coada toate "punctele de control"
/// simuland parcurgeri BFS (in paralel) din fiecare punct de control
/// Astfel fiecare nod va fi vizitat din cel mai apropiat punct de control

/// Complexitate O(n+m)


const int NMAX=100001;

vector <int> G[NMAX];
int n,m;

bool vis[NMAX];
queue <int> Q;
int D[NMAX]; /// D[X]=distanta de la nodul x pana la cel mai apropiat punct de control



void CitireGraf()
{ int x,y;
  fin>>n>>m;
  for(int i=1; i<=m; i++)
    {fin>>x>>y;
     G[x].push_back(y);
     G[y].push_back(x);
    }
  /// citim punctele de control
  while(fin>>x)
       { Q.push(x); /// le adaugam in coada
         vis[x]=1;  /// si le marcam ca vizitate
         D[x]=0;
        }
}

void BFS()
{ while(!Q.empty()) /// cat timp mai sunt noduri in coada
    { int x=Q.front(); /// extragem primul nod x
      Q.pop();
      for(auto next: G[x])   /// parcurgem lista de adiacenta a nodului x
        if(vis[next]==0)     /// si pentru fiecare vecin nevizitat inca
           { D[next]=D[x]+1; ///  stabilim distanta minima
             Q.push(next);   /// il adaugam in coada
             vis[next]=1;    /// si il marcam ca vizitat
           }
    }
}



void Afisare()
{ for(int i=1; i<=n; i++)
        fout<<D[i]<<" ";
}

int main()
{
    CitireGraf();
    BFS();
    Afisare();
    return 0;
}
