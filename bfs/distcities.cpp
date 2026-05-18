#include <bits/stdc++.h> // 1. Includes sempre no topo
using namespace std;

// 2. Macros e Definições logo abaixo dos includes
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define dbg(x) (cout << #x << " = " << x << endl);
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

int bfs(int inicio, int alvo, vector<vector<pair<int, int>>> &grafo, vector<int> &cor, vector<int> &distanciaAcumulado) {
  queue<int> q;
  cor[inicio] = 1;
  q.push(inicio);

  
  while(!q.empty()) {
    int verticeInicioFila = q.front();
    q.pop();
    
    for(auto v : grafo[verticeInicioFila]) {
      if(cor[v.second] == 0) {
        distanciaAcumulado[v.second] = distanciaAcumulado[verticeInicioFila] + v.first; // v.first indica a distância
        if(v.second == alvo) return distanciaAcumulado[v.second];
        cor[v.second] = 1;
        q.push(v.second);
      }
    }
  }

  return 0;
}

// 3. APENAS UMA função main
int main() {
    _ // Ativa o I/O rápido
    int n, a, b;
    cin >> n >> a >> b;
    
    vector<vector<pair<int, int>>> grafo(n);
    vector<int> distanciaAcumulado(n, 0);
    vector<int> cor(n, 0);
    
    for(int i = 0; i < n - 1; i++) {
      int u, v, w;
      cin >> u >> v >> w;
      
      u--;
      v--;
      
      grafo[u].push_back({w, v});
      grafo[v].push_back({w, u});
    }
    
    int distancia = bfs(a - 1, b - 1, grafo, cor, distanciaAcumulado);
    cout << distancia << endl;

    return 0;
}