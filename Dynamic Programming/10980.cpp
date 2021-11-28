#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

struct oferta {
	int uds;
	double precio;
};

bool resolver(int caso) {
	double p; // precio por unidad
	int n; // numero de ofertas
	cin >> p >> n;
	if (!cin) return false;
	oferta aux;
	vector<oferta> ofertas(n);
	for (int i = 0; i < n; ++i)
		cin >> ofertas[i].uds >> ofertas[i].precio;
	cin.ignore();
	string str;
	int x, max = 0;
	vector<int> casos;
	getline(cin, str);
	stringstream linea(str);
	while (linea) {
		linea >> x;
		casos.push_back(x);
		if (x > max) max = x;
	}
	casos.pop_back(); // Repite el ultimo
	
	vector<vector<double>> compra(n + 1, vector<double>(max + 1));
	for (int i = 0; i < n + 1; ++i)
		compra[i][0] = 0;
	for (int j = 1; j < max + 1; ++j)
		compra[0][j] = p * j;
	for (int i = 1; i < n + 1; ++i) {
		for (int j = 1; j < max + 1; ++j) {
			if (j <= ofertas[i - 1].uds) compra[i][j] = min(compra[i-1][j], ofertas[i-1].precio);
			else if (j - ofertas[i-1].uds < 0) compra[i][j] = compra[i - 1][j];
			else compra[i][j] = min(compra[i-1][j], compra[i][j - ofertas[i-1].uds] + ofertas[i-1].precio);
		}
	}
	cout << "Case " << caso << ":\n";
	for (int i = 0; i < casos.size(); ++i) {
		double precio = compra[n][casos[i]];
		cout << "Buy " << casos[i] << " for $" << setprecision(2) << fixed << precio << '\n';
	}
	return true;
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	//std::ofstream out("salida.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	//auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int caso = 1;
	while(resolver(caso)) ++caso;

#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	//std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif


	return 0;
}