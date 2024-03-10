/// Conectarea cu cost minim a nodurilor la mai multe  surse:
///   - https://www.infoarena.ro/problema/retea2

/// N - centrale
/// M - blocuri
/// Un bloc poate sa primeasca curent daca este conectat la o centrala sau la un bloc conectat la curent

/// cost legare = distanta euclidiana dintre cele 2 noduri (centrala sau bloc)
/// Care este costul  minim de conectare pentru cele n blocuri?

/// Algoritmul lui Prim - modificat
///    - Initializam vectorul d  astfel:
///         d[i] = distanta minima de la blocul i la una dintre centrale
///    - de m ori
///         - determinam costul minim de conectare al unui bloc nevizitat
///         - vizitam (conectam) blocul respectiv
///         - reactualizam distantele minime de la blocurile neconectate la cele conectate



#include <bits/stdc++.h>
using namespace std;

ifstream f("retea2.in");
ofstream g("retea2.out");

struct punct
{
    long long x, y;
};
punct c[2001], b[2001];
long long d[2001], vis[2001];

long long dist(punct a, punct b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int main()
{
    int n, m;
    f >> n >> m;
    for(int i = 1; i <= n; i++)  /// coordonatele centralelor
    {
        f >> c[i].x >> c[i].y;
    }
    for(int i = 1; i <= m; i++) /// coordonatele blocurilor
    {
        f >> b[i].x >> b[i].y;
        d[i] = 1e18;            /// pentru fiecare bloc initalizam costul cu infinit
    }

    /// Initial vom conecta fiecare bloc cu cea mai apropiata centrala
    for(int i = 1; i <= m; i++) /// pentru fiecare bloc
    {
        long long mn = 1e18;
        for(int j = 1; j <= n; j++)  /// determin cea mai apropiata centrala
        {
            mn = min(mn, dist(b[i], c[j]));
        }
        d[i] = mn;               /// si initializez costul cu distanta fata de aceasta
    }


    for(int i = 1; i <= m; i++)  /// de m ori
    {
        long long mn = 1e18;
        int pos = 0;
        for(int j = 1; j <= m; j++) /// determinam un nod nevizitat pentru care costul de conectare este minim
        {
            if(!vis[j] && d[j] < mn)
            {
                mn = d[j];
                pos = j;
            }
        }
        vis[pos] = 1;  /// marcam nodul gasit ca vizitat
        for(int j = 1; j <= m; j++) /// reactualizam costurile minim pentru celelalte noduri nevizitate folosind
        {                           /// nodul determinat anterior (pos)
            if(!vis[j] && d[j] > dist(b[pos], b[j]))
            {
                d[j] = dist(b[pos], b[j]);
            }
        }
    }
    double sol = 0;
    for(int i = 1; i <= m; i++)
    {
        sol += sqrt(d[i]);
    }
    g << fixed << setprecision(7) << sol;
    return 0;
}
