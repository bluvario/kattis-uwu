#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, T;
    scanf("%d %d", &N, &T);

    int M = N + 1;
    vector<int> delta(M), cost(M);
    delta[0] = 1; cost[0] = 1;
    int minDelta = 0;
    for (int i = 1; i <= N; i++) {
        scanf("%d %d", &delta[i], &cost[i]);
        minDelta = min(minDelta, delta[i]);
    }

    int maxNode = T - minDelta;
    const int INF = 1e9;
    vector<int> dist(maxNode + 1, INF), par(maxNode + 1, -1);
    vector<vector<int>> bucket(T + 1);
    dist[0] = 0;
    bucket[0].push_back(0);

    for (int d = 0; d <= T; d++) {
        while (!bucket[d].empty()) {
            int u = bucket[d].back(); bucket[d].pop_back();
            if (dist[u] != d) continue;
            if (u == T) {
                vector<int> path;
                for (int cur = T; cur != 0; ) {
                    int e = par[cur];
                    path.push_back(e + 1);
                    cur -= delta[e];
                }
                printf("%d\n", (int)path.size());
                for (int i = 0; i < (int)path.size(); i++)
                    printf("%d%c", path[i], i + 1 == (int)path.size() ? '\n' : ' ');
                return 0;
            }
            for (int i = 0; i < M; i++) {
                int v = u + delta[i];
                if (v < 1 || v > maxNode) continue;
                int nd = d + cost[i];
                if (nd >= dist[v] || nd > T) continue;
                dist[v] = nd;
                par[v] = i;
                bucket[nd].push_back(v);
            }
        }
    }
    return 0;
}
