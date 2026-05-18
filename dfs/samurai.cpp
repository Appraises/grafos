#include <bits/stdc++.h> // 1. Includes sempre no topo
using namespace std;

// 2. Macros e Definições logo abaixo dos includes
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define dbg(x) (cout << #x << " = " << x << endl);
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

void dfs(int inicio, vector<vector<int>> &grafo, vector<int> &cor, vector<int> &graus, int* maiorGrau, int *indiceMaiorGrau) {
    cor[inicio] = 1;

    if(graus[inicio] > *maiorGrau) {
        *maiorGrau = graus[inicio];
        *indiceMaiorGrau = inicio;
    }

    for(auto v : grafo[inicio]) {
        if(cor[v] == 0) {
            if(graus[v] > *maiorGrau) {
                *maiorGrau = graus[v];
                *indiceMaiorGrau = v;
            }
            dfs(v, grafo, cor, graus, maiorGrau, indiceMaiorGrau);
        }
    }

    cor[inicio] = 2;
}

void dfsIntroducao(int inicio, vector<vector<int>> &grafo, vector<int> &cor, vector<int> &graus, vector<int> &componenteAcoplar) {
    cor[inicio] = 1;

    for(auto v : grafo[inicio]) {
        if(cor[v] == 0) {
            for(auto w : componenteAcoplar) {
                grafo[v].push_back(w);
                grafo[w].push_back(v);
            }
            dfsIntroducao(v, grafo, cor, graus, componenteAcoplar);
        }
    }

    cor[inicio] = 2;
}


// 3. APENAS UMA função main
int main() {
    _ // Ativa o I/O rápido
    int n, m;
    cin >> n >> m;

    if(n < 2) {
        cout << "NO" << endl;
        return 0;
    }

    vector<vector<int>> grafo(n);
    vector<int> graus(n, 0);
    vector<int> cor(n, 0);
    vector<pair<int, int>> introducoes;

    int limite = (n * (n - 1))/4;

    for(int i = 0; i < m; i++) {
        int v, w;
        cin >> v >> w;

        v--;
        w--;

        grafo[v].push_back(w);
        grafo[w].push_back(v);
        graus[v]++;
        graus[w]++;
    }

    set<int> s1;
    set<int> s2;

    int maior = INT_MIN;
    int verticeMaior = -1;

    int maior2 = INT_MIN;
    int verticeMaior2 = -1;
    int maiorGrauCC = -1;
    int indiceMaiorGrau = -1;

    vector<pair<int, int>> indiceEGrauCC;
    
    for(int i = 0; i < n; i++) {
        if(cor[i] == 0) {
            dfs(i, grafo, cor, graus, &maiorGrauCC, &indiceMaiorGrau);
            indiceEGrauCC.push_back({maiorGrauCC, indiceMaiorGrau});
            indiceMaiorGrau = -1;
            maiorGrauCC = -1;
        }
    }

    
    for(int i = 0; i < indiceEGrauCC.size(); i++) {
        if (indiceEGrauCC[i].first > maior) {
            maior = indiceEGrauCC[i].first;
            verticeMaior = indiceEGrauCC[i].second;
        }
    }

    indiceEGrauCC[verticeMaior].first = 0;

    for(int i = 0; i < indiceEGrauCC.size(); i++) {
        if (indiceEGrauCC[i].first > maior2) {
            maior2 = indiceEGrauCC[i].first;
            verticeMaior2 = indiceEGrauCC[i].second;
        }
    }

    indiceEGrauCC[verticeMaior].first = maior;


    dbg(maior);
    dbg(verticeMaior);
    dbg(maior2);
    dbg(verticeMaior2);


    graus[verticeMaior] = maior;

    for(int i = 0; i < maior; i++) {
        for(int j = i; j < maior; j++) {
            if(i == j) continue;
            if(find(grafo[grafo[verticeMaior][i]].begin(), grafo[grafo[verticeMaior][i]].end(), grafo[verticeMaior][j]) == grafo[grafo[verticeMaior][i]].end()) {
                grafo[grafo[verticeMaior][i]].push_back(grafo[verticeMaior][j]);
                grafo[grafo[verticeMaior][j]].push_back(grafo[verticeMaior][i]);
                introducoes.push_back({grafo[verticeMaior][i], grafo[verticeMaior][j]});
            }
        }
    }

    for(int i = 0; i < maior2; i++) {
        for(int j = i; j < maior2; j++) {
            if(i == j) continue;
            if(find(grafo[grafo[verticeMaior2][i]].begin(), grafo[grafo[verticeMaior2][i]].end(), grafo[verticeMaior2][j]) == grafo[grafo[verticeMaior2][i]].end()) {
                grafo[grafo[verticeMaior2][i]].push_back(grafo[verticeMaior2][j]);
                grafo[grafo[verticeMaior2][j]].push_back(grafo[verticeMaior2][i]);
                introducoes.push_back({grafo[verticeMaior2][i], grafo[verticeMaior2][j]});
            }
        }
    }

    if(introducoes.size() <= limite) {
        cout << "YES" << endl;
        cout << introducoes.size() << endl;
        for(int i = 0; i < introducoes.size(); i++) {
            cout << introducoes[i].first + 1 << " " << introducoes[i].second + 1 << endl;
        }
    } else {
        cout << "NO" << endl;
    }


    // ok, agora eu tenho os dois com o maior grau, tenho que estruturar o campeonato emcima deles porque são eles que vão garantir pra mim o mínimo de ligações possíveis, já que no pior caso eu vou ter que fazer uma quant

    return 0;
}