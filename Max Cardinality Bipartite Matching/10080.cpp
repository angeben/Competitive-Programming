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
int N, M;

int aug(int l, const vector<vector<int>> & grafo, vector<int> & vis, vector<int> & match) {
	if (vis[l]) return 0;
	vis[l] = 1;
	for(auto r: grafo[l])
		if (match[r] == -1 || aug(match[r], grafo, vis, match)) {
			match[r] = l;
			return 1;
		}
	return 0;
}

int berge_mcbm(const vector<vector<int>> & grafo, vector<int> & vis, vector<int> & match) {
	int mcbm = 0;
	match.assign(N+M, -1);
	for (int l = 0; l < N; l++) {
		vis.assign(N,0);
		mcbm += aug(l, grafo, vis, match);
	}
	return mcbm;
}

double dist(pair<double, double> a, pair<double, double> b) {
	double x = b.first - a.first;
	double y = b.second - a.second;
	return sqrt(x*x + y * y);
}

bool resolverCaso() {
	int s, v;
	cin >> N >> M >> s >> v;
	if (!cin) return false;
	// Gophers
	vector<pair<double, double>> g(N);
	for (int i = 0; i < N; ++i)
		cin >> g[i].first >> g[i].second;
	// Holes
	vector<pair<double, double>> h(M);
	for (int i = 0; i < M; ++i)
		cin >> h[i].first >> h[i].second;
	// Generamos aristas
	vector<vector<int>> grafo(N);
	vector<int> match, vis;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j) {
			double d = dist(g[i], h[j]);
			double u = d / v;
			if (d / v <= s) {
				grafo[i].push_back(j);
			}
		}

	int card = berge_mcbm(grafo, vis, match);
	cout << N - card << '\n';
	return true;
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	std::ofstream out("salida.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	while (resolverCaso());

#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}