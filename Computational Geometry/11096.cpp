#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>
#include <cmath>
#include <random>
#include <tuple>
#include <cassert>
using namespace std;

const double EPS = 1e-9;
const double PI = acos(-1);

using T = double;
struct pt {
	T x, y;
	pt operator+(pt p) const { return { x + p.x, y + p.y }; }
	pt operator-(pt p) const { return { x - p.x, y - p.y }; }
	pt operator*(T d) const { return { x*d, y*d }; }
	pt operator/(T d) const { return { x / d, y / d }; } // only for floating-point

	bool operator==(pt o) const { return x == o.x && y == o.y; }
	bool operator!=(pt o) const { return !(*this == o); }

	bool operator<(pt o) const { // sort points lexicographically
		if (x == o.x) return y < o.y;
		return x < o.x;
	}
};
ostream& operator<<(ostream& os, pt p) {
	return os << "(" << p.x << "," << p.y << ")";
}

T sq(pt v) { return v.x*v.x + v.y*v.y; }
double abs(pt v) { return sqrt(sq(v)); }
double dist(pt a, pt b) { // Euclidean distance
	return hypot(a.x - b.x, a.y - b.y);
}
T cross(pt v, pt w) { return v.x*w.y - v.y*w.x; }
T orient(pt a, pt b, pt c) { return cross(b - a, c - a); }

// ENVOLVENTE CONVEXA

// para aceptar puntos colineales cambia a >=
// returns true if point r is on the left side of line pq
bool ccw(pt p, pt q, pt r) {
	return orient(p, q, r) > 0;
}

// devuelve un polígono con la envolvente convexa de una nube de puntos P.
vector<pt> convexHull(vector<pt> & P) {
	int n = int(P.size()), k = 0;
	vector<pt> H(2 * n);
	sort(P.begin(), P.end());
	// build lower hull
	for (int i = 0; i < n; ++i) {
		while (k >= 2 && !ccw(H[k - 2], H[k - 1], P[i])) --k;
		H[k++] = P[i];
	}
	// build upper hull
	for (int i = n - 2, t = k + 1; i >= 0; --i) {
		while (k >= t && !ccw(H[k - 2], H[k - 1], P[i])) --k;
		H[k++] = P[i];
	}
	H.resize(k);
	return H;
}

void resuelveCaso() {
	double len;
	int n;
	cin >> len >> n;
	vector<pt> ptos;
	double x, y;
	for (int i = 0; i < n; ++i) {
		cin >> x >> y;
		ptos.push_back({ x,y });
	}
	vector<pt> envolvente = convexHull(ptos);
	double d = 0;
	for (int i = 0; i < envolvente.size(); ++i) {
		d += dist(envolvente[i], envolvente[(i + 1) % envolvente.size()]);
	}
	if(d < len) cout << fixed << setprecision(5) << len << "\n";
	else cout << fixed << setprecision(5) << d << "\n";
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	std::ofstream out("salida.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int c;
	cin >> c;
	while(c--)
		resuelveCaso();
	
#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}