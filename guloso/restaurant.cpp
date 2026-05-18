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


    return 0;
}#include <bits/stdc++.h> // 1. Includes sempre no topo
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

    vector<pair<int, int>> conjuntoReservas(n);


    while(n--) {
        int l, r;
        cin >> l >> r;


        for(int i = 0; i < n; i++) {
            int flag = 1;
            if(!conjuntoReservas.empty()) {
                if(conjuntoReservas[i].first >= l || conjuntoReservas[i].second >= r) {
                    flag = 0;
                }
            }
        }
    }

    return 0;
} 