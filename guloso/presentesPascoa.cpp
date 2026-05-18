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
    int n;
    cin >> n;

    int c;
    cin >> c;

    vector<int> valorOvos(n);

    for(int i = 0; i < n; i++) {
        int ni;
        cin >> ni;

        valorOvos[i] = ni;
    }

    sort(valorOvos.begin(), valorOvos.end());

    int contador = 0;
    int i = 0;
    while(c > 0 && i != n) {
        if(valorOvos[i] <= c) {
            c -= valorOvos[i];
            contador++;
        }

        i++;
    }

    cout << contador << endl;

    return 0;
}