#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <utility>
#include <queue>

struct par{
	int first;
	char second;
	bool operator <(par otro) {
		return this->first > otro.first || this->first == otro.first && this->second < otro.second;
	}
};


using namespace std;
using matriz = vector<vector<char>>;
using vis = vector<vector<bool>>;

vector<int> df = { 1,0,-1,0 };
vector<int> dc = { 0,1,0,-1 };

int F, C;
int casos = 0;

bool ok(int i, int j) {
	return 0 <= i && i < F && 0 <= j && j < C;
}

int dfs(matriz const & ma, vis & v, int i, int j, char ant) {
	int tam = 1; v[i][j] = true;

	for (int k = 0; k < 4; ++k) {
		int ni = i + df[k], nj = j + dc[k];
		if (ok(ni, nj) && ma[ni][nj] == ant && !v[ni][nj])
			tam += dfs(ma, v, ni, nj, ant);
	}
	return tam;
}

bool resuelveCaso() {
	cin >> F >> C;
	if (F == 0 && C == 0) return false;
	casos++; 
	cout << "Problem " << casos << ":\n";
	matriz ma(F, vector<char>(C, '.'));
	vis v(F, vector<bool>(C, 0));
	for (int i = 0; i < F; ++i) {
		for (int j = 0; j < C; ++j) {
			cin >> ma[i][j];
		}
	}
	vector<par> sols;
	for (int i = 0; i < F; ++i) {
		for (int j = 0; j < C; ++j) {
			if(ma[i][j] != '.' && !v[i][j])
				sols.push_back({ dfs(ma, v, i, j, ma[i][j]), ma[i][j]});
		}
	}
	sort(sols.begin(), sols.end());
	for (auto x : sols) {
		cout << x.second << ' ' << x.first << '\n';
	}
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

