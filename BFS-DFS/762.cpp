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
map<string, bool> visited;

bool bfs(string a, string b, map<string, vector<string>> const& m, map<string, string>& prev) {
	queue<string> q;
	visited.at(a) = true;
	q.push(a);
	while (!q.empty() && !visited.at(b)) {
		string v = q.front(); q.pop();
		for (string x : m.at(v)) {
			if (!visited.at(x)) {
				visited.at(x) = true;
				prev.insert({ x, v });
				if (x == b) return true;
				q.push(x);
			}
		}
	}
	return false;
}

void resuelveCaso(int c) {
	map<string, vector<string>> m;
	string a, b;
	visited.clear();
	for (int i = 0; i < c; ++i) {
		cin >> a >> b;
		if (m.count(a) == 0) {
			m.insert({ a,{b} });
			visited.insert({ a,0 });
		}
		else m.at(a).push_back(b);
		if (m.count(b) == 0) {
			m.insert({ b,{a} });
			visited.insert({ b,0 });
		}
		else m.at(b).push_back(a);
	}
	cin >> a >> b;
	if (m.count(a) == 0 || m.count(b) == 0) {
		cout << "No route\n";
		return;
	}
	map<string, string> prev;
	if (bfs(a, b, m, prev)) {
		string l = b;
		stack<string> camino;
		while (l != a) {
			camino.push(l);
			l = prev.at(l);
		}
		camino.push(a);
		while (camino.top() != b) {
			cout << camino.top() << ' ';
			camino.pop();
			cout << camino.top() << '\n';
		}
	}
	else cout << "No route\n";
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	std::ofstream out("salida.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int c; string blank;
	cin >> c;
	resuelveCaso(c);
	while (cin >> c) {
		cout << '\n';
		resuelveCaso(c);
	}


#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}

