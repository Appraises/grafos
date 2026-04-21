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
        string a;
        string b;
        string c;
        int flag = 0;

        cin >> a >> b >> c;

        for(int i = 0; i < a.size(); i++) {
            if(c[i] == a[i]) {
                char guardar;
                guardar = b[i];
                b[i] = c[i];
                c[i] = guardar;
            } else if (c[i] == b[i]) {
                char guardar;
                guardar = a[i];
                a[i] = c[i];
                c[i] = guardar;
            } else {
                flag = 1;
                break;
            }
        
        }

        if(flag) cout << "NO" << endl;
        else cout << "YES" << endl;
        
    }

    return 0;
}