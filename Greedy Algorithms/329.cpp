#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <utility>
using namespace std;

struct ed {
	int izq;
	int der;
	bool operator <(const ed & e) const {
		if (der == e.der)
			return izq < e.izq;
		else return der < e.der;
	}
};

bool resuelveCaso() {
	int num;
	cin >> num;
	if (num == 0) return false;
	vector<ed> edificios;
	int i, d;
	for (int j = 0; j < num; ++j) {
		cin >> i >> d;
		edificios.push_back({ i,d });
	}
	sort(edificios.begin(), edificios.end());
	int tunel = 1, aux = edificios[0].der;
	for (int i = 1; i < edificios.size(); ++i) {
		if (edificios[i].izq >= aux) {
			tunel++;
			aux = edificios[i].der;
		}
	}
	cout << tunel << '\n';
	return true;
}

int main() {

/*#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	//std::ofstream out("output.txt");
	//auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif*/
	while(resuelveCaso());
	/*
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	//std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif*/

	return 0;
}

