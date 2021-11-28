#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long int bin(int n, int m){
    long long int f = n;
    long long int limitn = max(m, n - m);
    long long int num = n - 1;
    long long int den = min(m, n - m);
    while(num != limitn && den != 1){
        if(f % den == 0) {
            f /= den;
            --den;
        }
        else{
            f *= num;
            --num;
        }
    }
    if(num != limitn) {
        while(num != limitn){
            f *= num;
            --num;
        }
    }
    if(den != 1) {
        while(den != 1){
            f /= den;
            --den;
        }
    }
    return f;
}

bool rC(){
    int n,k;
    cin >> n >> k;
    if(n == 0 && k == 0) return false;
    
    cout << bin(n,k) << '\n';

    return true;
}

int main(){
    while(rC());
    return 0;
}