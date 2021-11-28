#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;
using vvi = vector<vector<int>>;
using vi = vector<int>;
int INF = 1000000;

void bfs(int s, int t, vector<bool> & visited, vi & parent, vvi & mat, vvi & lista) {
	queue<int> q;
	for (int i = 0; i < visited.size(); ++i)
		visited[i] = false;
	q.push(s);
	parent[s] = -1; visited[s] = true;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (u == t) break;
		for (int i = 0; i < lista[u].size(); ++i) {
			int v = lista[u][i];
			if (!visited[v] && (mat[u][v] > 0)) {
				parent[v] = u;
				visited[v] = true;
				q.push(v);
			}
		}
	}
}

int sendFlow(int s, int t, vector<bool> & visited, vi & parent, vvi & mat, vvi & lista) {
	// Intentamos llegar de s a t
	bfs(s, t, visited, parent, mat, lista);
	if (!visited[t])
		return 0; // No pudimos
		// Buscamos capacidad m´as peque˜na en el camino
	int flow = INF, v = t;
	while (v != s) {
		flow = min(mat[parent[v]][v], flow);
		v = parent[v];
	}
	// Mandamos flujo
	v = t;
	while (v != s) {
		mat[parent[v]][v] -= flow;
		mat[v][parent[v]] += flow; // INVERSA
		v = parent[v];
	}
	return flow;
}

bool resuelveCaso(int caso) {
	int n;
	cin >> n;
	if (n == 0) return false;

	vvi mat(n, vector<int>(n,0));
	vvi lista(n);
	int s, t, e;
	cin >> s >> t >> e;
	int u, v, cap;
	for (int i = 0; i < e; ++i) {
		cin >> u >> v >> cap;
		mat[u-1][v-1] += cap;
		mat[v-1][u-1] += cap;
		lista[u-1].push_back(v-1);
		lista[v-1].push_back(u-1);
	}

	// Edmonds-Karp
	int flow = 0;
	int ret = 0;
	vector<bool> visited(n, false);
	vi parent(n);
	do {
		flow = sendFlow(s - 1, t - 1, visited, parent, mat, lista);
		ret += flow;
	} while (flow > 0);

	cout << "Network " << caso << "\n";
	cout << "The bandwidth is " << ret << ".\n";
	return true;
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	std::ofstream out("salida.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int caso = 1;
	while (resuelveCaso(caso)) ++caso;


#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}