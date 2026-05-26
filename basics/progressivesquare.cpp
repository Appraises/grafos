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
        int n, c, d;
        cin >> n >> c >> d;
        vector<int> numeros(pow(n, 2));


        for(int i = 0; i < pow(n, 2); i++) {
            int ni;
            cin >> ni;

            numeros[i] = ni;
        }

        sort(numeros.begin(), numeros.end());

        int a11 = numeros[0];

        int L = 0;
        int R = 1;

        for(int i = 0; i < pow(n, 2); i++) {
            if((numeros[L] + b == numeros[R] || numeros[L] + c == numeros[R]) && (numeros[L] + b == numeros[R+1] || numeros[L] + c == numeros[R+1])) {
                L++;
                R++;
            }
        }
       
    }

    return 0;
}