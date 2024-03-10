#include <bits/stdc++.h>
using namespace std;

ifstream fin("grafpond.in");
ofstream fout ("grafpond.out");

const int NMAX=100;
const int oo=1e9;

int n,m;
int C[NMAX][NMAX];
int D[NMAX][NMAX];
int P[NMAX][NMAX];

void Citire()
{fin>>n>>m;
 for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
      if(i!=j) C[i][j]=oo;
 for(int i=1; i<=m; i++)
   {int x,y,c;
    fin>>x>>y>>c;
    C[x][y]=c;
   }
}

void FloydWarshall()
{for(int i=1; i<=n; i++)
  for(int j=1; j<=n; j++)
    {D[i][j]=C[i][j];
     if(C[i][j]<oo) P[i][j]=i;
    }

  for(int k=1; k<=n; k++)
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
           if(D[i][j]>D[i][k]+D[k][j])
                {D[i][j]=D[i][k]+D[k][j];
                 P[i][j]=P[k][j];
                }
}

int TestCiclu()
{ for(int i=1; i<=n; i++)
    if(D[i][i]<0) return i;
 return 0;
}

void Afisare1()
{
    for(int i=1; i<=n; i++)
       {for(int j=1; j<=n; j++)
          if(D[i][j]==oo)
            fout<<0<<" ";
          else fout<<D[i][j]<<" ";
        fout<<"\n";
       }
}

void Drum(int x, int y)
{
    if(x!=P[x][y]) Drum(x,P[x][y]);
    fout<<y<<" ";


}

void Afisare2(int x)
{
    fout<<"Circuit de cost negativ: "<<"\n";
    Drum(x,x);
}

int main()
{
    Citire();
    FloydWarshall();
    int x=TestCiclu();
    if(x==0) Afisare1();
    else Afisare2(x);
    return 0;
}
