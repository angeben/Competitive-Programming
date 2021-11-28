#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

pair<int,int> bfs(int s, vector<int> dist, vector<bool> visited, const vector<vector<int>> & g) {
	pair<int, int> p = { 0,0 };
	int prof = 1;
	queue<int> q;
	dist[s] = 0; visited[s] = true;
	for (int w : g[s])
		if (!visited[w]) {
			dist[w] = dist[s] + 1;
			visited[w] = 1;
			q.push(w);
		}
	while (!q.empty()) {
		int t = q.size();
		if (t > p.first) {
			p.first = t;
			p.second = prof;
		}
		while (t--) {
			int v = q.front(); q.pop();
			for (int w : g[v])
				if (!visited[w]) {
					dist[w] = dist[v] + 1;
					visited[w] = 1;
					q.push(w);
				}
		}
		++prof;
	}
	return p;
}

void rC() {
	int e;
	cin >> e;
	vector<vector<int>> g(e);
	int n, aux;
	for (int i = 0; i < e; ++i) {
		cin >> n;
		for (int j = 0; j < n; ++j) {
			cin >> aux;
			g[i].push_back(aux);
		}
	}
	int t, s;
	cin >> t;
	vector<int> dist(e);
	vector<bool> visited(e);
	for (int i = 0; i < t; ++i) {
		cin >> s;
		pair<int,int> p = bfs(s, dist, visited, g);
		if (p.first == 0) cout << "0\n";
		else cout << p.first << " " << p.second << "\n";
	}
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	std::ofstream out("salida.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	rC();

#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}