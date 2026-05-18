#include <bits/stdc++.h> // 1. Includes sempre no topo
using namespace std;

// 2. Macros e Definições logo abaixo dos includes
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define dbg(x) (cout << #x << " = " << x << endl);
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

int bfs(int inicio,  vector<vector<int>> &grafo, vector<int> &cor, vector<int> &niveis, vector<ll> &niveisAcumulado, vector<int> &numerosArray, int qtdDigitos) {
  queue<int> q;
  cor[qtdDigitos - inicio - 1] = 0;
  niveisAcumulado[qtdDigitos - inicio - 1] = numerosArray[inicio];
  niveis[qtdDigitos - inicio - 1] = 1;
  q.push(qtdDigitos - inicio - 1);
  int maior = -1;

 
    while(!q.empty()) {
        int verticeInicioFila = q.front();
        q.pop();
    
        for(auto u : grafo[verticeInicioFila]) {
            cor[u] = 1;
            niveis[u] = niveis[verticeInicioFila] + 1;
            q.push(u);
            niveisAcumulado[u] = (ll)niveisAcumulado[verticeInicioFila] * 10 + numerosArray[qtdDigitos - u - 1];
        
            if(niveisAcumulado[u] % 25 == 0) {
                maior = max(maior, niveis[u]);
            }
        }
   
    }
    return maior;
}

// 3. APENAS UMA função main
int main() {
    _ // Ativa o I/O rápido
    int t;
    cin >> t;

    while(t--) {
        ll n;
        cin >> n;

        ll copiaN = n;
        
        int qtdDigitos = (n == 0) ? 1 : (int)log10(abs(n)) + 1;
        
        vector<vector<int>> grafo(qtdDigitos);
        vector<int> cor(qtdDigitos);
        vector<int> niveis(qtdDigitos);
        vector<ll> niveisAcumulado(qtdDigitos);
        vector<int> numerosInvertidos;
        int contadorDigitos = 0;

        if(copiaN == 0) {
            numerosInvertidos.push_back(0);
        }

    while(copiaN > 0) {
        int ni = copiaN % 10;
        numerosInvertidos.push_back(ni);
        copiaN /= 10;
    }
    
      while(n > 0) {
        int ni = n % 10;
        int nAtual = n;
       
        int i = 1;
        while(nAtual > 0) {
            if(contadorDigitos + i < qtdDigitos) {
                grafo[contadorDigitos + i].push_back(contadorDigitos);
            }
            
            nAtual /= 10;
            i++;
        }
       
       
        n /= 10;
        contadorDigitos++;
      }
     
      int menor = INF;
      reverse(numerosInvertidos.begin(), numerosInvertidos.end());
      vector<int> numerosArray = numerosInvertidos;
      for(int i = 0; i < qtdDigitos; i++) {
          int qtdMantidos = bfs(i, grafo, cor, niveis, niveisAcumulado, numerosArray, qtdDigitos);
          if(qtdMantidos != -1) {
              int qtdPrecisa = qtdDigitos - qtdMantidos;
              menor = min(menor, qtdPrecisa);
          }

        cor.assign(qtdDigitos, 0);
        niveis.assign(qtdDigitos, 0);
        niveisAcumulado.assign(qtdDigitos, 0);
      }
     
      cout << menor << endl;
    }
    return 0;
}

// Solução funciona mas toma TLE