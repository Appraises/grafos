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
        int a, b;
        cin >> a >> b;
        int passos = 0;

        while(a != b) {
            int diff = b - a;
            // dbg(diff);
            
            if(diff > 0) {
                if(diff % 2 != 0) {
                    a += diff;
                } else {
                    a += diff - 1;
                }
            } else {
                if(diff % 2 == 0) {
                    a -= abs(diff);
                } else {
                    a -= abs(diff) + 1;
                }
            }
            passos++;
        }

        cout << passos << endl;

    }


    return 0;
}