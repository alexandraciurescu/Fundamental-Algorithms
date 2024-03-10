#include <iostream>
//3
using namespace std;

///Solutie: Algoritmul Fill
///Complexitate: O(n*m)

char a[1001][1001];
int n,m;

void Citire()
{ int i,j;
  cin>>n>>m;
  for(i=1; i<=n; i++)
    for(j=1; j<=m; j++)
       cin>>a[i][j];
}


void Fill(int l, int c)
{a[l][c]='#';
 if(l>1 && a[l-1][c]=='.') Fill(l-1,c);
 if(l<n && a[l+1][c]=='.') Fill(l+1,c);
 if(c>1 && a[l][c-1]=='.') Fill(l,c-1);
 if(c<m && a[l][c+1]=='.') Fill(l,c+1);
}


int NrCamere()
{int i,j,ct=0; ///ct=nr camere
 for(i=1; i<=n; i++)
  for(j=1; j<=m; j++)
      if(a[i][j]=='.')
         {ct++; Fill(i,j);} ///apelam Fill pentru a marca cu # intreaga camera (ca sa nu o mai
                            ///numaram inca o data)
  return ct;
}

int main()
{
    Citire();
    cout<<NrCamere();
    return 0;
}
