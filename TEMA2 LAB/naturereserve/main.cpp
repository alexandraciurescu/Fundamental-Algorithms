/// Conectarea cu cost minim a nodurilor la mai multe  surse:
///     https://open.kattis.com/problems/naturereserve

///
///   t - numarul de teste
///   Pentru un test:
///   n - numar statii (noduri)
///   m - numarul de muchii
///   L - cost program
///   k - numar de statii initiale
///   x1, x2, .... xk - statiile initiale

///   Vom utiliza
///      - un container set din STL care va memora initial in ordine crescatoare dupa cost statiile conectate initial
///      - cat timp mai sunt elemente in set
///             - extragem primul element (nodul care se conecteaza cu cost minim)
///             - incercam sa optimizam costul de conectare al vecinilor sai folosind nodul selectat
///

#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e4;
int d[NMAX + 1];  ///d[i]=distanta minima de la nodul i la nodurile deja selectate in APM
bool vis[NMAX + 1];
vector<pair<int, int>> G[NMAX + 1];

int main()
{
    int t;
    cin >> t;
    while(t--)  /// pentru fiecare dintre cele n teste
    {
        int n, m, L, k;
        cin >> n >> m >> L >> k; /// citim datele de intrare
        set<pair<int, int>> s;     /// initializari

        for(int i = 1; i <= n; i++)
        {
            d[i] = 1e9;
            vis[i] = 0;
        }
        for(int i = 1; i <= k; i++)
        {
            int x;
            cin >> x;                  /// statiile initiale
            d[x] = 0;                  /// costul de conectare este 0
            s.insert({0, x});          /// le adaugam la containerul set
        }
        for(int i = 1; i <= m; i++)    /// citirea muchiilor si a costului asociat
        {
            int x, y, c;
            cin >> x >> y >> c;
            G[x].push_back({y, c});    /// construim listele de adiacenta - graf neorientat
            G[y].push_back({x, c});
        }
        long long sol = 0;
        while(!s.empty())    /// cat timp mai sunt elemente in container
        {
            auto it = s.begin();  /// extragem primul element (cu cost minim de conectare)
            s.erase(it);
            int cost = (*it).first;    /// cost = costul de conectare
            int node = (*it).second;   /// node = statia

            if(vis[node])  {continue;}

            vis[node] = 1;           /// marcam nodul ca vizitat (nu se va putea conecta cu cost mai mic)
            sol += 1LL * cost;       /// adaugam costul muchiei cu care se coneteaza nodul

            for(auto next : G[node]) /// parcurgem lista de adiacenta a acestuia
            {
                if(d[next.first] > next.second)   /// daca costul de conectare al unui vecin este mai mare
                {                                 /// decat daca s-ar conecta cu nodul node
                    d[next.first] = next.second;  /// il legam de acesta
                    s.insert({d[next.first], next.first}); /// il adaugam la set ca sa ne folosim de noul cost
                }                                          /// si sa optimizam celelalte costuri
            }
        }
        for(int i = 1; i <= n; i++)
        {
            G[i].clear();
        }
        sol += 1LL * (n - k) * L;
        cout << sol << '\n';
    }
    return 0;
}

/// Date de intrare
/*
1
4 6 10 1
3
1 2 4
1 3 8
1 4 1
2 3 2
2 4 5
3 4 20
*/
