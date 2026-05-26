#include <bits/stdc++.h> // 1. Includes sempre no topo
using namespace std;

// 2. Macros e Definições logo abaixo dos includes
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define dbg(x) (cout << #x << " = " << x << endl);
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

void dfs(int inicio, vector<vector<int>> &grafo, vector<int> &cor, vector<int> &qtdSubordinados) {
    cor[inicio] = 1;
    qtdSubordinados[inicio] = 1;

    for(auto u : grafo[inicio]) {
        if(cor[u] == 0) {
            cor[u] = 1;
            dfs(u, grafo, cor, qtdSubordinados);
            qtdSubordinados[inicio] += qtdSubordinados[u];
        }

        cor[inicio] = 2;
    }
}

// 3. APENAS UMA função main
int main() {
    _ // Ativa o I/O rápido
    int n;
    cin >> n;

    vector<vector<int>> grafo(n);
    vector<int> cor(n, 0);
    vector<int> qtdSubordinados(n);

    for(int i = 1; i < n; i++) {
        int chefe;
        cin >> chefe;
        
        chefe--;
        // cout << chefe << "->" << i << endl;
        
        grafo[chefe].push_back(i);
        // cout << subordinadoDQ[i] << " ";
    }

    dfs(0, grafo, cor, qtdSubordinados);

    for(int i = 0; i < n; i++) {
        cout << qtdSubordinados[i] - 1 << " ";
    }
    return 0;
}