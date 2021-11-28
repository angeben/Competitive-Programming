#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;

int n,m;
int INF = 100000000;
int V; // vértices del grafo completo

vector<vector<pair<int,int>>> adjList;
vector<vector<int>> dist; // matriz de adyacencia del subgrafo
vector<vector<int>> memo; // tabla de DP
using vii = vector<pair<int,int>>;
using vi = vector<int>;
using vvi = vector<vi>;
using ii  = pair<int,int>;

void dijkstra(int s, vi &dista) {
    dista[s] = 0;
    priority_queue<ii, vii, greater<ii>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        ii front = pq.top(); pq.pop();
        int d = front.first, u = front.second;
        if (d > dista[u]) continue;
        for (auto a : adjList[u]) {
            if (dista[u] + a.first < dista[a.second]) {
                dista[a.second] = dista[u] + a.first;
                pq.push({dista[a.second], a.second});
            }
        }
    }   
}

// devuelve el coste de ir desde pos al origen (el vértice 0)
// pasando por todos los vértices no visitados (con un bit a 0)
int tsp(int pos, int visitados) {
    if (visitados == (1 << V) - 1) // hemos visitado ya todos los vértices
        return dist[pos][0]; // volvemos al origen
    if (memo[pos][visitados] != -1)
        return memo[pos][visitados];
    int res = 1000000000; // INF
    for (int i = 1; i < V; ++i)
        if (!(visitados & (1 << i))) // no hemos visitado vértice i
            res = min(res, dist[pos][i] + tsp(i, visitados | (1 << i)));
    return memo[pos][visitados] = res;
}

void rc(){
    cin >> n >> m;

    vector<vector<pair<int,int>>> list(n);
    int x,y,d;
    for(int i = 0; i < m;++i){
        cin >> x >> y >> d;
        list[x].push_back({d,y});
        list[y].push_back({d,x});
    }
    adjList = list;
    cin >> V;
    V = V+1;
    vector<int> tiendas(V);
    tiendas[0] = 0;
    for(int i = 1; i < V; ++i)
        cin >> tiendas[i];

    dist.assign(V, vector<int>(V,0));

    for(int i = 0; i < V; ++i){
        vector<int> ddist(n,INF);
        dijkstra(tiendas[i], ddist);
        for(int j = 0; j < V; ++j){
            dist[i][j] = ddist[tiendas[j]];
        }
        
    }

    memo.assign(V, vector<int>(1 << V, -1));
    cout << tsp(0, 1) << '\n';
}


int main(){
    int k;
    cin >> k;
    while(k--)rc();
    return 0;
}