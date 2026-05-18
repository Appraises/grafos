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
    int n;
    cin >> n;
    int contador = 0;
    map<int, string> conversas;


    while(n--) {
        string conversa;
        cin >> conversa;

        int jaExiste = 0;
        string valorPraBaixo;

        for(auto [key, value] : conversas) {
            valorPraBaixo = value;
            if(conversa == value) { // Essa conversa já existe
                for(auto [key, value] : conversas) { // Todo mundo até chegar nessa conversa tem o valor trocado
                    string salvar = value;
                    conversas[key] = valorPraBaixo;
                    valorPraBaixo = salvar;
                    jaExiste = 1;
                    if(conversa == salvar) break;
                }
            } 
        } 

        if(!jaExiste) {
            conversas.insert({++contador, conversa});
            valorPraBaixo = conversa;
            for(auto [key, value] : conversas) { // Todo mundo até chegar nessa conversa tem o valor trocado
                string salvar = value;
                conversas[key] = valorPraBaixo;
                valorPraBaixo = salvar;
            }
        }
    }

    for(auto [key, value] : conversas) {
        cout << value << endl;
    }
    
    return 0;
}