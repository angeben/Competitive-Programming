#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <string.h>
#include <algorithm>
using namespace std;

#define MAX_N 100010
std::string T;
int n;
int RA[MAX_N], tempRA[MAX_N];
int SA[MAX_N], tempSA[MAX_N];
int c[MAX_N];
int LCP[MAX_N];

void countingSort(int k) {
	int i, sum, maxi = std::max(300, n); // up to 255 ASCII
	memset(c, 0, sizeof c);
	for (i = 0; i < n; ++i)
		++c[i + k < n ? RA[i + k] : 0];
	for (i = sum = 0; i < maxi; ++i) {
		int t = c[i]; c[i] = sum; sum += t;
	}
	for (i = 0; i < n; ++i)
		tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
	for (i = 0; i < n; ++i)
		SA[i] = tempSA[i];
}

// Construccion del suffix array
void constructSA() {
	int i, k, r;
	for (i = 0; i < n; ++i) RA[i] = T[i];
	for (i = 0; i < n; ++i) SA[i] = i;
	for (k = 1; k < n; k <<= 1) {
		countingSort(k);
		countingSort(0);
		tempRA[SA[0]] = r = 0;
		for (i = 1; i < n; ++i)
			tempRA[SA[i]] =
			(RA[SA[i]] == RA[SA[i - 1]] &&
				RA[SA[i] + k] == RA[SA[i - 1] + k]) ?
			r : ++r;
		for (i = 0; i < n; ++i)
			RA[i] = tempRA[i];
		if (RA[SA[n - 1]] == n - 1) break;
	}
}

void computeLCP() {
	int Phi[MAX_N];
	int PLCP[MAX_N];
	int i, L;
	Phi[SA[0]] = -1;
	for (i = 1; i < n; ++i)
		Phi[SA[i]] = SA[i - 1];
	for (i = L = 0; i < n; ++i) {
		if (Phi[i] == -1) { PLCP[i] = 0; continue; }
		while (T[i + L] == T[Phi[i] + L]) ++L;
		PLCP[i] = L;
		L = std::max(L - 1, 0);
	}
	for (i = 0; i < n; ++i)
		LCP[i] = PLCP[SA[i]];
}

void resuelveCaso() {
	cin >> T;
	T.push_back('#');
	n = T.size();
	constructSA();
	computeLCP();
	int sol = 0;
	for (int i = 0; i < n; ++i) {
		if (LCP[i] > sol)
			sol = LCP[i];
	}
	cout << sol << "\n";
}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	//std::ofstream out("salida.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	//auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int c;
	cin >> c;
	while (c--)
		resuelveCaso();

#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	//std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif

	return 0;
}