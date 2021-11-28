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

vector<int> ady(int a) {
	return { (a + 1) % 10000, (a * 2) % 10000, (a / 3) % 10000 };
}

int bfs(int s, int b, vector<bool> & visited, vector<int> & dist) {
	queue<int> q;
	dist[s] = 0; visited[s] = true;
	q.push(s);
	while (!q.empty()) {
		int v = q.front(); q.pop();
		for (int w : ady(v))
			if (!visited[w]) {
				dist[w] = dist[v] + 1;
				visited[w] = 1;
				if (w == b) return dist[b];
				q.push(w);
			}
	}
	return 0;
}


bool resuelveCaso() {
	int a, b;
	if (!(cin >> a >> b)) return false;

	vector<bool> visited(10000, false);
	vector<int> dist(10000, 0);

	cout << bfs(a, b, visited, dist) << '\n';

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

