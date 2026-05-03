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

    vector<pair<vector<int>, vector<int>>> tamanhos(31);

    for(int i = 0; i < n; i++) {
        int tamanho;
        cin >> tamanho;

        char orientacao;
        cin >> orientacao;

        // tamanhos vão do 30 ao 60, então tudo que eu preciso é diminuir do mínimo pra ter um
        // array com 30 posições (meus 30 conjuntos de tamanhos)
        // que vão ter 2 arrays cada, indicando os pés direito e esquerdo
        vector<int> &esquerda = tamanhos[tamanho - 30].first;
        vector<int> &direita = tamanhos[tamanho - 30].second;

        if(orientacao == 'E') {
            esquerda.push_back(1);
        } else {
            direita.push_back(1);
        }
    }

    int qtdPares = 0;
    for(auto &par : tamanhos) { // Para cada conjunto de tamanhos, eu verifico quantos
        auto &esquerda = par.first; // pares dá pra formar, pegando o minimo
        auto &direita = par.second; // entre o pé esquerdo e o pé direito

        int qtdParesFormar = min(esquerda.size(), direita.size());
        qtdPares += qtdParesFormar;
    }

    cout << qtdPares << endl;

    return 0;
}