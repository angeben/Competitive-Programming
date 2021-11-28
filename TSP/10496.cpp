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

struct pos {
	int x, y;
};

int F, C, V;
pos k;
vector<pos> bs;
vector<vector<int>> memo;


int dist(pos a, pos b) {
	return max(a.x, b.x) - min(a.x, b.x) + max(a.y, b.y) - min(a.y, b.y);
}

int tsp(int p, int visitados) {
	if (visitados == (1 << V) - 1) // hemos visitado ya todos los vértices
		return dist(bs[p],bs[0]); // volvemos al origen
	if (memo[p][visitados] != -1)
		return memo[p][visitados];
	int res = 1000000000; // INF
	for (int i = 1; i < V; ++i)
		if (!(visitados & (1 << i))) // no hemos visitado vértice i
			res = min(res, dist(bs[p], bs[i]) + tsp(i, visitados | (1 << i)));
	return memo[p][visitados] = res;
}

void resuelveCaso() {
	cin >> F >> C;
	cin >> k.x >> k.y;
	cin >> V;
	V = V + 1;
	vector<pos> b(V);
	b[0] = k;
	for (int i = 1; i < V; ++i) {
		cin >> b[i].x >> b[i].y;
	}
	bs = b;
	memo.assign(V, vector<int>(1 << V, -1));
	int aux = 0;
	cout << "The shortest path has length ";
	cout << tsp(0, 1)<< '\n';
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

