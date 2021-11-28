#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;
using matriz = vector<vector<int>>;
const int INF = 1000000000;

void resuelve(int n) {

	matriz viento(10, vector<int>(n, 0));
	for (int i = 9; i >= 0; --i) {
		for (int j = 0; j < n; ++j) {
			cin >> viento[i][j];
		}
	}

	matriz m(10, vector<int>(n + 1, INF));
	m[0][n] = 0;
	for (int j = n - 1; j >= 0; --j) {
		for (int i = 0; i < 9; ++i) {
			int aux = 30 - viento[i][j] + m[i][j + 1];
			if (i > 0) aux = min(aux, 20 - viento[i][j] + m[i - 1][j + 1]);
			if (i < 9) aux = min(aux, 60 - viento[i][j] + m[i + 1][j + 1]);
			m[i][j] = aux;
		}
	}

	cout << m[0][0] << '\n';
	cout << '\n';

}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	//std::ofstream out("output.txt");
	//auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int casos;
	cin >> casos;
	int n;
	while (casos--) {
		cin >> n;
		n /= 100;
		resuelve(n);
	}
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	//std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}