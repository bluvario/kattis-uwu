#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int A, B;
    while (cin >> A >> B && (A || B)) {
        int a[5] = {}, b[5] = {}, c[10] = {};
        int la = 0, lb = 0, lc = 0;
        for (int x = A; x; x /= 10) a[++la] = x % 10;
        for (int i = 1, j = la; i < j; i++, j--) swap(a[i], a[j]);
        for (int x = B; x; x /= 10) b[++lb] = x % 10;
        for (long long x = 1LL * A * B; x; x /= 10) c[++lc] = x % 10;
        int flag = lc;

        cout << "+";
        for (int i = 0; i < 4 * la + 3; i++) cout << "-";
        cout << "+\n";

        cout << "| ";
        for (int i = 1; i <= la; i++) cout << "  " << a[i] << " ";
        cout << "  |\n";

        for (int i = lb; i >= 1; i--) {
            cout << "| +";
            for (int e = 1; e <= la; e++) cout << "---+";
            cout << " |\n";

            cout << "|" << (flag - la > i ? '/' : ' ');
            for (int e = 1; e <= la; e++) cout << "|" << a[e] * b[i] / 10 << " /";
            cout << "| |\n";

            cout << "| ";
            for (int e = 1; e <= la; e++) cout << "| / ";
            cout << "|" << b[i] << "|\n";

            cout << "|";
            if (lc - la >= i) cout << c[lc--];
            else cout << " ";
            for (int e = 1; e <= la; e++) cout << "|/ " << a[e] * b[i] % 10;
            cout << "| |\n";
        }

        cout << "| +";
        for (int e = 1; e <= la; e++) cout << "---+";
        cout << " |\n";

        cout << "|" << (flag > la ? '/' : ' ');
        while (lc) {
            cout << " " << c[lc--] << " ";
            if (lc) cout << "/";
        }
        cout << "   |\n";

        cout << "+";
        for (int i = 0; i < 4 * la + 3; i++) cout << "-";
        cout << "+\n";
    }
    return 0;
}
