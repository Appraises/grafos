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

    // 5
    // 1 2 3 -1 -2

    while(t--) {
        int n;
        cin >> n;

        vector<int> vetor(n);

        int p1 = 0;
        int p2 = 0;

        for(int i = 0; i < n; i++) {
            int ni;
            cin >> ni;

            vetor[i] = ni;
        }

        
        ll sequenciaAlternada = 0;
        int primeiro = 1;
        
        while(p1 != n || p2 != n) {
            int maiorAteAgora = INT_MIN;
            int entrouP = 0;
            while(p1 < n && vetor[p1] > 0) {
                maiorAteAgora = max(maiorAteAgora, vetor[p1]);
                p1++;
                entrouP = 1;
            }

            if(entrouP) sequenciaAlternada += maiorAteAgora;
            maiorAteAgora = INT_MIN;

            p2 = p1;
            int entrouN = 0;
            while(p2 < n && vetor[p2] < 0) {
                maiorAteAgora = max(maiorAteAgora, vetor[p2]);
                entrouN = 1;
                p2++;
            }

            if(entrouN) sequenciaAlternada += (ll)maiorAteAgora;
            
            p1 = p2;
        }

        cout << sequenciaAlternada << endl;
    }

    return 0;
}