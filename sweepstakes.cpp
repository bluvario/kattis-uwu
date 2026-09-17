#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-12;

int m, n, t, q;
vector<double> pv, qv;
vector<set<int>> v;
vector<vector<int>> qcells;

struct Poly {
    int l = 0, r = 0, cap;
    vector<double> f;
    Poly(int c) : cap(c), f(c + 1, 0.0) { f[0] = 1.0; }
    void mul(double p) {
        if (p == 0.0) return;
        double q = 1.0 - p;
        if (r < cap) r++;
        for (int i = r; i >= l; i--) {
            f[i] = f[i] * q;
            if (i != l) f[i] += f[i - 1] * p;
        }
        while (l < r && f[l] < EPS) l++;
        while (l < r && f[r] < EPS) r--;
    }
    double get(int x) const {
        if (x < l || x > r) return 0.0;
        return f[x];
    }
};

double rat(int id) {
    int i = id / n + 1, j = id % n + 1;
    return pv[i] + qv[j];
}

Poly *cur;

void build(int p, int L, int R) {
    if (L == R) {
        for (int c : qcells[L]) v[p].insert(c);
        return;
    }
    int M = (L + R) >> 1;
    build(p << 1, L, M);
    build(p << 1 | 1, M + 1, R);
    for (int c : v[p << 1]) v[p].insert(c);
    for (int c : v[p << 1 | 1]) v[p].insert(c);
}

void solve(int p, int L, int R) {
    if (L == R) {
        Poly res(t + 1);
        for (int c : v[p]) res.mul(rat(c));
        int s = (int)v[p].size();
        double pos = 0.0;
        for (int k = 0; k <= s && k <= t; k++) pos += res.get(k) * cur->get(t - k);
        for (int k = 0; k <= s; k++) {
            double val = (k <= t) ? res.get(k) * cur->get(t - k) / pos : 0.0;
            printf("%.10f ", val);
        }
        putchar('\n');
        return;
    }
    int M = (L + R) >> 1;
    Poly saved = *cur;
    for (int c : v[p])
        if (!v[p << 1].count(c)) cur->mul(rat(c));
    solve(p << 1, L, M);
    *cur = saved;
    for (int c : v[p])
        if (!v[p << 1 | 1].count(c)) cur->mul(rat(c));
    solve(p << 1 | 1, M + 1, R);
    *cur = saved;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> m >> n >> t >> q)) return 0;

    pv.assign(m + 1, 0.0);
    for (int i = 1; i <= m; i++) cin >> pv[i];
    qv.assign(n + 1, 0.0);
    for (int j = 1; j <= n; j++) cin >> qv[j];

    qcells.assign(q + 1, {});
    for (int i = 1; i <= q; i++) {
        int s, x, y;
        cin >> s;
        while (s--) {
            cin >> x >> y;
            qcells[i].push_back((x - 1) * n + (y - 1));
        }
    }

    if (q == 0) return 0;

    v.assign(4 * q + 4, {});
    build(1, 1, q);

    cur = new Poly(t + 1);
    for (int id = 0; id < m * n; id++)
        if (!v[1].count(id)) cur->mul(rat(id));

    solve(1, 1, q);
    delete cur;
    return 0;
}
