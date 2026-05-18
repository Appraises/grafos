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
    int contador = 0;

    vector<string> conversas(n);

    for(int i = 0; i < n; i++) {
        string conversa;
        cin >> conversa;

        conversas[i] = conversa;
    }

    unordered_set<string> jaVistos;

    for(int i = n - 1; i >= 0; i--) {
        if(!jaVistos.count(conversas[i])) {
            cout << conversas[i] << endl;
            jaVistos.insert(conversas[i]);
        }
    }

    return 0;
}