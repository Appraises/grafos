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
    vector<int> A(n);

    for(int i = 0; i < n; i++) {
        int ai;
        cin >> ai;
        A[i] = ai;
    }

    int m;
    cin >> m;
    vector<int> B(m);

    for(int i = 0; i < m; i++) {
        int bi;
        cin >> bi;
        B[i] = bi;
    }

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    for(int i = 0; i < n; i++) {
        int achou;
        for(int j = 0; j < m; j++) {
            achou = 0;
            int valorFora = A[i] + B[j];

            // Agora que eles tão ordenados, só precisamos fazer uma busca binária em A e em B pra verificar
            // se esse valor fora não tá em nenhum dos dois, se chegar até o final
            // da árvore binária e não estiver, então esse valor é possível
            int low = 0;
            int high = n - 1;

            while(low <= high) {
                int mid = low + (high - low) / 2;

                if(A[mid] == valorFora) {
                    achou = 1;
                    break;
                }
                if(A[mid] < valorFora) low = mid + 1;
                else high = mid - 1;
            }

            low = 0;
            high = m - 1;

            if(!achou) {
                while(low <= high) {
                    int mid = low + (high - low) / 2;
    
                    if(B[mid] == valorFora) {
                        achou = 1;
                        break;
                    }
                    if(B[mid] < valorFora) low = mid + 1;
                    else high = mid - 1;
                }
            }

            if(!achou) {
                cout << A[i] << " " << B[j] << endl;
                break;
            }
        }

        if(!achou) break;
    }



    

    return 0;
}