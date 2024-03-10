#include <bits/stdc++.h>
//5
using namespace std;

///Un nod este punct de articulatie (critic) <=> prin eliminarea
///acestuia se pierde proprietatea de conexitate.

///Det. pct. de articulatie are la baza o parcurgere DFS(1) in care se retin
///mai multe informatii despre fiecare nod care vor conduce in final la
///determinarea punctelor critice.

///Pentru fiecare nod se vor determina
/// - d[x] - nivelul nodului x in parcurgerea DFS
/// - low[x] - numarul minim al nivelului care poate fi atins din nodul x folosind descendentii
   ///sai si cel mult o muchie de intoarcere.

///Obs 1. Daca dintr-un nod x nu se poate ajunge pe un nivel strict mai mic
       ///decat al tatalui sau atunci TATAL lui x este punct de articulatie
    ///2. Radacina (nodul 1) este punct de articulatie daca are mai mult de un singur
       /// descendent direct.

///Complexitate: O(n+m)

const int NMAX = 1e5;
vector<int> G[NMAX + 1];
int d[NMAX + 1]; ///d[x]=nivelul nodului x in arborele DFS
int low[NMAX + 1]; ///low[x]=nr minim al nivelului care
///poate fi atins din nodul x folosind descendentii sai si cel mult
///o muchie de intoarcere
int cnt; ///nr de descendenti ai radacinii
int sol; ///nr de puncte critice
int art[NMAX + 1]; ///art[x]=1 daca x e punct critic
int h; ///inaltimea arb DFS
int vis[NMAX + 1];
int r; ///radacina arborelui

void dfs(int x, int p) ///p=tatal lui x
{
    vis[x] = 1;
    h++;
    d[x] = low[x] = h;
    for(auto next : G[x])
         if(!vis[next])
           {dfs(next, x);
            low[x] = min(low[x], low[next]);
            if(x == r)
                cnt++; ///calculam nr de descendenti directi ai radacinii
            else if(low[next] >= d[x]) art[x] = 1;
           }

         else ///muchie de intoarcere de la x la next
            if(next != p)
                low[x] = min(low[x], d[next]);
}

int main() {
    while(true) {
        int n, m;
        cin >> n >> m;
        if(n == 0 && m == 0) {
            break;
        }
        while(m--) {
            int x, y;
            cin >> x >> y;
            G[x].push_back(y);
            G[y].push_back(x);
        }
        r = 1;
        sol = 0;
        cnt = 0;
        h = 0;
        dfs(r, 0);
        if(cnt >= 2) {
            art[1] = 1;  ///Radacina (nodul 1) este punct de articulatie daca are
                          ///mai mult de un singur descendent direct.
        }
        for(int i = 1; i <= n; i++) {
            if(art[i] == 1) {
                sol++;
            }
        }
        for(int i = 1; i <= n; i++) {
            G[i].clear();
            art[i] = vis[i] = d[i] = low[i] = 0;
        }
        cout << sol << '\n';
    }
    return 0;
}
