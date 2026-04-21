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
        int a, b, x, y;
        cin >> a >> b >> x >> y;

        int flag = 0;

        int areaCobertaCimaHorizontal = 0;
        int areaCobertaBaixoHorizontal = 0;
        int areaCobertaCimaVertical = 0;
        int areaCobertaBaixoVertical = 0;

        // Começando por cima
        for(int i = 0; i < a; i++) {
            if(i != x) {
                areaCobertaCimaHorizontal += b;
            } else {
                break;
            }
        }

        // cout << areaCobertaCimaHorizontal << endl;

        // Começando por baixo
        for(int i = a - 1; i > 0; i--) {
            if(i != x) {
                areaCobertaBaixoHorizontal += b;
            } else {
                break;
            }
        }

        // cout << areaCobertaBaixoHorizontal << endl;

        for(int j = 0; j < b; j++) {
            if(j != y) {
                areaCobertaCimaVertical += a;
            } else {
                break;
            }
        }

        // cout << areaCobertaCimaVertical << endl;

        for(int j = b - 1; j > 0; j--) {
            if(j != y) {
                areaCobertaBaixoVertical += a;
            } else {
                break;
            }
        }

        // cout << areaCobertaBaixoVertical << endl;

        // cout << areaCobertaCimaHorizontal << areaCobertaBaixoHorizontal << areaCobertaCimaVertical << areaCobertaBaixoVertical << endl;
        cout << max(max(areaCobertaCimaHorizontal, areaCobertaBaixoHorizontal), max(areaCobertaCimaVertical, areaCobertaBaixoVertical)) << endl;

    }

    return 0;
}