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
int INF = 1000000000;

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
		// Buscamos capacidad más pequeña en el camino
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

bool resuelveCaso() {
	int n;
	cin >> n;
	if (!cin) return false;
	// tamaño 2*n + 2 (2*n por duplicar cada vertice y +2 por las dos ciudades)
	// 0 es el origen y 2*n + 1 el destino
	vvi mat(2*n + 2, vector<int>(2*n + 2, 0));
	vvi lista(2*n + 2);
	// vertice i: dividido en (2*i - 1) -> 2*i con el valor de arista de la capacidad del regulador
	int cap, links;
	for (int i = 1; i <= n; ++i) {
		cin >> cap;
		mat[2*i - 1][2*i] += cap;
		lista[2*i - 1].push_back(2*i);
		lista[2*i].push_back(2*i - 1);
	}
	cin >> links;
	int i, j;
	// No olvidar aristas inversas para el algoritmo
	for (int k = 0; k < links; ++k) {
		cin >> i >> j >> cap;
		mat[2*i][2*j - 1] += cap;
		lista[2*i].push_back(2*j - 1);
		lista[2*j - 1].push_back(2*i);
	}
	int b, d, v;
	cin >> b >> d;
	// enlaces a origen y destino
	for (int i = 0; i < b; ++i) {
		cin >> v;
		mat[0][2*v-1] = INF;
		lista[0].push_back(2*v - 1);
		lista[2*v - 1].push_back(0);
	}
	for (int i = 0; i < d; ++i) {
		cin >> v;
		mat[2*v][2*n + 1] = INF;
		lista[2*v].push_back(2*n + 1);
		lista[2*n + 1].push_back(2*v);
	}

	// Edmonds-Karp
	int flow = 0;
	int ret = 0;
	vector<bool> visited(2*n + 2, false);
	vi parent(2*n + 2);
	do {
		flow = sendFlow(0, 2*n + 1, visited, parent, mat, lista);
		ret += flow;
	} while (flow > 0);

	cout << ret << "\n";
	return true;
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	std::ofstream out("salida.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	while (resuelveCaso());

#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}