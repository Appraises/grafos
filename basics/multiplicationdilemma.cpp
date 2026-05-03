#include <bits/stdc++.h> // 1. Includes sempre no topo
using namespace std;

// 2. Macros e Definições logo abaixo dos includes
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define dbg(x) (cout << #x << " = " << x << endl);
typedef long long ll;

const int INF = 0x3f3f3f3f;

int main() {
    _ // Ativa o I/O rápido


    int t;
    cin >> t;

    while(t--) {
        int a, b;
        cin >> a >> b;

        vector<int> numerosEspeciaisEmA;
        vector<int> numerosEspeciaisEmB;

        int potencia = 0;
        int aNegativo = 0;
        int bNegativo = 0;
        
        if(a < 0) {
            aNegativo = 1;
            a = -a;
        }

        if(b < 0) {
            bNegativo = 1;
            b = -b;
        }


        while(a > 0) {
            int ni = a % 10;
            a /= 10;

            if(ni != 0) {
                numerosEspeciaisEmA.push_back(ni * pow(10, potencia));
                // dbg(ni);
                // dbg(potencia);
            }
            potencia++;
        }

        potencia = 0;
        while(b > 0) {
            int ni = b % 10;
            b /= 10;

            if(ni != 0) {
                numerosEspeciaisEmB.push_back(ni * pow(10, potencia));
                // dbg(ni);
                // dbg(potencia);
            }
            potencia++;
        }

        reverse(numerosEspeciaisEmA.begin(), numerosEspeciaisEmA.end());
        reverse(numerosEspeciaisEmB.begin(), numerosEspeciaisEmB.end());

        bool first = true;
        for(auto i : numerosEspeciaisEmA) {
            for(auto j : numerosEspeciaisEmB) {
                if(!first) cout << " + ";
                cout << (aNegativo ? -i : i) << " x " << (bNegativo ? -j : j);
                first = false;
            }
        }

        cout << endl;

    }

    return 0;
}