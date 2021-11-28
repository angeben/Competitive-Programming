#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <sstream>

using namespace std;

int c, d, v;
int k;

vector<vector<int>> grafo;
vector<pair<int, int>> gatos;
vector<pair<int, int>> perros;
vector<int> match, vis;

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

int aug(int l) {
	if (vis[l]) return 0;
	vis[l] = 1;
	for (auto r : grafo[l]) {
		if (match[r] == -1 || aug(match[r])) {
			match[r] = l;
			return 1;
		}
	}
	return 0;
}

int berge_mcm() {
	int mcbm = 0;
	match.assign(k, -1);
	for (int l = 0; l < grafo.size(); ++l) {
		vis.assign(grafo.size(), 0);
		mcbm += aug(l);
	}
	return mcbm;
}


void resuelveCaso() {
	cin >> c >> d >> v;
	gatos.clear();
	perros.clear();
	grafo.clear();
	string a, b;
	int x, y;
	for (int i = 0; i < v; ++i) {
		cin >> a >> b;
		bool ord = (a.at(0) == 'C');
		a.erase(0, 1);
		b.erase(0, 1);
		stringstream sa(a);
		stringstream sb(b);
		sa >> x;
		sb >> y;
		if (ord) {
			gatos.push_back({ x - 1,y - 1 });
		}
		else perros.push_back({ x - 1,y - 1 });
	}
	vector<vector<int>> graf(gatos.size());
	for (int i = 0; i < gatos.size(); ++i) {
		for (int j = 0; j < perros.size(); ++j) {
			if (gatos[i].first == perros[j].second || gatos[i].second == perros[j].first)
				graf[i].push_back(j);
		}
	}
	grafo = graf;
	k = gatos.size() + perros.size();
	cout << v - berge_mcm() << '\n';
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

