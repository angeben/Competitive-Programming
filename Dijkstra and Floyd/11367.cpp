#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

struct triple {
	int coste, gas, ciudad;
	bool operator>(triple const& b)  const {
		return (this->coste > b.coste) || (this->coste == b.coste && this->gas < b.gas)
			|| (this->coste == b.coste && this->gas == b.gas && this->ciudad > b.ciudad);
	}
};

using par = pair<int, int>;
using vi = vector<int>;
using vp = vector<par>;
using vt = vector<triple>;
using vvi = vector<vi>;
using vvp = vector<vector<par>>;
vvp grafo;
vi p;
int n, m, c, s, e;

vt adjList(triple t) {
	vt l;
	if (t.gas < c) l.push_back({ p[t.ciudad], t.gas + 1, t.ciudad });
	for (par ady : grafo[t.ciudad]) {
		if (ady.second <= t.gas) l.push_back({ 0, t.gas - ady.second, ady.first });
	}
	return l;
}


int dijkstra(int s, int e) {
	vvi dist; int cota = 1000000000;
	dist.assign(n, vi(c + 1, 1000000000));
	dist[s][0] = 0;
	priority_queue<triple, vt, greater<triple>> pq;
	pq.push({ 0, 0, s });
	while (!pq.empty()) {
		triple front = pq.top(); pq.pop();
		int d = front.coste, u = front.ciudad, g = front.gas;
		if (d > dist[u][g]) continue;
		for (auto a : adjList(front)) {
			int nuevo = dist[u][g] + a.coste;
			if (nuevo <= cota && nuevo < dist[a.ciudad][a.gas]) {
				dist[a.ciudad][a.gas] = nuevo;
				pq.push({ dist[a.ciudad][a.gas], a.gas, a.ciudad });
				if (a.ciudad == e) return dist[e][a.gas];
			}
		}
	}
	return 1000000000;
}


void resuelveCaso() {
	cin >> n >> m;
	p.assign(n, 0);
	for (int i = 0; i < n; ++i) {
		cin >> p[i];
	}
	grafo.assign(n, vp());
	int u, v, d;
	for (int i = 0; i < m; ++i) {
		cin >> u >> v >> d;
		grafo[u].push_back({ v,d });
		grafo[v].push_back({ u,d });
	}

	int q;
	cin >> q;
	while (q--) {
		cin >> c >> s >> e;
		if (s == e) cout << "0\n";
		else {
			int sol = dijkstra(s, e);
			if (sol >= 1000000000) cout << "impossible\n";
			else cout << sol << '\n';
		}

	}
}


int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	std::ofstream out("salida.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	resuelveCaso();


#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}

