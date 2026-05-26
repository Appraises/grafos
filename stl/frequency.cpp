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
    set<int> chamada;
    int n;
    cin >> n;

    for(int i = 0; i < n; i++){
      int nR;
      cin >> nR;
      chamada.insert(nR);
    }
    
    cout << chamada.size() << endl;
    return 0;
}