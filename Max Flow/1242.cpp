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
int caso = 1;



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

	vvi mat(n+2, vector<int>(n+2, 0));
	vvi lista(n+2);

	int u, v;
	for (int i = 0; i < m; ++i) {
		cin >> u >> v;
		mat[u - 1][v - 1] += 1;
		mat[v - 1][u - 1] += 1;
		lista[u - 1].push_back(v - 1);
		lista[v - 1].push_back(u - 1);
	}

	int s, t;
	cin >> s >> t;
	

	mat[s - 1][n] = 2;
	mat[n][s - 1] = 2;
	lista[s - 1].push_back(n);
	lista[n].push_back(s - 1);
	mat[t - 1][n+1] = 2;
	mat[n+1][t-1] = 2;
	lista[t - 1].push_back(n + 1);
	lista[n + 1].push_back(t - 1);

	//ED
	s = n;
	t = n + 1;
	int flow = 0;
	int ret = 0;
	vector<bool> visited(n+2, false);
	vi parent(n+2);
	do {
		flow = sendFlow(s, t, visited, parent, mat, lista);
		ret += flow;
	} while (flow > 0);

	if (ret == 2) cout << "Case " << caso << ": YES\n";
	else cout << "Case " << caso << ": NO\n";

	caso++;
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

