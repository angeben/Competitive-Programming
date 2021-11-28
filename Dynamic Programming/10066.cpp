#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;


bool resolver(int n) {
	int l1, l2;
	cin >> l1 >> l2;
	if (l1 == 0 && l2 == 0) return false;
	vector<int> t1(l1);
	vector<int> t2(l2);
	for (int i = 0; i < l1; ++i)
		cin >> t1[i];
	for (int i = 0; i < l2; ++i)
		cin >> t2[i];

	vector<vector<int>> m(l1+1, vector<int>(l2+1, 0));
	for (int i = 1; i <= l1; ++i) {
		for (int j = 1; j <= l2; ++j) {
			if (t1[i - 1] == t2[j - 1])
				m[i][j] = m[i - 1][j - 1] + 1;
			else m[i][j] = max(m[i-1][j],m[i][j-1]);
		}
	}
	cout << "Twin Towers #" << n << "\n";
	cout << "Number of Tiles : " << m[l1][l2] << "\n\n";
	return true;
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	std::ofstream out("salida.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif
	
	int n = 1;
	while (resolver(n)) ++n;

#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}
