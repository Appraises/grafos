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
    int contador = 0;
    map<string, string> conjuntoNomes;

    for(int i = 0; i < q; i++) {
        string nicknameAntigo;
        cin >> nicknameAntigo;
        string nicknameNovo;
        cin >> nicknameNovo;
        int achou = 0;

        // Percorro o map tentando ver se tem alguém
        // cujo o valor é igual ao nick antigo que a gente
        // tá indo trocar
        for(auto [key, value] : conjuntoNomes) {
            if(value == nicknameAntigo) { // Se for igual, então esse nick já é de um usuário que tá no nosso banco
                conjuntoNomes[key] = nicknameNovo; // Defino o valor do usuário original como esse novo nick
                achou = 1; // Defino que descobri que essa troca de nome é de um usuário que já tinhamos
            }
        }

        if(!achou) { // Se não for de um usuário que já tinhamos, defino um novo usuário, e somo o contador
            conjuntoNomes.insert({nicknameAntigo, nicknameNovo});
            contador++;
        }
        

    }

    cout << contador << endl;
    for(auto [key, value] : conjuntoNomes) {
        cout << key << " " << value << endl;
    }

    return 0;
}