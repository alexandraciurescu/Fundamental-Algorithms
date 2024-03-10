#include <iostream>
#include <vector>
#include <stack>
//2b
using namespace std;


///Solutie:
/// Folosim DFS pe graful reprezentat cu liste de adiacenta. => O(n+m)
/// Vom memora intr-o stiva nodurile in ordinea momentului de final
/// Momentul de final al nodului x = momentul in care am terminat de verificat vecinii sai (nodul devine negru)
/// Sortarea topologica se obtine afisand nodurile in ordinea inversa a momentului de
/// final (de aceea le memoram intr-o stiva)
/// Verificam si daca graful nu contine circuite si anume daca nu contine arce de intoarcere

///Pt afisarea circuitului am folosit o functie recursiva care construieste drumul de la nodul x la nodul y
///unde (x,y) e arc de intoarcere.


const int NMAX=100001;

vector <int> G[NMAX];
int n,m;

bool vis[NMAX];
stack <int> S;
bool fin[NMAX]; /// fin[x]=1 daca nodul x este negru
bool sorttop=1;

int tata[NMAX];
int c1,c2;

void CitireGraf()
{
    int x,y;
    cin>>n>>m;
    for(int i=1; i<=m; i++)
    {
        cin>>x>>y;
        G[x].push_back(y);
    }
}

void DFS(int x)
{
    vis[x]=1;
    for(auto next: G[x])
        if(vis[next]==0)
            {tata[next]=x;
             DFS(next);
            }
        else if(fin[next]==0) /// avem arcul (x,next) si next este gri ==> este arc de intoarcere
            {sorttop=0; /// => avem un circuit
             c1=x;
             c2=next;
            }

/// am terminat de parcurs vecinii lui x, deci il putem adauga in stiva
    fin[x]=1; /// x este negru
    S.push(x);
}


void SortareTopologica()
{
    int i;
    for(i=1; i<=n; i++)
        if(vis[i]==0)
            DFS(i);
}

void Drum(int x, int y)
{if(tata[x]!=y) {Drum(tata[x],y); cout<<x<<" ";}
 else cout<<y<<" "<<x<<" ";
}

void Afisare()
{
    if(sorttop)
    {
        while(!S.empty())
        {
            cout<<S.top()<<" ";
            S.pop();
        }
    }
    else
    {
        cout<<"Graful contine cel putin un circuit: ";
        Drum(c1,c2);
        cout<<c2; ///pt circuit

    }
}
    int main()
    {
        CitireGraf();
        SortareTopologica();
        Afisare();
        return 0;
    }
