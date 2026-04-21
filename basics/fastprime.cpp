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

    int q;
    cin >> q;
    while(q--) {
        ll n;
        cin >> n;
    
        int flag = 0;
    
        for(ll i = 2; i * i <= n; i++) {
            if(n % i == 0) {
                flag = 1; // Não é primo porque alguém dividiu por ele
                break;
            }
        }
    
        if(flag) cout << "Not Prime" << endl;
        else cout << "Prime" << endl;
        
    }

    

    return 0;
}