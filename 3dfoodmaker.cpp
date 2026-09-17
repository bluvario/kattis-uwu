#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<string> tok;
    string t;
    while (cin >> t) tok.push_back(t);

    vector<int> L, R;
    vector<string> OP, NAME;
    vector<char> isLeaf;
    auto addNode = [&]() {
        L.push_back(-1); R.push_back(-1);
        OP.push_back(""); NAME.push_back(""); isLeaf.push_back(0);
        return (int)isLeaf.size() - 1;
    };

    vector<int> nodes;
    vector<string> ops;
    for (string& s : tok) {
        if (s == "(") continue;
        if (s == ")") {
            string o = ops.back(); ops.pop_back();
            int r = nodes.back(); nodes.pop_back();
            int l = nodes.back(); nodes.pop_back();
            int id = addNode();
            L[id] = l; R[id] = r; OP[id] = o;
            nodes.push_back(id);
        } else if (isupper((unsigned char)s[0])) {
            ops.push_back(s);
        } else {
            int id = addNode();
            isLeaf[id] = 1; NAME[id] = s;
            nodes.push_back(id);
        }
    }
    int root = nodes.back();

    vector<int> stk{root}, order;
    while (!stk.empty()) {
        int v = stk.back(); stk.pop_back();
        order.push_back(v);
        if (!isLeaf[v]) { stk.push_back(L[v]); stk.push_back(R[v]); }
    }
    reverse(order.begin(), order.end());

    int bowls = 0;
    for (int v : order) {
        if (isLeaf[v]) continue;
        string b = "bowl_" + to_string(++bowls);
        NAME[v] = b;
        cout << "LOAD\t" << NAME[L[v]] << "\n";
        cout << OP[v] << "\t" << NAME[R[v]] << "\n";
        cout << "STORE\t" << b << "\n";
    }
    cout << "BAKE\t" << NAME[root] << "\n";
    return 0;
}
