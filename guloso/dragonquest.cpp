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
        int h, n, m;
        cin >> h >> n >> m;
        int flag = 0;

        while(h > 0) {
            if(n == 0 && m == 0) {
                cout << "NO" << endl;
                flag = 1;
                break;
            }

            int melhorEscolha;
            int escolhaVoid = h / 2 + 10;
            int escolhaTrovao = h - 10;

            
            if(n > 0) {
                melhorEscolha = escolhaVoid;
                n--;
            } else {
                melhorEscolha = escolhaTrovao;
                m--;
            }
            if (m * 10 >= h) {
                melhorEscolha = escolhaTrovao;
                m--;
            }
            
            h = melhorEscolha;
        }


        if(!flag) cout << "YES" << endl;
    }

    return 0;
}