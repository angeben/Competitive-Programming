#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <utility>
#include <queue>
using namespace std;
using vvi = vector<vector<int>>;

void bicolor(const vvi & adj) {
	queue<int> q;
	vector<int> color(adj.size(), -1); // -1 es no visitado
	color[0] = 0;
	q.push(0);
	bool ok = true;
	while (!q.empty() && ok) {
		int u = q.front(); q.pop();
		for (int v : adj[u]) {
			if (color[v] == -1) { // No visitado: Lo pintamos del color contrario al de u
				color[v] = 1 - color[u];
				q.push(v);
			}
			else if (color[v] == color[u]) // Mismo color que adyacente
				ok = false;
		}
	}
	if (ok) cout << "BICOLORABLE.\n";
	else cout << "NOT BICOLORABLE.\n";
}

bool resuelveCaso() {
	int n, e;
	cin >> n;
	if (n == 0) return false;
	cin >> e;
	int u, v;
	vvi adj(n);
	for (int i = 0; i < e; ++i) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	bicolor(adj);
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
