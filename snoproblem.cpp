#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<pair<int, int>>> g(n + 1);
    ll total = 0;
    for (int i = 0; i < n - 1; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        g[a].push_back({b, d});
        g[b].push_back({a, d});
        total += d;
    }

    vector<int> par(n + 1, -1), order;
    {
        vector<int> st(1, 1);
        par[1] = 0;
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            order.push_back(v);
            for (auto [to, w] : g[v])
                if (to != par[v]) {
                    par[to] = v;
                    st.push_back(to);
                }
        }
    }

    vector<ll> down(n + 1, 0), best(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        int v = order[i];
        ll a1 = 0, a2 = 0;
        for (auto [to, w] : g[v]) {
            if (to == par[v]) continue;
            ll arm = (ll)w + down[to];
            if (arm > a1) { a2 = a1; a1 = arm; }
            else if (arm > a2) a2 = arm;
            best[v] = max(best[v], best[to]);
        }
        down[v] = a1;
        best[v] = max(best[v], a1 + a2);
    }

    vector<ll> up(n + 1, 0), out(n + 1, 0);
    ll twoBest = 0, fourBest = 0;

    for (int v : order) {
        vector<pair<ll, int>> arms;
        if (v != 1) arms.push_back({up[v], -1});
        for (auto [to, w] : g[v])
            if (to != par[v]) arms.push_back({(ll)w + down[to], to});
        sort(arms.rbegin(), arms.rend());

        ll s = 0;
        for (int i = 0; i < 4 && i < (int)arms.size(); i++) s += arms[i].first;
        fourBest = max(fourBest, s);

        ll t1 = 0, t2 = 0, t3 = 0;
        int d1 = -2, d2 = -2, d3 = -2;
        for (auto [val, dir] : arms) {
            if (val >= t1) { t3 = t2; d3 = d2; t2 = t1; d2 = d1; t1 = val; d1 = dir; }
            else if (val >= t2) { t3 = t2; d3 = d2; t2 = val; d2 = dir; }
            else if (val > t3) { t3 = val; d3 = dir; }
        }

        ll b1 = 0, b2 = 0;
        int who = -1;
        for (auto [to, w] : g[v]) {
            if (to == par[v]) continue;
            if (best[to] >= b1) { b2 = b1; b1 = best[to]; who = to; }
            else if (best[to] > b2) b2 = best[to];
        }

        for (auto [to, w] : g[v]) {
            if (to == par[v]) continue;

            ll exclMax = (d1 != to) ? t1 : (d2 != to) ? t2 : t3;

            ll arr[3];
            int k = 0;
            if (d1 != to) arr[k++] = t1;
            if (d2 != to) arr[k++] = t2;
            if (d3 != to) arr[k++] = t3;
            ll sum = (k >= 2) ? arr[0] + arr[1] : (k == 1) ? arr[0] : 0;
            ll local = max(sum, (who != to) ? b1 : b2);

            out[to] = max(out[v], local);
            twoBest = max(twoBest, best[to] + out[to]);
            up[to] = (ll)w + max(0LL, exclMax);
        }
    }

    ll ans = max(best[1], max(twoBest, fourBest));
    cout << 2 * total - ans << '\n';
    return 0;
}
