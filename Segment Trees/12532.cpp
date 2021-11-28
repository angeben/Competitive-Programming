#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <sstream>

using namespace std;
int v[100001];

class SegmentTree {
	vector<int> st;
	int tam; // Numero de hojas que manejamos
public:
	// Tamano maximo que podremos guardar
	// (numero de hojas).
	// Antes de las consultas, se necesita rellenar
	// con los datos iniciales usando build().
	SegmentTree(int maxN) {
		st.assign(4 * maxN + 10, 0);
	}
	int query(int a, int b) {
		return query(1, 0, tam - 1, a, b);
	}
	int query(int vertex, int L, int R, int i, int j) {
		if (i > R || j < L) {
			return 1;
		}
		if (L >= i && R <= j)
			// Segmento completamente dentro de la consulta
			return st[vertex];
		int mitad = (L + R) / 2;
		return query(2 * vertex, L, mitad, i, j) *
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
		st[vertex] = st[2 * vertex] * st[2 * vertex + 1];
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
		st[p] = st[2 * p] * st[2 * p + 1];
	}
};

bool resuelveCaso() {
	int n, k;
	cin >> n;
	if (!cin) return false;
	cin >> k;

	for (int i = 0; i < n; ++i) {
		cin >> v[i];
		if (v[i] > 0) v[i] = 1;
		else if (v[i] < 0) v[i] = -1;
	}
	SegmentTree s(n);
	s.build(v, n);

	char action;
	int a, b, o;
	for(int i = 0; i < k; ++i) {
		cin >> action >> a >> b;
		if (action == 'C') {
			if (b > 0) b = 1;
			else if (b < 0) b = -1;
			s.update(a - 1, b);
		}
		else {
			o = s.query(a - 1, b - 1);
			if (o == 1) cout << '+';
			else if (o == -1) cout << '-';
			else cout << '0';
		}
	}
	cout << '\n';
	return true;
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	std::ofstream out("output.txt");
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
