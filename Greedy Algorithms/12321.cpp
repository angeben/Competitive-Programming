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

struct intervalo {
	int ini;
	int fin;
	bool operator <(const intervalo & i) const {
		if (ini == i.ini)
			return fin < i.fin;
		else return ini < i.ini;
	}
};

bool resuelveCaso() {
	int d, gas;
	cin >> d >> gas;
	if (d == 0 && gas == 0) return false;
	vector<intervalo> intervalos(gas);
	int c, l;
	for (int i = 0; i < gas; ++i) {
		cin >> c >> l;
		intervalos[i] = {c - l, c + l};
	}
	sort(intervalos.begin(), intervalos.end());
	priority_queue<int> pq;
	int ultimo = 0, aux = 0, usados = 0;
	int i = 0;
	bool posible = true;
	while (posible && ultimo < d && i < gas) {
		if (intervalos[i].ini > ultimo)
			posible = false;
		else {
			while (i < gas && intervalos[i].ini <= ultimo) {
				pq.push(intervalos[i].fin);
				++i;
			}
			aux = pq.top();
			++usados;
			ultimo = aux;
			while (!pq.empty())
				pq.pop();
		}
	}
	if (posible && ultimo < d) posible = false;

	if (posible) std::cout << gas - usados << '\n';
	else cout << "-1\n";
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