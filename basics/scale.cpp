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
    int t;
    cin >> t;

    while(t--) {
        int n, k;
        cin >> n >> k;

        vector<vector<int>> matriz(n, vector<int>(n));

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                int ni;
                cin >> ni;
                matriz[i][j] = ni;
            }
        }

        int tamanhoNovaMatriz = n / k;

        vector<vector<int>> novaMatriz(tamanhoNovaMatriz, vector<int>(tamanhoNovaMatriz));
        for(int i = 0; i < tamanhoNovaMatriz; i++) {
            for(int j = 0; j < tamanhoNovaMatriz; j++) {
                if(matriz[i*k][j*k] == 1) {
                    novaMatriz[i][j] = 1;
                } else {
                    novaMatriz[i][j] = 1;
                }

                cout << novaMatriz[i][j] << endl;
            }
        }

    }


    return 0;
}