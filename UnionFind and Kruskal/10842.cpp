#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

using arista = pair<int,pair<int,int>>;

int caso = 0;


struct UFDS {
    vector<int> p;
    int numSets;
    UFDS(int n) : p(n, 0), numSets(n) {
        for (int i = 0; i < n; ++i) p[i] = i;
    }
    int find(int x) {
        return (p[x] == x) ? x : p[x] = find(p[x]);
    }
    void merge(int x, int y) {
        int i = find(x), j = find(y);
        if (i == j) return;
        p[i] = j;
        --numSets;
    }
};


void rc(){
    caso++;
    int n,m;
    cin >> n >> m;
    vector<arista> aristas(m);
    int u,v,c;
    for(int i = 0; i < m; ++i){
        cin >> u >> v >> c;
        aristas[i] = {c, {u,v}};
    }

    sort(aristas.begin(), aristas.end());
    reverse(aristas.begin(), aristas.end());

    UFDS uf(n);
    int min = 100000000;
    for(auto ar: aristas){
        if(uf.find(ar.second.first) != uf.find(ar.second.second)){
            uf.merge(ar.second.first, ar.second.second);
            if(min > ar.first) min = ar.first;
            if(uf.numSets == 1) break;
        }
    }

    printf("Case #%i: %i\n", caso, min);

}

int main(){
    int n; cin >> n;
    while(n--)rc();
    return 0;
}