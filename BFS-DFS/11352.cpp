#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <utility>
#include <queue>

//Este codigo es un poco feo y largo

using namespace std;
using matriz = vector<vector<char>>;
using vis = vector<vector<bool>>;

bool visitar(pair<int, int> const& p, queue<pair<int, int>>& q, matriz const& ma) {
	int a = p.first, b = p.second;
	if (ma[a][b] == 'B') return true;
	if (a + 1 < ma.size()) {
		q.push({ a + 1, b });
		if (b - 1 >= 0) q.push({ a + 1, b - 1 });
		if (b + 1 < ma[0].size()) q.push({ a + 1, b + 1 });
	}
	if (a - 1 >= 0) {
		q.push({ a - 1, b });
		if (b - 1 >= 0) q.push({ a - 1, b - 1 });
		if (b + 1 < ma[0].size()) q.push({ a - 1, b + 1 });
	}
	if (b - 1 >= 0) q.push({ a, b - 1 });
	if (b + 1 < ma[0].size()) q.push({ a, b + 1 });

	return false;
}

void visitarCaballo(int a, int b, vis& v) {
	if (a + 1 < v.size()) {
		if (b - 2 >= 0) v[a + 1][b - 2] = 1;
		if (b + 2 < v[0].size()) v[a + 1][b + 2] = 1;
	}
	if (a + 2 < v.size()) {
		if (b - 1 >= 0) v[a + 2][b - 1] = 1;
		if (b + 1 < v[0].size()) v[a + 2][b + 1] = 1;
	}

	if (a - 1 >= 0) {
		if (b - 2 >= 0) v[a - 1][b - 2] = 1;
		if (b + 2 < v[0].size()) v[a - 1][b + 2] = 1;
	}

	if (a - 2 >= 0) {
		if (b - 1 >= 0) v[a - 2][b - 1] = 1;
		if (b + 1 < v[0].size()) v[a - 2][b + 1] = 1;
	}

}

void resuelveCaso() {
	int m, n;
	cin >> m >> n;
	matriz ma(m, vector<char>(n, '.'));
	vis v(m, vector<bool>(n, 0));
	queue<pair<int, int>> q;
	pair<int, int> s1, s2;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> ma[i][j];
			if (ma[i][j] == 'A') {
				s1 = { i,j };
			}
			else if (ma[i][j] == 'B') {
				s2 = { i,j };
			}
			else if (ma[i][j] == 'Z') {
				visitarCaballo(i, j, v);
				v[i][j] = 1;
			}
		}
	}
	v[s1.first][s1.second] = 0;
	v[s2.first][s2.second] = 0;
	q.push(s1);
	bool ok = false; int count = 0;
	while (!q.empty() && !ok) {
		int tam = q.size();
		while (tam-- && !ok) {
			pair<int, int> p = q.front(); q.pop();
			if (!v[p.first][p.second]) {
				v[p.first][p.second] = true;
				ok = visitar(p, q, ma);
			}
		}
		count++;
	}
	if (ok) cout << "Minimal possible length of a trip is " << count - 1 << '\n';
	else cout << "King Peter, you can't go now!\n";

}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	std::ofstream out("salida.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int t;
	cin >> t;
	while (t > 0) {
		resuelveCaso(); --t;
	}



#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}

