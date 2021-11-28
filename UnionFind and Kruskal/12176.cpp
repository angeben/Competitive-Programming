#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int INF = 10000000;
int caso = 0;
using arista = pair<int, pair<int, int>>;

struct UFDS {
	vector<int> p;
	int numSets;
	UFDS(int n) : p(n, 0), numSets(n) {
		for (int i = 0; i < n; ++i) p[i] = i;
	}
	int find(int x) {
		return (p[x] == x) ? x : p[x] = find(p[x]);
	}
	void merge(int x, int y) {
		int i = find(x), j = find(y);
		if (i == j) return;
		p[i] = j;
		--numSets;
	}
};

void bfs(int s, int t , const vector<vector<int>> & adjList, const vector<vector<int>> & mat) {
	queue<int> q;
	vector<int> dist(adjList.size(), -1);
	vector<bool> visited(adjList.size(), false);
	visited[s] = true;
	q.push(s);
	while (!q.empty()) {
		int v = q.front(); q.pop();
		for (int w : adjList[v])
			if (!visited[w]) {
				dist[w] = v;
				visited[w] = 1;
				q.push(w);
			}
	}
	// Reconstruir el camino para obtener la mayor arista
	int aux = t;
	int max = 0;
	while (aux != s) {
		int arista = mat[aux][dist[aux]];
		if (arista > max)
			max = arista;
		aux = dist[aux];
	}
	cout << max << '\n';
}

void rC() {
	++caso;
	cout << "Case " << caso << '\n';
	int n, r;
	cin >> n >> r;
	int a, b, l;
	vector<arista> aristas;
	for (int i = 0; i < r; ++i) {
		cin >> a >> b >> l;
		aristas.push_back({ l,{ a - 1, b - 1} });
	}

	UFDS uf(n);
	sort(aristas.begin(), aristas.end());
	// Kruskal
	double coste = 0;
	vector<arista> sol;
	for (arista a : aristas) {
		if (uf.find(a.second.first) != uf.find(a.second.second)) {
			uf.merge(a.second.first, a.second.second);
			coste += a.first;
			sol.push_back(a);
			if (uf.numSets == 1) break;
		}
	}

	// Nuevo grafo con el arbol de recubrimiento minimo
	vector<vector<int>> adjList(n);
	vector<vector<int>> mat(n, vector<int>(n, INF));
	for (int i = 0; i < sol.size(); ++i) {
		adjList[sol[i].second.first].push_back(sol[i].second.second);
		adjList[sol[i].second.second].push_back(sol[i].second.first);
		mat[sol[i].second.first][sol[i].second.second] = sol[i].first;
		mat[sol[i].second.second][sol[i].second.first] = sol[i].first;
	}

	int q, k, t;
	cin >> q;
	for (int i = 0; i < q; ++i) {
		cin >> k >> t;
		bfs(k - 1, t - 1, adjList, mat);
	}
	cout << "\n";
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	std::ofstream out("salida.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int t;
	cin >> t;
	while(t--) rC();

#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}