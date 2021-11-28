#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <utility>
#include <queue>
#include <map>
#include <stack>
using namespace std;

int vectorToint(const vector<int> & v) {
	int r = 0;
	int pot = 1000;
	for (int i = 0; i < 4; ++i) {
		r += pot * v[i];
		pot = pot / 10;
	}
	return r;
}

vector<vector<int>> ady(const vector<int> & a) {
	vector<vector<int>> r;
	for(int i = 0; i < 4; ++i){
		vector<int> aux1 = a;
		vector<int> aux2 = a;
		aux1[i] = (aux1[i] + 1) % 10;
		aux2[i] = (aux2[i] - 1) % 10;
		if (aux2[i] == -1) aux2[i] = 9;
		r.push_back(aux1);
		r.push_back(aux2);
	}
	return r;
}

int bfs(const vector<int> & ini, const vector<int> & fin, vector<bool>& visited, vector<int> & dist) {
	queue<vector<int>> q;
	dist[vectorToint(ini)] = 0; visited[vectorToint(ini)] = true;
	q.push(ini);
	while (!q.empty()) {
		vector<int> v = q.front(); q.pop();
		for (vector<int> w : ady(v))
			if (!visited[vectorToint(w)]) {
				dist[vectorToint(w)] = dist[vectorToint(v)] + 1;
				visited[vectorToint(w)] = 1;
				if (w == fin) return dist[vectorToint(fin)];
				q.push(w);
			}
	}
	return dist[vectorToint(fin)];
}


void resuelveCaso() {
	vector<int> ini(4);
	vector<int> fin(4);
	for (int i = 0; i < 4; ++i)
		cin >> ini[i];
	for (int i = 0; i < 4; ++i)
		cin >> fin[i];

	int n; 
	cin >> n;
	vector<bool> visited(10000, false);
	vector<int> dist(10000, -1);

	for (int i = 0; i < n; ++i) {
		vector<int> aux(4);
		for (int j = 0; j < 4; ++j)
			cin >> aux[j];
		visited[vectorToint(aux)] = true;
	}
	cout << bfs(ini, fin, visited, dist) << '\n';
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	std::ofstream out("salida.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int casos;
	cin >> casos;
	while (casos > 0) {
		resuelveCaso();
		--casos;		
	};


#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}