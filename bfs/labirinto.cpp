#include <bits/stdc++.h> // 1. Includes sempre no topo
using namespace std;
 
// 2. Macros e Definições logo abaixo dos includes
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define dbg(x) (cout << #x << " = " << x << endl);
typedef long long ll;
 
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
 
int ehValido(int x, int y, int n, int m) {
    return (x >= 0 && x < n && y >= 0 && y < m);
}
 
void bfs(pair<int, int> inicio, pair<int, int> fim, vector<vector<int>> &matriz, vector<vector<int>> &cor, vector<vector<char>> &mov, vector<vector<int>> &niveis, int n, int m) {
    cor[inicio.first][inicio.second] = 1;
    queue<pair<int, int>> q;
    q.push({inicio.first, inicio.second});
    mov[inicio.first][inicio.second] = 0;
    niveis[inicio.first][inicio.second] = 0;
 
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
 
    while(!q.empty()) {
        pair<int, int> coordenadaInicioFila = q.front();
        int i = coordenadaInicioFila.first;
        int j = coordenadaInicioFila.second;
        q.pop();
 
        for(int d = 0; d < 4; d++) {
            int ni = i + dx[d];
            int nj = j + dy[d];
 
            if(ehValido(ni, nj, n, m) && cor[ni][nj] == 0) {
                if(matriz[ni][nj] != '#') {
                    cor[ni][nj] = 1;
                    char escolha;
 
                    if(dx[d] == 1) {
                        escolha = 'D';
                    } else if(dx[d] == -1) {
                        escolha = 'U';
                    } else if(dy[d] == -1) {
                        escolha = 'L';
                    } else {
                        escolha = 'R';
                    }
 
                    mov[ni][nj] = escolha;
                    niveis[ni][nj] = niveis[i][j] + 1;
                    q.push({ni, nj});
 
                    if(ni == fim.first && nj == fim.second) {
                        return;
                    }
                }
            }
        }
    }
 
}
 
string reconstruirCaminho(pair<int, int> inicio, pair<int, int> fim, vector<vector<char>> &mov) {
    string caminho;
    int i = fim.first;
    int j = fim.second;
 
    while(!(i == inicio.first && inicio.second == j)) {
        char c = mov[i][j];
        caminho.push_back(c);
 
        if(c == 'D') {
            i--;
        } else if(c == 'U') {
            i++;
        } else if(c == 'R') {
            j--;
        } else {
            j++;
        }
    }
 
    reverse(caminho.begin(), caminho.end());
    return caminho;
}
 
// 3. APENAS UMA função main
int main() {
    _ // Ativa o I/O rápido
    int n, m;
    cin >> n >> m;
 
    vector<char> mapa;
    pair<int, int> inicio;
    pair<int, int> fim;
 
    vector<vector<int>> matriz(n, vector<int>(m)); 
    vector<vector<int>> cor(n, vector<int>(m, 0));
    vector<vector<char>> mov(n, vector<char>(m, 0));
    vector<vector<int>> niveis(n, vector<int>(m, -1));
 
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            char caractere;
            cin >> caractere;
 
            if(caractere == 'A') {
                inicio = {i, j};
            } else if (caractere == 'B') {
                fim = {i, j};
            }
 
            matriz[i][j] = caractere;
        }
    }
 
    string caminho;
    bfs(inicio, fim, matriz, cor, mov, niveis, n, m);
    if(niveis[fim.first][fim.second] == -1) {
        cout << "NO" << endl;
    } else {
        caminho = reconstruirCaminho(inicio, fim, mov);
        cout << "YES" << endl;
        cout << caminho.size() << endl;
        cout << caminho << endl;
    }
 
    return 0;
}