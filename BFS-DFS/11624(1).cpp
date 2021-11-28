#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <cmath>
#include <map>

using namespace std;
using matriz = vector<vector<char>>;
int F, C;

vector<int> df = { 1,0,-1,0 };
vector<int> dc = { 0,1,0,-1 };

struct obj {
	char type;
	int i, j;
};

bool ok(int i, int j) {
	return 0 <= i && i < F && 0 <= j && j < C;
}
bool borde(int i, int j) {
	return (0 == i) ||
		(0 == j) ||
		(F - 1 == i) ||
		(j == C - 1);
}

int bfs(obj& jason, queue<obj>& q, matriz& m) {
	if (borde(jason.i, jason.j)) return 1;
	int tam = 1;
	queue<obj> buenos;
	int js = 1;
	while (!q.empty() && js != 0) {
		int s = q.size();
		tam++;
		while (s-- && js != 0) {
			obj o = q.front();
			if (o.type == 'J') js--;
			q.pop();
			for (int k = 0; k < 4; ++k) {
				int ni = o.i + df[k], nj = o.j + dc[k];
				if (ok(ni, nj) && m[ni][nj] != '#' && m[ni][nj] != 'F' && m[ni][nj] != o.type) {
					if (borde(ni, nj) && o.type == 'J') {
						buenos.push({ 'J', ni,nj });
					}
					if (o.type != 'J') m[ni][nj] = 'F';
					else m[ni][nj] = 'J';
					q.push({ o.type, ni,nj });
					if (o.type == 'J') js++;
				}
			}
		}
		while (!buenos.empty()) {
			obj o = buenos.front();
			if (m[o.i][o.j] != 'F') return tam;
			buenos.pop();
		}

	}
	if (q.empty() || js == 0) return -1;
}


void resuelveCaso() {
	cin >> F >> C;
	obj jason;
	queue<obj> q;
	matriz m(F, vector<char>(C, '.'));
	for (int i = 0; i < F; ++i) {
		for (int j = 0; j < C; ++j) {
			cin >> m[i][j];
			if (m[i][j] == 'J') {
				jason = { 'J', i,j };
			}
			else if (m[i][j] == 'F') {
				q.push({ 'F', i, j });
			}
		}
	}
	queue<obj> q2;
	q2.push(jason);
	while (!q.empty()) {
		q2.push(q.front());
		q.pop();
	}
	int sol = bfs(jason, q2, m);
	if (sol == -1) cout << "IMPOSSIBLE\n";
	else cout << sol << '\n';
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::ofstream out("output.txt");
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
	//system("PAUSE");
#endif

	return 0;
}

