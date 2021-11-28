#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;
using matriz = vector<vector<int>>;

void resuelveCaso() {
	int n;
	cin >> n;
	vector<long long int> v(n+1, 0);
	v[0] = 1;
	v[1] = 1;
	if(n >= 2) v[2] = 5;
	for (int i = 3; i < n+1; ++i) {
		v[i] = v[i - 1] + 4 * v[i - 2] + 2 * v[i - 3];
	}
	cout << v[n] << '\n';
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	//std::ofstream out("output.txt");
	//auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int t;
	cin >> t;
	for (int i = 0; i < t; ++i) {
		resuelveCaso();
	}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	//std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}