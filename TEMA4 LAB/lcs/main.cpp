#include <bits/stdc++.h>
using namespace std;
#define N 1005

ifstream fin("lcs.in");
ofstream fout("lcs.out");

int a[N][N],n,m;
char s[N],t[N],sol[N];
int main()
{
    fin>>(s+1);
    fin>>(t+1);  ///sirurile vor fi indexate de la 1
    int i,j,k=0;
    n=strlen(s+1);
    m=strlen(t+1);
    for (i=1; i<=n; i++)
        for (j=1; j<=m; j++)
            if (s[i]==t[j]) a[i][j]=a[i-1][j-1]+1;
            else a[i][j]=max(a[i-1][j],a[i][j-1]);
    i=n; j=m;
    while (i>=1 && j>=1)
    {
        if (s[i]==t[j]) sol[++k]=s[i], i--, j--;
        else if (a[i-1][j]<a[i][j-1]) j--;
             else i--;
    }
    for (i=k; i>=1; i--)
        fout<<sol[i];
    return 0;
}
