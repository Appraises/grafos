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
        int n;
        cin >> n;

        vector<int> arrayNumeros(n);
        vector<int> balde6;
        vector<int> baldeNAO23;
        vector<int> balde2;
        vector<int> balde3;

        for(int i = 0; i < n; i++) {
            int ni;
            cin >> ni;
            arrayNumeros[i] = ni;

            if(ni % 6 == 0) {
                balde6.push_back(ni);
            }

            else if(ni % 2 == 0) {
                balde2.push_back(ni);
            }

            else if(ni % 3 == 0 ) {
                balde3.push_back(ni);
            }

            else if(ni % 2 != 0 && ni % 2 != 0) {
                baldeNAO23.push_back(ni);
            }
        }

        for(auto v : balde6) {
            cout << v << " ";
        }

        for(auto v : balde3) {
            cout << v << " ";
        }

        for(auto v : baldeNAO23) {
            cout << v << " ";
        }

        for(auto v : balde2) {
            cout << v << " ";
        }

        cout << "\n";
    }

    return 0;
}