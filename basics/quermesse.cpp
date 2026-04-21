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

    int n = 0;
    int np = 1;
    
    while(np != 0) {
        cin >> np;

        if(np != 0) {
            n++;
            vector<int> vetor(np, 0);
            
            cout << "Teste " << n << endl; 
            for(int i = 0; i < np; i++) {
                int numeroIngresso;
                cin >> numeroIngresso;
                vetor[i] = numeroIngresso;

                if(numeroIngresso == i + 1) {
                    cout << numeroIngresso << endl;
                }
            }
            cout << endl;
        }

    }
 

    return 0;
}