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
using arista = pair<double, pair<int, int>>;

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

double dist(pair<int,int> a, pair<int,int> b) {
	int x = b.first - a.first;
	int y = b.second - a.second;
	return sqrt(x*x + y*y);
}

void resolverCaso() {
	int s, p;
	cin >> s >> p;
	vector<pair<int, int>> v(p);
	for (int i = 0; i < p; ++i)
		cin >> v[i].first >> v[i].second;
	// Generamos aristas
	vector<arista> aristas;
	for (int i = 0; i < p; ++i)
		for (int j = i + 1; j < p; ++j) {
			arista e;
			e.first = dist(v[i], v[j]);
			e.second.first = i;
			e.second.second = j;
			aristas.push_back(e);
		}

	UFDS uf(p);
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
	int pos = sol.size() - s;
	cout << setprecision(2) << fixed << sol[pos].first << "\n";
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	std::ofstream out("salida.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int T;
	cin >> T;
	while (T != 0) {
		resolverCaso();
		T--;
	}

#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}