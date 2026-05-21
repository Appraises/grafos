#include <bits/stdc++.h> // 1. Includes sempre no topo
using namespace std;
 
// 2. Macros e Definições logo abaixo dos includes
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define dbg(x) (cout << #x << " = " << x << endl);
typedef long long ll;
 
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

int main()
{
    int t;
    cin >> t;
    while(t--) {
      int n;
      cin >> n;
      vector<pair<int, int>> pontosEspeciais(n);
      vector<bool> visitados(n);

      int u, d, r, l;
      u = 0;
      d = 0;
      r = 0;
      l = 0;

      int x = 0;
      int y = 0;

      for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;

        if(x < 0) l = 1;
        if(x > 0) u = 1;
        if(y > 0) r = 1;
        if(y < 0) d = 1;
      }



      if(l && u && r && d) {
        cout << "NO" << endl;
      } else {
        cout << "YES" << endl;
      }

    }
}