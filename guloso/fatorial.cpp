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

    int valorEscolha;
    int fatorial;
    vector<int> escolhas;

    int k = 1;
    while(n > 0) {
        fatorial = 1;
        for(int j = 1; j <= k; j++) { // Fatorial de k
            fatorial *= j;
        }

        if(fatorial <= n) { // Se o fatorial de k, for menor ou igual
            valorEscolha = fatorial; // eu salvo a escolha, já que ele pode ser o maior
        } else {
            escolhas.push_back(k - 1); // no momento que ele passou pra cá, fatorial fica maior que o n 
            k = 1; // Resetamos o k pra podermor achar o próximo fatorial
            n -= valorEscolha;
        }
        
        k++;
    }

    cout << escolhas.size() << endl;

    return 0;
}