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
        int n, a, b;
        cin >> n >> a >> b;

        int qtdGastar = 0;
        if(n % 2 == 0) {
            if(n * a < (n/2) * b) {
                qtdGastar = n * a;
            } else {
                qtdGastar = b * (n/2);
            }
        } else {
            int quantosCabem = n/2;
            int quantosSobram = n % 2;

            if(n * a < ((n/2) * b + quantosSobram * a)) {
                qtdGastar = n * a;
            } else {
                qtdGastar = quantosCabem * b + quantosSobram * a;
            }
        }

        cout << qtdGastar << endl;
    }

    return 0;
}