#include <bits/stdc++.h>
using namespace std;

static const int P[] = {100,75,60,50,45,40,36,32,29,26,24,22,20,18,16,
                        15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    int k = n - 1;
    vector<vector<int>> s(m, vector<int>(k));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) cin >> s[i][j];
        sort(s[i].begin(), s[i].end());
    }
    auto sumTop = [&](int i, int t) {
        int r = 0;
        for (int j = 0; j < t; j++) r += s[i][k - 1 - j];
        return r;
    };
    int me = sumTop(0, min(k, 4));
    vector<int> need;
    for (int i = 1; i < m; i++) {
        if (sumTop(i, min(k, 4)) > me) need.push_back(0);
        else need.push_back(1 + me - sumTop(i, min(k, 3)));
    }
    sort(need.begin(), need.end());
    auto ok = [&](int t) {
        long long tot = 0;
        int g = 0;
        for (int i = 0; i < t; i++) {
            int r = t - i;
            tot += (r <= 30 ? P[r - 1] : 0) + 1;
            g++;
            if ((tot + g - 1) / g >= need[i]) tot = g = 0;
        }
        return g == 0;
    };
    int lo = 0, hi = (int)need.size();
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (ok(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << 1 + lo << '\n';
    return 0;
}
