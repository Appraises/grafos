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
    int n, q;
    cin >> n >> q;
    // multiset é um conjunto que permite repetições, como ele sempre fica ordenado em uma
    // árvore autobalanceante, que usa uma árvore rubro negra, conseguimos garantir
    // inserção e remoção em log n
    multiset<int> tamanhos;
    for(int i = 0; i < n; i++) {
        int tamanhoNi;
        cin >> tamanhoNi;

        // inserimos no nosso conjunto, que vai formando nossa árvore rubro negra
        tamanhos.insert(tamanhoNi);
    }

    while(q--) {
        int x;
        cin >> x;

        // lower bound percorre a árvore autobalanceante e encontra o rpimeiro valor >= x
        auto it = tamanhos.lower_bound(x);

        if(it == tamanhos.end()) {
            cout << "-1" << endl;
        } else {
            cout << *it << endl;
            tamanhos.erase(it);
        }

    }

    return 0;
}