#include <iostream>
#include <vector>

using namespace std;


long long int exp(long long int b, long long int p, long long int m){
    if (m == 1) return 0;
    if(p == 1) return (b%m);
    if(p == 0) return 1;
    long long int res = exp(b, p/2, m)%m;
    if(p %2 == 0)
        return (res * res)%m;
    return (((res * res)%m) * b)%m;
}

bool rC(){
    int b,p,m;
    cin >> b >> p >> m;
    if(!cin) return false;
    cout << exp(b,p,m) << '\n';
    return true;
}

int main(){
    while(rC());
    return 0;
}
