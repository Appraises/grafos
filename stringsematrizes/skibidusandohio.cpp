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
        string umaString;
        cin >> umaString;

        int i = 0;
        int flag = 0;

        while((i <= umaString.size()) && !flag) {
            flag = 1;
            for(i = 0; i < umaString.size(); i++) {
                if(umaString[i] == umaString[i + 1]) {
                    umaString.erase(i + 1, 1);
                    if(umaString.size() > 1 && (i - 1) >= 0) umaString[i] = umaString[i - 1];
                    else if (umaString.size() > 1 && (i + 1) < umaString.size()) umaString[i] = umaString[i + 1];

                    flag = 0;
                    break;
                }
            }
        }

        // cout << umaString << endl;
        cout << umaString.size() << endl;
    }

    // ivrnpozeoyvgratakycpkkboxzmkxouwwbpvscnwxgnlkwsxeflxpbaxsnypqjzooasfcqnzyzxnypnqtbdqnutxavype

    return 0;
}