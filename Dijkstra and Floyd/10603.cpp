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

int INF = 1000000;

struct estado { // agua en las jarras primera y segunda
	int a, b;
};

bool operator <(pair<int,estado> const a, pair<int, estado> const b) {
	return a.first > b.first;
}

vector<pair<int, estado>> movimientos(estado u, int CA, int CB, int CC) {
	// Pares {agua movida, estado al que se llega}
	vector<pair<int, estado>> l;
	if (u.a != 0) { // Vaciar la primera jarra
		if (u.a + u.b <= CB) l.push_back({ u.a, {0, u.a + u.b} }); // Pasamos todo el agua de A a B
		else l.push_back({ CB - u.b, {u.a + u.b - CB, CB} }); // No podemos pasar todo el agua
		l.push_back({ u.a, {0, u.b} }); // Pasar agua de A a C (no se puede llenar C y que aun haya en A)
	}
	if (u.b != 0) { // Vaciar la segunda jarra
		if (u.a + u.b <= CA) l.push_back({ u.b, { u.a + u.b, 0} }); // Pasamos todo el agua de B a A
		else l.push_back({ CA - u.a, {CA, u.a + u.b - CA} }); // No podemos pasar todo el agua
		l.push_back({ u.b, {u.a, 0} }); // Pasar agua de B a C (no se puede llenar C y que aun haya en B)
	}
	int aguaC = CC - u.a - u.b;
	if (aguaC != 0) { // Vaciar la tercera jarra
		if (u.a + aguaC <= CA) l.push_back({ aguaC, { u.a + aguaC, u.b} }); // Pasamos todo el agua de C a A
		else l.push_back({ CA - u.a, {CA, u.b} }); // No podemos pasar todo el agua
		if (u.b + aguaC <= CB) l.push_back({ aguaC, { u.a , u.b + aguaC } }); // Pasamos todo el agua de C a B
		else l.push_back({ CB - u.b, {u.a, CB} }); // No podemos pasar todo el agua
	}
	return l;
}

void cercanoSinsolucion(int agua, estado u, int CC, int d, int & cercanoAgua, estado & cercanoEst) {
	if (u.a < d && u.a > cercanoAgua) {
		cercanoAgua = u.a;
		cercanoEst = u;
	}
	if (u.b < d && u.b > cercanoAgua) {
		cercanoAgua = u.b;
		cercanoEst = u;
	}
	int aguaC = CC - u.a - u.b;
	if (aguaC < d && aguaC > cercanoAgua) {
		cercanoAgua = aguaC;
		cercanoEst = u;
	}
}

void resolverCaso() {
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	vector<vector<int>> dist(a+1, vector<int>(b+1, INF));
	// En caso de que no se encuentre solucion
	int cercanoAgua = 0;
	estado cercanoEst = { 0,0 };
	// Dijkstra
	priority_queue<pair<int,estado>, vector<pair<int,estado>>> pq;
	pq.push({ 0, {0,0} });
	dist[0][0] = 0;
	estado fin;
	bool encontrado = false;
	while (!pq.empty() && !encontrado) {
		pair<int, estado> front = pq.top(); pq.pop();
		int agua = front.first;
		estado u = front.second;
		if (u.a == d || u.b == d || (c - u.a - u.b) == d) {
			fin = u;
			encontrado = true;
		}
		cercanoSinsolucion(agua, u, c, d, cercanoAgua, cercanoEst);
		if (agua > dist[u.a][u.b]) continue;
		for (auto v : movimientos(u, a, b, c)) {
			if (dist[u.a][u.b] + v.first < dist[v.second.a][v.second.b]) {
				dist[v.second.a][v.second.b] = dist[u.a][u.b] + v.first;
				pq.push({ dist[v.second.a][v.second.b], v.second });
			}
		}
	}

	if(encontrado) cout << dist[fin.a][fin.b] << " " << d << "\n";
	else cout << dist[cercanoEst.a][cercanoEst.b] << " " << cercanoAgua << "\n";
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	std::ofstream out("salida.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int T;
	cin >> T;
	while (T != 0) {
		resolverCaso();
		T--;
	}

#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}