#include <bits/stdc++.h> // 1. Includes sempre no topo
using namespace std;

// 2. Macros e Definições logo abaixo dos includes
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define f first  
#define s second
#define dbg(x) (cout << #x << " = " << x << endl);
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

// 3. APENAS UMA função main
int main() {
    _ // Ativa o I/O rápido

    int nPalavras;
    cin >> nPalavras;
    vector<pair<string, char>> mapaDePalavras;
    string s;

    for(int i = 0; i < nPalavras; i++) {
        cin >> s;
        mapaDePalavras.push_back({s, 'O'});
        for(int j = 0; j < s.length() - 1; j++) {
            if(tolower(s[j]) >= tolower(s[j+1])) {
                mapaDePalavras[i] = {s, 'N'};
            }
        }   
    }

    for(auto i : mapaDePalavras) {
        cout << i.f << ": " << i.s << endl;
    }

    return 0;
}