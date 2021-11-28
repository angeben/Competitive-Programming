#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <sstream>

using namespace std;
using namespace std;
using vvi = vector<vector<int>>;
using vi = vector<int>;
int INF = 1000000;



void bfs(int s, int t, vector<bool>& visited, vi& parent, vvi& mat, vvi& lista) {
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

int sendFlow(int s, int t, vector<bool>& visited, vi& parent, vvi& mat, vvi& lista) {
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

bool resuelveCaso() {

	int n, m;
	cin >> n >> m;
	if (n == 0 && m == 0) return false;

	vvi mat(n, vector<int>(n, 0));
	vvi lista(n);

	int u, v, cap;
	for (int i = 0; i < m; ++i) {
		cin >> u >> v >> cap;
		mat[u - 1][v - 1] += cap;
		mat[v - 1][u - 1] += cap;
		lista[u - 1].push_back(v - 1);
		lista[v - 1].push_back(u - 1);
	}

	int s = 0;
	int t = 1;

	//ED
	int flow = 0;
	int ret = 0;
	vector<bool> visited(n, false);
	vi parent(n);
	do {
		flow = sendFlow(s, t, visited, parent, mat, lista);
		ret += flow;
	} while (flow > 0);

	queue<pair<int, int>> sol;
	for (int i = 0; i < n; ++i) {
		if (visited[i]) {
			for (int x : lista[i]) {
				if (!visited[x] && mat[i][x] == 0) sol.push({ i,x });
			}
		}
	}

	while (!sol.empty()) {
		pair<int, int> p = sol.front(); sol.pop();
		cout << p.first + 1 << ' ' << p.second + 1 << '\n';
	}
	cout << '\n';

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

