#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

int main() {
    _

    int L, Y;
    cin >> L >> Y;

    int p = 0;

    vector<bool> questoes(3, false);

    // Lucca
    if(L & 4) {
        p += 4;
        questoes[0] = true;
    }

    if(L & 2) {
        p += 2;
        questoes[1] = true;
    }

    if(L & 1) {
        p += 1;
        questoes[2] = true;
    }

    // Yvens
    if((Y & 4) && !questoes[0]) {
        p += 4;
        questoes[0] = true;
    }

    if((Y & 2) && !questoes[1]) {
        p += 2;
        questoes[1] = true;
    }

    if((Y & 1) && !questoes[2]) {
        p += 1;
        questoes[2] = true;
    }

    cout << p << endl;

    return 0;
}