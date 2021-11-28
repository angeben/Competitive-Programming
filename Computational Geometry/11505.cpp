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
#include <string>
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

// TRANSFORMACIONES

pt translate(pt v, pt p) { return p + v; }

// scale p by a certain factor around a center c
pt scale(pt c, double factor, pt p) {
	return c + (p - c)*factor;
}

// rotate p by a certain angle a counter-clockwise around origin
pt rotate(pt p, double a) {
	return { p.x*cos(a) - p.y*sin(a), p.x*sin(a) + p.y*cos(a) };
}

// rotate 90º counterclockwise
pt perp(pt p) { return { -p.y, p.x }; }

struct line {
	pt v; T c;
	// from direction vector v and offset c
	line(pt v, T c) : v(v), c(c) {}
	// from equation ax + by = c
	line(T a, T b, T c) : v({ b,-a }), c(c) {}
	// from points p and q
	line(pt p, pt q) : v(q - p), c(cross(v, p)) {}

	T side(pt p) { return cross(v, p) - c; }

	double dist(pt p) { return abs(side(p)) / abs(v); }

	line translate(pt t) { return { v, c + cross(v,t) }; }

	pt proj(pt p) { return p - perp(v)*side(p) / sq(v); }
};

bool inter(line l1, line l2, pt & out) {
	T d = cross(l1.v, l2.v);
	if (d == 0) return false;
	out = (l2.v*l1.c - l1.v*l2.c) / d; // requires floating-point coordinates
	return true;
}

void resuelveCaso() {
	int n;
	cin >> n;
	pt c = { 0,0 };
	pt pos = { 0,0 };
	pt v = { 1,0 };
	string accion;
	int d;
	for (int i = 0; i < n; ++i) {
		cin >> accion >> d;
		if (accion == "fd") {
			pt vaux = v * d;
			pos = translate(pos, vaux);
		}
		else if (accion == "bk") {
			pt vaux = v * (-d);
			pos = translate(pos, vaux);
		}
		else if (accion == "lt") {
			double rad = d * PI / 180;
			v = rotate(v, rad);
		}
		else { // rt
			double rad = - (d * PI / 180);
			v = rotate(v, rad);
		}
	}
	cout << round(dist(pos,c)) << "\n";
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
	while (c--)
		resuelveCaso();

#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}