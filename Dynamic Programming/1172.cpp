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

struct ciudad {
	string os;
	int valor;
};

void resolver(vector<ciudad> const& norte, vector<ciudad> const& sur) {
	vector<vector<int>> v(norte.size(), vector<int>(sur.size(), 0)); //v max primeras i j de n y s
	vector<vector<int>> p(norte.size(), vector<int>(sur.size(), 0)); //p min puentes para v max

	for (int i = 1; i < norte.size(); ++i) {
		for (int j = 1; j < sur.size(); ++j) {
			bool o = ((v[i - 1][j] > v[i][j - 1]) || (v[i - 1][j] == v[i][j - 1]) && p[i - 1][j] < p[i][j - 1]);
			v[i][j] = o ? v[i - 1][j] : v[i][j - 1];
			p[i][j] = o ? p[i - 1][j] : p[i][j - 1];
			if (norte[i].os == sur[j].os) {
				int us = v[i - 1][j - 1] + norte[i].valor + sur[j].valor; //usando i j
				if (us > v[i][j] || us == v[i][j] && p[i - 1][j - 1] < p[i][j]) {
					v[i][j] = us; p[i][j] = p[i - 1][j - 1] + 1;
				}
			}
		}
	}
	cout << v[norte.size() - 1][sur.size() - 1] << ' ' << p[norte.size() - 1][sur.size() - 1] << '\n';
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	std::ofstream out("salida.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int c, n, s;
	string na, o;
	int v;
	cin >> c;
	for (int i = 0; i < c; ++i) {
		cin >> n;
		vector<ciudad> norte(n + 1);
		for (int i = 1; i <= n; ++i) {
			cin >> na >> o >> v;
			norte[i] = { o,v };
		}
		cin >> s;
		vector<ciudad> sur(s + 1);
		for (int i = 1; i <= s; ++i) {
			cin >> na >> o >> v;
			sur[i] = { o,v };
		}
		resolver(norte, sur);
	}



#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}

