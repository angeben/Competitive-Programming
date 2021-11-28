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
using vii = vector<pair<int, int>>;
using ii = pair<int, int>;
int INF = 10000000;

int caso = 0;

void resuelveCaso(int c) {
	caso++;
	vector<vii> adjList(c+1);
	vector<bool> visited(c+1,0);
	vector<int> dist(c+1,INF);
	vector<int> prev(c+1,-1);
	int p, s, b, d;
	for (int i = 0; i < c; ++i) {
		cin >> p;
		vii v(p);
		for (int j = 0; j < p; ++j) {
			cin >> b >> d;
			v[j] = { d, b };
		}
		adjList[i+1] = v;
	}
	cin >> s >> b;
	dist[s] = 0;
	priority_queue<ii, vii, greater<ii>> pq;
	pq.push({ 0, s });
	while (!pq.empty()) {
		ii front = pq.top(); pq.pop();
		int d = front.first, u = front.second;
		if (d > dist[u]) continue;
		for (auto a : adjList[u]) {
			if (dist[u] + a.first < dist[a.second]) {
				dist[a.second] = dist[u] + a.first;
				prev[a.second] = u;
				pq.push({ dist[a.second], a.second });
			}
		}
	}
	int x = b;
	stack<int> st;
	st.push(x);
	x = prev[x];
	while (x != s) {
		st.push(x);
		x = prev[x];
	}
	st.push(s);
	cout << "Case " << caso << ": Path =";
	while (!st.empty()) {
		cout << ' ' << st.top();
		st.pop();
	}
	cout << "; " << dist[b] << " second delay\n";
}


int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	std::ofstream out("salida.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int c;
	cin >> c;
	while (c != 0) {
		resuelveCaso(c);
		cin >> c;
	}


#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}

