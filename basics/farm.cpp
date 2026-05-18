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
        int n;
        cin >> n;

        if(n % 2 != 0) {
            cout << 0 << endl;
        } else {
            int maxVacas = n / 4;
            int qtdCombinacoes = 0;
            if(maxVacas < 0) {
                cout << 1 << endl;
                return 0;
            }

            while(maxVacas > 0) {
                qtdCombinacoes++;
                maxVacas--;
            }

            cout << qtdCombinacoes + 1 << endl;
        }
    }

    return 0;
}