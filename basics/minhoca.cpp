#include <bits/stdc++.h> // 1. Includes sempre no topo
using namespace std;

// 2. Macros e Definições logo abaixo dos includes
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define dbg(x) (cout << #x << " = " << x << endl);
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

// 3. APENAS UMA função main
int main() {
    _ // Ativa o I/O rápido

    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> matrizMinhoca(n, vector<int>(m));
    vector<int> somaLinha(n, 0);
    vector<int> somaColuna(m, 0);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int qtdMinhoca;
            cin >> qtdMinhoca;

            matrizMinhoca[i][j] = qtdMinhoca;
            somaLinha[i] += qtdMinhoca;
            somaColuna[j] += qtdMinhoca;
        }
    }

    int maiorLinha = -1;
    int maiorColuna = -1;

    for(int i = 0; i < n; i++) {
        // cout << somaLinha[i] << endl;
        if(somaLinha[i] > maiorLinha) maiorLinha = somaLinha[i];
    }

    for(int i = 0; i < m; i++) {
        // cout << somaColuna[i] << endl;
        if(somaColuna[i] > maiorColuna) maiorColuna = somaColuna[i];
    }

    if(maiorLinha > maiorColuna) {
        cout << maiorLinha << endl;
    } else {
        cout << maiorColuna << endl;
    }


    return 0;
}