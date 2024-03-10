#include <bits/stdc++.h>

using namespace std;

///Complexitate: O(M*2^N)

ifstream fin("graf.in");
ofstream fout("graf.out");

const int MAXN = 20;
const int MAXX = 262150;
const int INF = 100000000;

int N, M, Sol;
int Cost[MAXN][MAXN];
int C[MAXX][MAXN];
vector <int> G[MAXN];

int main()
{


	fin >> N >> M;

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j) Cost[i][j] = INF;

	for (int i = 1; i <= M; ++i)
	{
		int x, y;
		fin >> x >> y;
		G[y].push_back(x);
		fin >> Cost[x][y];
	}

    ///matrice cu 2^N linii si N coloane
    ///C[i][j] = costul minim al unui drum ce viziteaza o singura data fiecare nod din submultimea
    ///i sau infinit daca nu exista un astfel de drum
	for (int i = 0; i < 1 << N; ++i)   ///1<<N -> 2^N
		for (int j = 0; j < N; ++j) C[i][j] = INF;
    ///in C[i][j] i este o masca de biti ce codifica o submultime de noduri ale grafului
    ///bitul k este setat la 1 <=> k apartine submultimii

	C[1][0] = 0;


	for (int i = 0; i < 1 << N; ++i)
		for (int j = 0; j < N; ++j)
			if (i & (1<<j)) ///daca nodul j apartine submultimii i (bitul j e setat la 1)
                for(auto k: G[j])
                  if(i & (1<<k)) ///daca si nodul k apartine submultimii
                      C[i][j]= min(C[i][j], C[i^(1<<j)][k]+ Cost[k][j]);
                      ///i^(1<<j) codifca submultimea obtinuta eliminandu-l pe j din submult i

	Sol = INF;
	for(auto i: G[0])
		Sol = min(Sol, C[(1<<N) - 1][ i ] + Cost[i][0]);

	if (Sol == INF) fout << "Nu exista solutie" << endl;
	else fout << Sol << endl;

	return 0;
}
