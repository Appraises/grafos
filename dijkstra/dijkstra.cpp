#include <bits/stdc++.h> // 1. Includes sempre no topo
using namespace std;

// 2. Macros e Definições logo abaixo dos includes
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define dbg(x) (cout << #x << " = " << x << endl);
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

typedef struct area {
    pair<int, int> 
} area;

void dijkstra(int source, int sink, vector<int> dist, vector<vector<pair<int, int>>> &grafo) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[source] = 0;

    pq.push({dist[source], source});

    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        for(auto [v, peso] : grafo[u]) {
            if(dist[v] > d + peso) {
                dist[v] = d + peso;
                pq.push({dist[v], v});
            }
        }
    }


}

// 3. APENAS UMA função main
int main() {
    _ // Ativa o I/O rápido
    pair<int, int> inicioXY;
    pair<int, int> finalXY;
    int contador = 0;

    int xi, yi;
    cin >> xi >> yi;

    inicioXY = {xi, yi};

    int xf, yf;
    cin >> xf >> yf;

    finalXY = {xf, yf};

    int n;
    cin >> n;

    vector< pair<int, pair<int, pair<int,int>>> > vetorAreas(n);

    for(int i = 0; i < n; i++) {
        contador++;


        int pex, pey;
        cin >> xi >> yi;

        int pdx, pdy;
        cin >> xf >> yf;

        

    }

    vector<vector<pair<int, int>>> grafo(n + 2); // pair<peso, vizinho>
    vector<int> dist(n, LINF);

    
    dijkstra(0, n + 1, dist, grafo);


    return 0;
}