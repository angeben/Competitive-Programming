#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>

using namespace std;
using matriz = vector<vector<int>>;

vector<int> kx = { 1,1,2,2,-1,-1,-2,-2 };
vector<int> ky = { 2,-2,1,-1,2,-2,1,-1 };

vector<int> bx = { 2,2,-2,-2 };
vector<int> by = { 2,-2,2,-2 };

int N;

struct pos {
	int i, j;
	int prev;
};

bool ok(int i, int j) {
	return i < N&& i >= 0 && j < N&& j >= 0;
}

vector<pos> adjList(pos p) {
	vector<pos> ret;
	int ni, nj;
	if (p.prev != 2) {
		for (int i = 0; i < 8; ++i) {
			ni = p.i + kx[i]; nj = p.j + ky[i];
			if (ok(ni, nj)) ret.push_back({ ni,nj, 2});
		}
	}
	if (p.prev != 3) {
		for (int i = 0; i < 4; ++i) {
			ni = p.i + bx[i]; nj = p.j + by[i];
			if (ok(ni, nj)) ret.push_back({ ni,nj, 3});
		}
	}
	if (p.prev != 5) {
		ret.push_back({ N - 1 - p.i, p.j, 5 });
		ret.push_back({ p.i, N - 1 - p.j, 5 });
	}
	return ret;
}

int bfs(pos ini, pos dest, matriz & visited) {
	if (ini.i == dest.i && ini.j == dest.j) return 0;
	queue<pos> q;
	visited[ini.i][ini.j] = 30;
	q.push(ini);
	int d = 0;
	while (!q.empty()) {
		int s = q.size();
		++d;
		while(s--){
			pos v = q.front(); q.pop();
			for (pos& w : adjList(v)) {
				if (visited[w.i][w.j] % w.prev != 0) { // 2*3*5 = 30
					visited[w.i][w.j] *= w.prev;
					if (w.i == dest.i && w.j == dest.j)
						return d;
					q.push(w);
				}
			}
		}
	}
	return -1;
}


bool resuelveCaso() {

	cin >> N;
	if (N == 0) return false;
	N = 2 * N;
	
	matriz visitados(N, vector<int>(N, 1));

	int i, j;
	cin >> i >> j;
	pos ini = { i - 1,j - 1, -1};

	cin >> i >> j;
	pos fin = { i - 1,j - 1,-1 };

	cin >> i >> j;
	while (i != 0 && j != 0) {
		visitados[i - 1][j - 1] = 30;
		cin >> i >> j;
	}

	int sol = bfs(ini, fin, visitados);
	if (sol == -1) cout << "Solution doesn't exist\n";
	else cout << "Result : " << sol << '\n';

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

