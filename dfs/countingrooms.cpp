#include <bits/stdc++.h> // 1. Includes sempre no topo
using namespace std;

// 2. Macros e Definições logo abaixo dos includes
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define dbg(x) (cout << #x << " = " << x << endl);
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

int ehValido(int ni, int nj, int n, int m) {
    return(ni >= 0 && ni < n && nj >= 0 && nj < m);
}

void dfs(pair<int, int> inicio, vector<vector<char>> &matriz, vector<vector<int>> &cor, int n, int m) {
    cor[inicio.first][inicio.second] = 1;

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    for(int d = 0; d < 4; d++) {
        int ni = inicio.first + dx[d];
        int nj = inicio.second + dy[d];

        if(ehValido(ni, nj, n, m) && cor[ni][nj] == 0) {
            if(matriz[ni][nj] == '.') {
                cor[ni][nj] = 1;
                dfs({ni, nj}, matriz, cor, n, m);
            }
        }
    }
}

// 3. APENAS UMA função main
int main() {
    _ // Ativa o I/O rápido
    int n, m;
    cin >> n >> m;
    vector<vector<char>> matriz(n, vector<char>(m));
    vector<vector<int>> cor(n, vector<int>(m, 0));
    vector<pair<int, int>> coordenadasChao;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            char ci;
            cin >> ci;

            matriz[i][j] = ci;

            if(ci == '.') {
                coordenadasChao.push_back({i, j}); // Tem chão nessas coordenadas aí
            }
        }
    }

    int contadorDfs = 0;
    for(int i = 0; i < coordenadasChao.size(); i++) {
        if(cor[coordenadasChao[i].first][coordenadasChao[i].second] == 0) {
            contadorDfs++;
            dfs(coordenadasChao[i], matriz, cor, n, m);
        }
    }

    cout << contadorDfs << endl;

    return 0;
}