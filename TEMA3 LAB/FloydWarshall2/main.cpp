#include <bits/stdc++.h>
using namespace std;
///FLOYD WARSHALL PCTB

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

int Raza()
{
    int i,j,vmin=1e9,vmax;
    for(i=1; i<=n; i++)
      {vmax=-1e9;
       for(j=1; j<=n; j++)
        if(i!=j && D[i][j]!=oo)
          vmax=max(vmax,D[i][j]);
       if(vmax!=-1e9) vmin=min(vmin,vmax);
      }
  return vmin;
}

int Diametru()
{
    int i,j,Dia=-1e9,vmax;
    for(i=1; i<=n; i++)
      {vmax=-1e9;
       for(j=1; j<=n; j++)
        if(i!=j && D[i][j]!=oo)
          vmax=max(vmax,D[i][j]);
       if(vmax!=-1e9) Dia=max(Dia,vmax);
      }
  return Dia;
}

void Centru()
{
    int i,j,Dia=1e9,vmax;
    int r=Raza();
    for(i=1; i<=n; i++)
      {vmax=-1e9;
       for(j=1; j<=n; j++)
        if(i!=j && D[i][j]!=oo)
         vmax=max(vmax,D[i][j]);
       if(vmax==r) fout<<i<<" ";
      }
}

void Drum(int x, int y)
{
    if(y!=x) Drum(x,P[x][y]);
    fout<<y<<" ";
}

void LantDiametral()
{
    int dia=Diametru();
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
           if(D[i][j]==dia)
             {Drum(i,j); return;}
}


int main()
{
    Citire();
    FloydWarshall();
    fout<<"Raza: "<<Raza()<<"\n";
    fout<<"Centru: "; Centru(); fout<<"\n";
    fout<<"Diametru: "<<Diametru()<<"\n";
    fout<<"Lant diametral: "; LantDiametral();

    return 0;
}
