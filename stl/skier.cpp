#include <bits/stdc++.h>
using namespace std;

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
    _ 

    int q;
    cin >> q;
    
    while(q--) {
        // Um par onde o primeiro elemento é um par (x, y) e o segundo é outro par (x, y)

        int segundos = 0;
        string direcoes;
        cin >> direcoes;

        set<pair<pair<int, int>, pair<int, int>>> conjuntoDeSegmentos;

        int x = 0; int y = 0;

        for(char c : direcoes) {
            int antigoX = x;
            int antigoY = y;

            if(c == 'N') y++;
            else if (c == 'S') y--;
            else if (c == 'E') x++;
            else x--;

            pair<int, int> p1 = {antigoX, antigoY};
            pair<int, int> p2 = {x, y};

            // dbg(c);

            pair<pair<int, int>, pair<int, int>> segmento = {min(p1, p2), max(p1, p2)};

            if(!conjuntoDeSegmentos.count(segmento)) {
                conjuntoDeSegmentos.insert(segmento);
                segundos += 5;
            } else {
                segundos++;
            }


            // dbg(segundos);
        }

        cout << segundos << endl;
    }



    return 0;
}
