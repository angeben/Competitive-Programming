#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>

using namespace std;
int MAX_V;
int hora;

struct par {
	int first, second;

};

bool operator <(par const a, par const b) {
	return (a.first > b.first) || (a.first == b.first && a.second > b.second);
}

void dfs(int u, int uParent, vector<vector<int>> adj, priority_queue<par>& q, vector<int>& horaVertice, vector<int>& alcanzable) {
	horaVertice[u] = alcanzable[u] = hora; hora++;
	for (int i = 0; i < adj[u].size(); ++i) {
		int v = adj[u][i];
		if (v == uParent) continue; // B.E. con el padre, que ignoramos
		if (horaVertice[v] == 0) { // No visitado
			dfs(v, u, adj, q, horaVertice, alcanzable);
			if (alcanzable[v] > horaVertice[u]) {
				if (u > v) {
					q.push({ v,u });
				}
				else q.push({ u,v });
			}
			alcanzable[u] = min(alcanzable[u], alcanzable[v]);
		}
		else alcanzable[u] = min(alcanzable[u], horaVertice[v]); // B.E.
	}
}

bool resuelveCaso() {
	if (!(cin >> MAX_V)) return false;
	if (MAX_V == 0) {
		cout << "0 critical links\n\n";
		return true;
	}

	vector<vector<int>> adj(MAX_V);
	int a, b;
	int n;
	char c;
	for (int i = 0; i < MAX_V; ++i) {
		cin >> a;
		cin >> c >> n >> c;
		for (int j = 0; j < n; ++j) {
			cin >> b;
			adj[a].push_back(b);
		}
	}

	priority_queue<par> q;
	vector<int> horaVertice(MAX_V, 0);
	vector<int> alcanzable(MAX_V, 0);
	hora = 1;
	for (int i = 0; i < MAX_V; ++i) {
		if (!horaVertice[i])
			dfs(i, -1, adj, q, horaVertice, alcanzable);
	}

	cout << q.size() << " critical links\n";
	while (!q.empty()) {
		cout << q.top().first << " - " << q.top().second << '\n';
		q.pop();
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

