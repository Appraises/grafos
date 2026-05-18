#include <bits/stdc++.h> // 1. Includes sempre no topo
using namespace std;

// 2. Macros e Definições logo abaixo dos includes
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define dbg(x) (cout << #x << " = " << x << endl);
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

int bfs(int inicio, vector<vector<int>> &grafo, vector<int> &cor, vector<int> &niveis, int alvo) {
    queue<int> fila;
    int contador = 0;
    int achou = 0;
    cor[inicio] = 1;    
    fila.push(inicio);

    while(!fila.empty()) {
        int verticeExplorar = fila.front();
        fila.pop();
        for(auto u : grafo[verticeExplorar]) {
            if(cor[u] == 0) {
                cor[u] = 1;
                niveis[u] = niveis[verticeExplorar] + 1;
                fila.push(u);
                if(u == alvo) {
                    achou = 1;
                    break;
                };
            }
        }
    }

    return achou;
}

// 3. APENAS UMA função main
int main() {
    _ // Ativa o I/O rápido
    int n, d;
    cin >> n >> d;

    vector<int> cor(n, 0);
    vector<int> niveis(n, 0);

    vector<vector<int>> grafo(n);

    string lilliesOUN;
    cin >> lilliesOUN;
    int a = 1;
    int x = 0;
    int pulos = d;
    int contadorLillies = 0;
    for(int i = 0; i < n; i++) {
        if(lilliesOUN[i] == '1') {
            for(int j = i + 1; j <= i + d && j < n; j++) {
                if(lilliesOUN[j] == '1') {
                    grafo[i].push_back(j);
                }
            }
        }
    }

    if(!bfs(0, grafo, cor, niveis, n - 1)) cout << -1 << endl;
    else cout << niveis[n - 1] << endl;

    return 0;
}