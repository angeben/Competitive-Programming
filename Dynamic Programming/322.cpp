#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <utility>
using namespace std;


bool resuelveCaso() {
	string palabra;
	cin >> palabra;
	if (!cin) return false;
	// m(i,j) = maxima longitud de un palindromo considerando las letras i...j; Se rellena por diagonales
	vector<vector<int>> m(palabra.size(), vector<int>(palabra.size(), 0));

	// Palabras de una letra
	for (int i = 0; i < palabra.size(); ++i)
		m[i][i] = 1;

	for (int d = 2; d <= palabra.size(); ++d) {
		for (int i = 0; i <= palabra.size() - d; ++i) {
			int j = i + d - 1;
			if (palabra[i] == palabra[j] && d == 2) {
				m[i][j] = 2;
			}
			else if (palabra[i] == palabra[j]) {
				m[i][j] = m[i + 1][j - 1] + 2;
			}
			else m[i][j] = max(m[i + 1][j], m[i][j - 1]);
		}
	}
	// Reconstrucción de la solución
	int lon = m[0][palabra.size() - 1];
	int i = 0, j = palabra.size() - 1;
	string palindromo = "";
	while (i <= j && lon > 0) {
		if (i == j) { // Palabra de longitud 1
			palindromo.push_back(palabra[i]);
			--lon;
		}
		else if (palabra[i] == palabra[j]) {
			palindromo.push_back(palabra[i]);
			lon -= 2;
			++i; --j;
		}
		// La solucion no usa la i o la j
		else if (m[i + 1][j] < m[i][j - 1]) // Sin usar la j tenemos mejor solucion
			--j;
		else ++i;
	}
	// Tenemos la mitad del palindromo
	for (int i = (m[0][palabra.size() - 1] / 2) - 1; i >= 0; --i)
		palindromo.push_back(palindromo[i]);
	cout << palindromo << '\n';
	return true;
}

int main() {

/*	#ifndef DOMJUDGE
		std::ifstream in("datos.txt");
		auto cinbuf = std::cin.rdbuf(in.rdbuf());
		//std::ofstream out("output.txt");
		//auto coutbuf = std::cout.rdbuf(out.rdbuf());
	#endif*/
	while (resuelveCaso());
/*
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	//std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif*/

	return 0;
}

