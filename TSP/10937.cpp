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
using mapa = vector<vector<char>>;
using ii = pair<int, int>;
using vii = vector<pair<int, int>>;
using vvi = vector<vector<int>>;

int INF = 1000000000;
int h, w;
int df[] = { 1,0,-1,0 }, dc[] = { 0,1,0,-1 };
int df8[] = { 1,1,0,-1,-1,-1,0,1 };
int dc8[] = { 0,1,1,1,0,-1,-1,-1 };

bool ok(int i, int j) {
	return 0 <= i && i < h && 0 <= j && j < w;
}

bool seguro(int i, int j, const mapa & m) {
	bool safe = true;
	for (int k = 0; k < 8 && safe; ++k) {
		int ni = i + df8[k];
		int nj = j + dc8[k];
		if (ok(ni, nj)) safe = safe && (m[ni][nj] != '*');
	}
	return safe;
}

vii adjList(ii v, const mapa & m) {
	vii l;
	for (int i = 0; i < 4; ++i) {
		int ni = v.first + df[i], nj = v.second + dc[i];
		if (ok(ni, nj) && seguro(ni, nj, m) && m[ni][nj] != '~' && m[ni][nj] != '#' && m[ni][nj] != '*')
			l.push_back({ni,nj});
	}
	return l;
}

int bfs(ii s, ii e, const mapa & m) {
	vvi distBFS(m.size(), vector<int>(m[0].size(), INF));
	vvi visited(m.size(), vector<int>(m[0].size(), 0));
	queue<ii> q;
	distBFS[s.first][s.second] = 0; visited[s.first][s.second] = 1;
	q.push(s);
	bool posible = true;
	while (!q.empty() && posible) {
		ii v = q.front(); q.pop();
		posible = posible && seguro(v.first, v.second, m);
		for (ii w : adjList(v, m)) {
			if (!visited[w.first][w.second]) {
				distBFS[w.first][w.second] = distBFS[v.first][v.second] + 1;
				visited[w.first][w.second] = 1;
				q.push(w);
				if (w == e) return distBFS[e.first][e.second];
			}
		}			
	}
	return INF;
}

int tsp(int pos, int visitados, vvi & memo, const vvi & dist) {
	if (visitados == (1 << memo.size()) - 1) // hemos visitado ya todos los vértices
		return dist[pos][0]; // volvemos al origen
	if (memo[pos][visitados] != -1)
		return memo[pos][visitados];
	int res = 1000000000; // INF
	for (int i = 1; i < memo.size(); ++i)
		if (!(visitados & (1 << i))) // no hemos visitado vértice i
			res = min(res, dist[pos][i] + tsp(i, visitados | (1 << i), memo, dist));
	return memo[pos][visitados] = res;
}

bool resuelveCaso() {
	cin >> h >> w;
	if (h == 0 && w == 0) return false;
	mapa m(h, vector<char>(w, ' '));
	vii posiciones;
	ii ini;
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			cin >> m[i][j];
			if (m[i][j] == '@') {
				posiciones.push_back({i,j});
				ini.first = i; ini.second = j;
			}
			if(m[i][j] == '!')
				posiciones.push_back({ i,j });
		}
	}
	int v = posiciones.size();
	int sol = 0;
	if (posiciones.size() > 1) {
		vvi memo;
		memo.assign(v, vector<int>(1 << v, -1));
		// Completar el grafo con bfs
		vvi dist;
		dist.assign(v, vector<int>(1 << v, 0));
		for (int i = 0; i < v; ++i) {
			for (int j = i + 1; j < v; ++j) {
				dist[i][j] = bfs(posiciones[i], posiciones[j], m);
				dist[j][i] = dist[i][j];
			}
		}

		/*for (int i = 0; i < v; ++i) {
			for (int j = 0; j < v; ++j) {
				cout << dist[i][j] << " ";
			}
			cout << '\n';
		}*/
		sol = tsp(0, 1, memo, dist);
	}
	if(sol == INF || !seguro(ini.first, ini.second, m)) cout << -1 << '\n';
	else cout << sol << '\n';
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