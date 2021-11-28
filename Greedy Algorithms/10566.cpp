#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>

const double EPSILON = 0.00000000001;
using namespace std;


double resolver(double x, double y, double c) {
	double a = 0, b = min(x, y), m;
	m = (a + b) / 2;
	while (abs((1/c) - (1 / sqrt(x * x - m * m)) - (1 / sqrt(y * y - m * m))) > EPSILON) {
		if (1/c < 1 / sqrt(x * x - m * m) + 1 / sqrt(y * y - m * m)) {
			b = m;
		}
		else {
			a = m;
		}
		m = (a + b) / 2;
	}
	return m;
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	std::ofstream out("salida.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif
	double x, y, c;
	while (cin >> x >> y >> c) {
		cout << fixed << setprecision(3) << resolver(x, y, c) << '\n';
	}
	#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}

