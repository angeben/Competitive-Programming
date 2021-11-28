#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <utility>
#include <queue>
using namespace std;

struct medic{
	string na;
	int f, act, ord;
	bool operator <(medic const & b) const{
		return (this->act > b.act) || (this->act == b.act && this->ord > b.ord);
	}
};

void resolverCaso(int const&  n, int const&  k) {
	string na = ""; int f=0;
	vector<pair<int, string>> v;
	priority_queue<medic, vector<medic>> q;
	for (int i = 0; i < n; ++i) {
		cin >> na >> f;
		q.push({na, f, f, i});
	}
	medic m;
	for (int i = 1; i <= k; ++i) {
		m = q.top();
		cout << m.act << ' ' << m.na << '\n';
		q.pop();
		m.act = m.act + m.f;
		q.push(m);
	}
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	std::ofstream out("salida.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int T, n, k;
	cin >> T;
	while (T != 0) {
		cin >> n >> k;
		resolverCaso(n, k);
		T--;
	}
	
	#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}

