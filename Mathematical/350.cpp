#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int f(unsigned int z, unsigned int i, unsigned int m, unsigned int x0){
    return (z * x0 + i) % m;
}

typedef pair<unsigned int, unsigned int> uu;
// <µ,λ> : <inicio ciclo, longitud ciclo>
uu floydCycleFinding(unsigned int z, unsigned int i, unsigned int m, unsigned int x0) {
    int tortoise = f(z, i, m, x0), hare = f(z, i, m, f(z, i, m, x0));
    while (tortoise != hare) {
        tortoise = f(z, i, m, tortoise); hare = f(z, i, m, f(z, i, m, hare));
    }
    int mu = 0; hare = x0;
    while (tortoise != hare) {
        tortoise = f(z, i, m, tortoise); hare = f(z, i, m, hare); mu++;
    }   
    int lambda = 1; hare = f(z, i, m, tortoise);
    while (tortoise != hare) {
        hare = f(z, i, m, hare); lambda++;
    }
    return uu(mu, lambda);
}

bool rC(int caso){
    int z, i, m, l;
    cin >> z >> i >> m >> l;
    if(z == 0 && i == 0 && m == 0 && l == 0) return false;
    uu par = floydCycleFinding(z, i, m, l);
    cout << "Case " << caso << ": " << par.second << "\n";
    return true;
}

int main(){
    int caso = 1;
    while(rC(caso)) ++caso;
    return 0;
}