#include <bits/stdc++.h> // 1. Includes sempre no topo
using namespace std;

// 2. Macros e Definições logo abaixo dos includes
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define dbg(x) (cout << #x << " = " << x << endl);
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

void dfs(int inicio, vector<vector<int>> &grafo, vector<int> &cor, int caminhoAtual, int &caminhoMaximo, int &ultimoVertice) {
    cor[inicio] = 1;

    for(auto u : grafo[inicio]) {
        if(cor[u] == 0) {
            cor[u] = 1;
            dfs(u, grafo, cor, caminhoAtual + 1, caminhoMaximo, ultimoVertice);
            // cout << caminhoAtual << endl;
        }
    }

    if(caminhoAtual > caminhoMaximo) {
        caminhoMaximo = caminhoAtual;
        ultimoVertice = inicio;
    }

    cor[inicio] = 2;
}

// 3. APENAS UMA função main
int main() {
    _ // Ativa o I/O rápido
    int n;
    cin >> n;

    vector<vector<int>> grafo(n);
    vector<int> cor(n, 0);

    int caminhoMaximo = -1;
    int ultimoVertice = -1;

    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        u--;
        v--;

        grafo[u].push_back(v);
        grafo[v].push_back(u);
    }

    // Rodaremos uma dfs uma vez pra ir até uma das pontas da árvore, depois só preciso rodar de novo
    // pra achar o diâmetro

    dfs(0, grafo, cor, 0, caminhoMaximo, ultimoVertice);
    caminhoMaximo = 0;
    for(int i = 0; i < n; i++) {
      cor[i] = 0;
    }
    dfs(ultimoVertice, grafo, cor, 0, caminhoMaximo, ultimoVertice);

    cout << caminhoMaximo << endl;

    return 0;
}