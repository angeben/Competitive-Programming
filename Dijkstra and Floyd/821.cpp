#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <utility>
#include <queue>
#include <unordered_map>

struct par {
	int first;
	int second;
};
using namespace std;
using matriz = vector<vector<int>>;
int INF = 100000;

float myround(float var) {
	float value = (int)(var * 1000 + .5);
	return (float)value / 1000;
}

bool resuelveCaso(int caso) {
	int u, v;
	cin >> u >> v;
	if (u == 0 && v == 0) return false;
	unordered_map<int, int> m;
	m[u] = 0; m[v] = 1;
	int cont = 2;
	vector<par> e;
	e.push_back({0,1});
	int nu, nv;
	cin >> u >> v;
	while (u != 0 && v != 0) {
		if (m.count(u) == 1) nu = m[u];
		else {
			m[u] = cont;
			nu = cont;
			++cont;
		}
		if (m.count(v) == 1) nv = m[v];
		else {
			m[v] = cont;
			nv = cont;
			++cont;
		}
		e.push_back({ nu, nv });
		cin >> u >> v;
	}

	matriz mat(cont, vector<int>(cont, INF));
	for (int i = 0; i < e.size(); ++i) {
		mat[e[i].first][e[i].second] = 1;
	}

	for (int k = 0; k < cont; k++)
		for (int i = 0; i < cont; i++)
			for (int j = 0; j < cont; j++)
				if (mat[i][k] + mat[k][j] < mat[i][j])
					mat[i][j] = mat[i][k] + mat[k][j];
	
	double sum = 0; // USAR DOUBLE
	for (int i = 0; i < cont; i++)
		for (int j = 0; j < cont; j++)
			if (i != j)
				sum += mat[i][j];

	double med = sum / (cont*(cont - 1));
	cout << "Case " << caso << ": average length between pages = ";
	cout << setprecision(3) << fixed << med << " clicks\n";
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