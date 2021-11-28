#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;
using vvi = vector<vector<int>>;
using vi = vector<int>;

int MAX_V = 100;
int N;

void dfs(int u, int uParent, const vvi & m, int & hora, int & hijosRaiz, vi & horaVertice, vi & alcanzable, int & places, vi & puntos) {
	horaVertice[u] = alcanzable[u] = hora; hora++;
	for (int i = 0; i < m[u].size(); ++i) {
		int v = m[u][i];
		if (v == uParent) continue;
		if (horaVertice[v] == 0) {
			if (uParent == 0) hijosRaiz++;
			dfs(v, u, m, hora, hijosRaiz, horaVertice, alcanzable, places, puntos);
			if (alcanzable[v] >= horaVertice[u])
				if (uParent != 0) {
					if (find(puntos.begin(), puntos.end(), u) == puntos.end()) {
						++places; // Punto de articulacion
						puntos.push_back(u);
					}
				}
			alcanzable[u] = min(alcanzable[u], alcanzable[v]);
		}
		else
			alcanzable[u] = min(alcanzable[u], horaVertice[v]);
	}
}

bool resuelveCaso() {
	cin >> N;
	if (N == 0) return false;
	
	vvi m(N + 1);
	int x, aux;
	cin >> x;
	while (x != 0) {
		string str;
		getline(cin, str);
		stringstream linea(str);
		while (linea) {
			linea >> aux;
			if(find(m[x].begin(), m[x].end(), aux) == m[x].end())
				m[x].push_back(aux);
			if (find(m[aux].begin(), m[aux].end(), x) == m[aux].end())
				m[aux].push_back(x);
		}
		cin >> x;
	}


	int hora = 1;
	int hijosRaiz;
	vi horaVertice(MAX_V, 0);
	vi alcanzable(MAX_V, -1);
	int places = 0;
	vi puntos;

	for (int i = 1; i <= N; ++i) {
		if (!horaVertice[i]) {
			hijosRaiz = 0;
			dfs(i, 0, m, hora, hijosRaiz, horaVertice, alcanzable, places, puntos);
			if (hijosRaiz > 1)
				++places;
		}
	}
	cout << places << "\n";
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