#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<unsigned char> dp(n + 1, 255);
    dp[1] = 1;
    for (int k = 2; k <= n; k++) {
        int best = dp[k - 1] + 1;
        for (int l = 1; 2 * l <= k; l++)
            best = min(best, (int)dp[k - l] + dp[l]);
        for (int l = 2; l * l <= k; l++)
            if (k % l == 0) best = min(best, (int)dp[k / l] + dp[l]);
        string s = to_string(k);
        for (size_t i = 0; i + 1 < s.size(); i++) {
            if (s[i + 1] == '0') continue;
            best = min(best, (int)dp[stoi(s.substr(0, i + 1))] +
                                  dp[stoi(s.substr(i + 1))]);
        }
        dp[k] = (unsigned char)best;
    }
    cout << (int)dp[n] << "\n";
    return 0;
}
