#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <stack>

using namespace std;

bool matr(vector<int> const& v) {
	bool ok = true;
	stack<int> s;
	stack<int> sumas;
	s.push(v[0]);
	sumas.push(v[0]);

	for (int i = 1; i < v.size() - 1 && ok; ++i) {
		if (v[i] < 0 && abs(v[i]) < abs(s.top())) {
			s.push(v[i]);
			sumas.push(v[i]);
		}
		else if (v[i] > 0 && s.size() != 0 && abs(v[i]) == abs(s.top())) {
			s.pop();
			sumas.pop();
			if (sumas.size() != 0) {
				sumas.top() += v[i];
				if (sumas.top() >= 0) ok = false;
			}
		}
		else {
			ok = false;
		}
	}
	return (ok && s.size() == 0);
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	std::ofstream out("salida.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	string str;
	int x;
	getline(cin, str);
	while (cin) {
		vector<int> v;
		stringstream linea(str);
		while (linea) {
			linea >> x;
			v.push_back(x);
		}
		if (matr(v)) cout << ":-) Matrioshka!\n";
		else cout << ":-( Try again.\n";
		getline(cin, str);
	}

	#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif


	return 0;
}

