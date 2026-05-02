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
        int uso1Passo = 1; // Ele começa tendo o direito a dar um passo curto
        pair<int, int> coordenadaAtual = {0, 0};
        int flag = 0;

        int x, y;
        cin >> x >> y;

        if(x % 2 == 0) {
            // Se o resto da divisão por 2 for igual a 0, então com uma quantidade par de passos ele consegue chegar lá
        } else {
            // Se não for, ele necessariamente precisa gastar o passo único que ele tem
            uso1Passo = 0;
        }

        if(y % 2 == 0) {
            // Se o resto da divisão por 2 for igual a 0, então com uma quantidade par de passos ele consegue chegar lá
        } else {
            // Se não for, ele necessariamente precisa gastar o passo único que ele tem
            if(!uso1Passo) flag = 1; // Precisou usar mais de 1 passo único
            uso1Passo = 0;
        }

        if(flag) cout << "NO" << endl;
        else cout << "YES" << endl;


    }


    return 0;
}