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

    int n, k;

    cin >> n >> k;
    vector<int> vetor;

    for(int i = 0; i < n; i++) {
        int v;
        cin >> v;

        vetor.push_back(v); 
    }

    set<vector<int>> conjuntoDeConjuntos;


    // Começando no indice j
    for(int j = 0; j < n; j++) {

        for(int mask = 0; mask < (1 << n); mask++) {
            // dbg(mask);
            // cout << "{";
            vector<int> freq(n + 1, 0);
            int qtd = 0;
            
            for(int i = 0; i < n; i++) {
                // dbg(i);
                // dbg(j);
                if(i <= j) {
                    if(abs(j - i) == 0 || abs(j - i) > k) { // Se a diferença entre i e j for maior do k
                        if((1 << i) & mask) {
                            freq[vetor[i]]++;
                            qtd++;
                            // cout << vetor[i];
                        }
                    }
                }
            }
    
            if(qtd > 0) conjuntoDeConjuntos.insert(freq);
            // cout << "}" << endl;
        }
    }

    cout << conjuntoDeConjuntos.size() % 998244353 << endl;

    
    return 0;
}