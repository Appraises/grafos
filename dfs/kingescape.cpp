#include <bits/stdc++.h> // 1. Includes sempre no topo
using namespace std;

// 2. Macros e Definições logo abaixo dos includes
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define dbg(x) (cout << #x << " = " << x << endl);
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

int ehValido(int r, int c, int n, int m) {
  return (r >= 0 && r < n && c >= 0 && c < m); 
}


int dfs(pair<int, int> inicio, pair<int, int> alvo, vector<vector<int>> &tabuleiro, vector<vector<int>> &cor, int n, int m) {
  cor[inicio.first][inicio.second] = 1;
  if(inicio.first == alvo.first && inicio.second == alvo.second) return 1;
  
  vector<int> dx = {1, -1, 0, 0, 1, -1, 1, -1};
  vector<int> dy = {0, 0, 1, -1, -1, 1, 1, -1};
  
  for(int i = 0; i < 8; i++) {
    int nx = inicio.first + dx[i];
    int ny = inicio.second + dy[i];
    
    if(ehValido(nx, ny, n, m)) {
      if(cor[nx][ny] == 0 && tabuleiro[nx][ny] == 0) {
        if(dfs({nx, ny}, alvo, tabuleiro, cor, n, m)) {
          return 1;
        }
      }
    }
  }


  return 0;
}

// 3. APENAS UMA função main
int main() {
    _ // Ativa o I/O rápido
   
    int dimensoesTabuleiro;
    cin >> dimensoesTabuleiro;
   
    int x, y;
    cin >> x >> y;
    pair<int, int> posRainha = {x - 1, y - 1};
   
    cin >> x >> y;
    pair<int, int> posRei = {x - 1, y - 1};

    cin >> x >> y;
    pair<int, int> posFinal = {x - 1, y - 1};
   
    vector<vector<int>> tabuleiro(dimensoesTabuleiro, vector<int>(dimensoesTabuleiro, 0)); // Matriz do tabuleiro, todo mundo começa zerado
    vector<vector<int>> cor(dimensoesTabuleiro, vector<int>(dimensoesTabuleiro, 0));
   
    for(int i = 0; i < dimensoesTabuleiro; i++) {
      for(int j = 0; j < dimensoesTabuleiro; j++) {
          if(i == posRainha.first) {
            tabuleiro[i][j] = 1;
          } else if (j == posRainha.second) {
            tabuleiro[i][j] = 1;
          } else if(abs(posRainha.first - i) == abs(posRainha.second - j)) {
            tabuleiro[i][j] = 1;
          }
      }
    }
    
    int encontrou = dfs({posRei.first, posRei.second}, {posFinal.first, posFinal.second}, tabuleiro, cor, dimensoesTabuleiro, dimensoesTabuleiro);
    if(encontrou) cout << "YES" << endl;
    else cout << "NO" << endl;


    return 0;
}