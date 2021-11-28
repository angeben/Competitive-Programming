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
using matriz = vector<vector<int>>;

int dfs(vector<vector<int>> const& v, vector<bool>& visitados, int const& s) {
	int count = 1;
	if (visitados[s]) count = 0;
	visitados[s] = true;
	for (int x : v[s]) {
		if (!visitados[x]) count += dfs(v, visitados, x);
	}
	return count;
}

void resuelveCaso() {
	int n, m, l;
	cin >> n >> m >> l;
	vector<vector<int>> v(n + 1);
	vector<bool> visitados(n + 1, 0);
	queue<int> q;
	int x, y;
	for (int i = 0; i < m; ++i) {
		cin >> x; cin >> y;
		v[x].push_back(y);
	}
	int z;
	for (int i = 0; i < l; ++i) {
		cin >> z; q.push(z);
	}
	int count = 0;
	while (!q.empty()) {
		int s = q.front(); q.pop();
		count += dfs(v, visitados, s);
	}
	cout << count << '\n';
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

