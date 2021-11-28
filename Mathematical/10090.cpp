#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

long long int extendedEuclidRec(long long int a, long long int b, long long int &u, long long int &v) {
    if (!b) {
        u = 1;
        v = 0;
        return a;
    }
    long long int r = extendedEuclidRec(b, a % b, u, v);
    long long int uAux = v;
    long long int vAux = u - (a / b) * v;
    u = uAux;
    v = vAux;
    return r;
}

bool rC(){
    long long int n, c1, n1, c2, n2;
    cin >> n;
    if(n == 0) return false;
    cin >> c1 >> n1 >> c2 >> n2;
    long long int u, v;
    long long int d = extendedEuclidRec(n1,n2,u,v);
    if (n % d != 0) cout << "failed\n";
    else {
        u = u * n / d;
        v = v * n / d;
        n1 = n1 / d;
        n2 = n2 / d;
        // Tenemos que ver las soluciones de los extremos
        long long int aux1 = ceil(-(double)u/n2);
        long long int aux2 = floor((double)v/n1);
        if(aux1 > aux2) // No hay solución con u,v positivos
            cout << "failed\n";
        else {
            long long int ext1 = c1 * (u + n2*aux1) + c2 * (v - n1*aux1);
            long long int ext2 = c1 * (u + n2*aux2) + c2 * (v - n1*aux2);
            if(ext1 < ext2){
                cout << u + n2*aux1 << " " << v - n1*aux1 << "\n";
            }
            else{
                cout << u + n2*aux2 << " " << v - n1*aux2 << "\n";
            }
        }
    }
    return true;
}

int main(){
    while(rC());
    return 0;
}