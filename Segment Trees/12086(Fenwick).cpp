#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <sstream>

using namespace std;
int caso = 0;

class FenwickTree {
	vector<int> ft;
public:
	FenwickTree(int n) { ft.assign(n + 1, 0); }

	int getSum(int b) {
		int ret = 0;
		while (b) {
			ret += ft[b]; b -= (b & -b);
		}
		return ret;
	}

	void add(int pos, int val) {
		while (pos < ft.size()) {
			ft[pos] += val; pos += (pos & -pos);
		}
	}

	int getSum(int a, int b) {
		return getSum(b) - getSum(a - 1);
	}
	int getValue(int pos) {
		return getSum(pos) - getSum(pos - 1);
	}
	void setValue(int pos, int val) {
		add(pos, val - getValue(pos));
	}
};

bool resuelveCaso() {
	caso++;
	int n; cin >> n;
	if (n == 0) return false;
	cout << "Case " << caso << ":\n";
	FenwickTree f(n);
	int pot;
	for (int i = 1; i <= n; ++i) {
		cin >> pot;
		f.setValue(i, pot);
	}
	string op;
	int x, y;
	cin >> op;
	while (op != "END") {
		cin >> x >> y;
		if (op == "S") {
			f.setValue(x, y);
		}
		if (op == "M") {
			cout << f.getSum(x,y) << '\n';
		}
		cin >> op;
	}
	cout << '\n';
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