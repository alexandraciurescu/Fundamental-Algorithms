///KRUSKAL - O(m*log n) - structuri de multimi disjuncte

#include <bits/stdc++.h>
using namespace std;

///calculam dist Lev
///generam graf complet


const int N=10001;
const int M=N*(N-1)/2;

ifstream fin ("cuvinte.in");
ofstream fout ("cuvinte.out");

struct muchie
{   int x,y,cost;
    bool selectat;
};

int k; ///nr de clase
char cuv[N][21]; ///vectorul de cuvinte
int clasa[N]; ///clasa[i]=clasa din care face parte cuvantul i


int distL[N][N]; ///distL[i][j]=distanta Levenshtein dintre cuvintele i si j

vector <muchie> G;  ///reprez grafului cu vector de muchii
int n,m;


int tata[N]; ///memorarea comp conexe folosind vectorul de tati
int h[N]; ///inaltimea fiecarui arbore



void Citire()
{char s[21];
 cout<<"Dati numarul de clase k= ";
 cin>>k;
 while(fin>>s)
   {n++;
    strcpy(cuv[n],s);
   }
}

void GenerareGrafComplet()
{ m = n*(n-1)/2;
  for(int i=1; i<n; i++)
    for(int j=i+1; j<=n; j++)
      {muchie e;
       e.x=i;
       e.y=j;
       e.cost=distL[i][j];
       G.push_back(e);
      }
}

int CalculDistLevenshtein(char x[], char y[])
{ int lx=strlen(x), ly=strlen(y);
  int c[lx+1][ly+1];
  for(int i=0; i<=lx; i++)
    for(int j=0; j<=ly; j++)
      if(i==0) c[i][j]=j;
      else if(j==0) c[i][j]=i;
           else if (x[i-1]==y[j-1]) c[i][j]=c[i-1][j-1];
                else c[i][j]=1+min(c[i-1][j],min(c[i-1][j-1],c[i][j-1]));
  return c[lx][ly];

}

void CompletareDistLevenshtein()
{for(int i=1; i<n; i++)
  for(int j=i+1; j<=n; j++)
    distL[i][j]=distL[j][i]=CalculDistLevenshtein(cuv[i],cuv[j]);
}

bool cmp(muchie a, muchie b)
{
    return a.cost<b.cost;
}

///initial se pleaca de la n componente conexe, fiecare reprezentata de un nod
void Initializare()
{ for(int i=1; i<=n; i++)
    tata[i]=h[i]=0;
}


///returneaza radacina arborelui din care face parte nodul x cu compresia caii
int Reprez(int x)
{
    if(tata[x]==0) return x;
    tata[x]=Reprez(tata[x]);
    return tata[x];
}

/// radacina unui arbore devine fiu al radacinii celuilalt arbore
/// arborele cu inaltime mai mica devine subarbore al arborelui cu inaltime mai mare
/// daca cei doi arbori au inaltime egala dupa reuniune inaltimea arborelui creste cu 1
void Reuneste(int x, int y)
{
    int rx=Reprez(x);
    int ry=Reprez(y);
    if (h[rx]>h[ry]) tata[ry]=rx;
    else
        { tata[rx]=ry;
          if(h[rx]==h[ry]) h[rx]=h[rx]+1;
        }
}

void Kruskal()
{   int ct=0; ///cate muchii am selectat in apm
    Initializare();
    for(int i=0; i<m && ct<n-k; i++)
      { int rx=Reprez(G[i].x);
        int ry=Reprez(G[i].y);
        if(rx!=ry)
          {ct++;
           G[i].selectat=1;
           Reuneste(G[i].x,G[i].y);
          }

      }
}

void DFS(int x,int ct)
{   clasa[x]=ct;
    fout<<cuv[x]<<" ";
    for(int i=1; i<=n; i++)
        if(tata[i]==x)
          DFS(i,ct);
}

int GradDeSeparare()
{   int gmin=1e9;
    for(int i=1; i<=n; i++)
        for(int j=i+1; j<=n; j++)
           if(clasa[i]!=clasa[j])
              gmin=min(gmin,distL[i][j]);
    return gmin;
}

void Afisare()
{   int ct=0; ///pt determinarea claselor
    for(int i=1; i<=n ; i++)
      if(tata[i]==0)
        {ct++;
         DFS(i,ct);
         fout<<"\n";
        }
    fout<<GradDeSeparare();

}

int main()
{
    Citire();
    CompletareDistLevenshtein();
    GenerareGrafComplet();
    sort(G.begin(),G.end(),cmp);
    Kruskal();
    Afisare();
    return 0;
}
