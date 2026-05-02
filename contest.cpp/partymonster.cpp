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
        int c;
        cin >> c;

        int contadorAbre = 0;
        int contadorFecha = 0;
        string sequencia;
        cin >> sequencia;
        for(int i = 0; i < c; i++) {
            if(sequencia[i] == '(') {
                contadorAbre++;
            } else if (sequencia[i] == ')'){
                contadorFecha++;
            }
        }

        //dbg(contadorAbre);
        //dbg(contadorFecha);
        if(contadorAbre == contadorFecha) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }


    return 0;
}