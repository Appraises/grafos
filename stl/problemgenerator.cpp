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
        map<char, int> contagemTipoProblema;
        contagemTipoProblema.insert({'A', 0});
        contagemTipoProblema.insert({'B', 0});
        contagemTipoProblema.insert({'C', 0});
        contagemTipoProblema.insert({'D', 0});
        contagemTipoProblema.insert({'E', 0});
        contagemTipoProblema.insert({'F', 0});
        contagemTipoProblema.insert({'G', 0});

        int n, m;
        cin >> n >> m;
        string problemas;
        cin >> problemas;

        for(int i = 0; i < n; i++) {
            contagemTipoProblema[problemas[i]]++;
        }

        int contagemProblemasFaltantes = 0;
        for(auto [x, y] : contagemTipoProblema) {
            if(y < m) contagemProblemasFaltantes += m - y;
        }

        cout << contagemProblemasFaltantes << endl;

    }




    return 0;
}