#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

//0: no, 1:tocado, 2:hundido
void dfs(int u, vector<vector<int>>& adj, vector<int>& estado, bool & bucle, bool & terminado) {
	estado[u] = 1;
	for (int i = 0; i < adj[u].size(); ++i) {
		int v = adj[u][i];
		if (v == adj.size()) {
			terminado = true;
			continue;
		}
		if (estado[v] == 1) {
			bucle = true;
		}
		else if ((estado[v] == 0)) {
			dfs(v, adj, estado, bucle, terminado);
		}
	}
	estado[u] = 2;
}

void resuelveCaso() {
	int L, w;
	cin >> L;
	vector<vector<int>> adj(L);
	char c;
	for (int i = 0; i < L; ++i) {
		cin >> c;
		if (c != 'A') {
			cin >> w;
			if (c == 'C') adj[i] = { w-1, i + 1 };
			else adj[i] = { w-1};
		}
		else adj[i] = {i + 1};
	}
	vector<int> estado(L, 0);
	bool bucle = false;
	bool terminado = false;
	dfs(0, adj, estado, bucle,terminado);
	if (terminado && bucle) cout << "SOMETIMES\n";
	else if (terminado && !bucle) cout << "ALWAYS\n";
	else if (!terminado) cout << "NEVER\n";
}


int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	std::ofstream out("salida.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int c;
	cin >> c;
	while (c--) {
		resuelveCaso();
	}


#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}

