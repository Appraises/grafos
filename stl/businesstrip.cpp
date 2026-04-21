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
    int k;
    cin >> k;

    list<int> lista;

    for(int i = 0; i < 12; i++) {
        int r;
        cin >> r;
        lista.push_back(r); 
    }

    lista.sort(greater<int>());
    int contador = 0;
    int soma = 0;
    int flag = 0;
    for(int valor : lista) {
        // dbg(soma);
        if(soma >= k) {
            flag = 1;
            break;
        } 
        soma += valor;
        contador++;
    }

    if(soma < k) cout << -1 << endl;
    else cout << contador << endl;
    

    return 0;
}