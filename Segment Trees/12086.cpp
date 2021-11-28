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
int v[200000];

class SegmentTree {
	vector<int> st;
	int tam; // Numero de hojas que manejamos
public:
	// Tamano maximo que podremos guardar
	// (numero de hojas).
	// Antes de las consultas, se necesita rellenar
	// con los datos iniciales usando build().
	SegmentTree(int maxN) {
		st.assign(4 * maxN + 10,0);
	}
	int query(int a, int b) {
		return query(1, 0, tam - 1, a, b);
	}
	int query(int vertex, int L, int R, int i, int j) {
		if (i > R || j < L) {
			return 0;
		}
		if (L >= i && R <= j)
			// Segmento completamente dentro de la consulta
			return st[vertex];
		int mitad = (L + R) / 2;
		return query(2 * vertex, L, mitad, i, j) +
			query(2 * vertex + 1, mitad + 1, R, i, j);
	}
	void update(int pos, int newVal) {
		update(1, 0, tam - 1, pos, newVal);
	}
	void update(int vertex, int l, int r,
		int pos, int newVal) {
		if ((pos < l) || (r < pos)) return;
		if (l == r) {
			st[vertex] = newVal;
			return;
		}
		int m = (l + r) / 2;
		if ((l <= pos) && (pos <= m))
			update(2 * vertex, l, m, pos, newVal);
		else
			update(2 * vertex + 1, m + 1, r, pos, newVal);
		st[vertex] = st[2 * vertex] + st[2 * vertex + 1];
	}
	void build(int* values, int n) {
		tam = n;
		build(values, 1, 0, n - 1);
	}
	void build(int* values, int p, int l, int r) {
		if (l == r) {
			st[p] = values[l];
			return;
		}
		int m = (l + r) / 2;
		build(values, 2 * p, l, m);
		build(values, 2 * p + 1, m + 1, r);
		st[p] = st[2 * p] + st[2 * p + 1];
	}
};

bool resuelveCaso() {
	caso++;
	int n; cin >> n;
	if (n == 0) return false;
	cout << "Case " << caso << ":\n";
	SegmentTree s(n);
	for (int i = 0; i < n; ++i) {
		cin >> v[i];
	}

	s.build(v, n);

	string action;
	int a, b;
	cin >> action;
	while (action != "END") {
		cin >> a >> b;
		//cout << action << ' ' << a << ' ' << b << '\n';
		if (action == "S") {
			s.update(a-1, b);
		}
		else cout << s.query(a - 1, b - 1) << '\n';
		cin >> action;
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

