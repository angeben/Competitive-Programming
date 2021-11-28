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

void resolver(const vvi& g, int e) {
	vector<int> vis(g.size(), -1);
	queue<int> q;
	bool ok = true;
	int guardias = 0;
	for (int ver = 0; ver < g.size() && ok; ++ver) { // Varias componenetes conexas
		int guardiaCC = 1, tam = 1;
		if (vis[ver] == -1) {
			q.push(ver);
			vis[ver] = 0; // Colocamos un guardia
			while (!q.empty() && ok) {
				int u = q.front(); q.pop();
				for (int v : g[u]) {
					if (vis[v] == -1) { // No tiene guardia asignado ni esta vigilado
						vis[v] = 1 - vis[u]; // Lo vigilamos
						if (vis[v] == 0) ++guardiaCC;
						++tam;
						q.push(v);
					}
					else if (vis[v] == vis[u]) // Conflicto entre guardias
						ok = false;
				}
			}
			if (tam - guardiaCC != 0 && tam - guardiaCC < guardiaCC)
				guardiaCC = tam - guardiaCC;
			guardias += guardiaCC;
		}
	}
	if (ok) cout << guardias << "\n";
	else cout << "-1\n";
}

void resuelveCaso() {
	int v, e;
	cin >> v >> e;
	vvi g(v);
	int u, w;
	for (int i = 0; i < e; ++i) {
		cin >> u >> w;
		g[u].push_back(w);
		g[w].push_back(u);
	}
	resolver(g, e);
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
	for(int i = 0; i < t; ++i) resuelveCaso();

#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}