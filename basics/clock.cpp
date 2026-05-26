#include <bits/stdc++.h> // 1. Includes sempre no topo
using namespace std;

// 2. Macros e Definições logo abaixo dos includes
#define _ ios_base::sync_withstdio(0);cin.tie(0);
#define endl '\n'
#define dbg(x) (cout << #x << " = " << x << endl);
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

// 3. APENAS UMA função main
int main() {
     // Ativa o I/O rápido

    int t;
    cin >> t;

    while(t--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        // qualquer valor que estiver dentro de um dado intervalo (a, b), e for alcançado por
        // um valor c ou d, necessariamente tivemos uma intersecção, e o mesmo vale pro oposto

        int minimo = min(a, b);
        int maximo = max(a, b);

        if((c > minimo && c < maximo)) { // Pelo menos um deles tá na parte de baixo da reta
            if(d > maximo || d < minimo) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        } else if((d > minimo && d < maximo)) { // Pelo menos um deles tá na parte de baixo da reta
            if(c > maximo || c < minimo) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }  else {
            cout << "NO" << endl;
        }
        
    }

    return 0;
}