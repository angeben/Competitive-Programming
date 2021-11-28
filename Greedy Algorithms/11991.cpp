#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
#include <unordered_map>

using namespace std;
using matriz = vector<vector<int>>;

bool resuelveCaso() {
	int n, m;
	cin >> n >> m;
	if (!cin) return false;
	else {
		unordered_map<int, vector<int>> map;
		int aux;
		for (int i = 0; i < n; ++i) {
			cin >> aux;
			map[aux].push_back(i + 1);
		}
		int k, v;
		for (int j = 0; j < m; ++j) {
			cin >> k >> v;
			if (map.count(v) == 1 && k <= map[v].size())
				cout << map[v][k - 1] << '\n';
			else cout << "0\n";
		}
		return true;
	}
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	//std::ofstream out("output.txt");
	//auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif
	while (resuelveCaso());

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	//std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}