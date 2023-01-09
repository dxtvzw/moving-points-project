#include <bits/stdc++.h>

using namespace std;

mt19937 rnd(123);

class SCCGraph {
    /*
     * this class is to check if a graph is strongly connected
     * 1-based indexing
     */
    const int n;
    vector<vector<int>> g, gr;
    vector<bool> used;
    vector<int> post;
    vector<vector<int>> comps;

    void dfs_inv(int v) {
        used[v] = true;
        for (int to : gr[v]) {
            if (!used[to]) {
                dfs_inv(to);
            }
        }
        post.push_back(v);
    }

    void dfs(int v, vector<int>& comp) {
        used[v] = true;
        comp.push_back(v);
        for (int to : g[v]) {
            if (!used[to]) {
                dfs(to, comp);
            }
        }
    }

public:
    SCCGraph(int n) : n(n), g(n + 1), gr(n + 1), used(n + 1) {}

    SCCGraph(const vector<vector<int>>& g_) : n(g_.size() - 1), g(g_), gr(g_.size()), used(g_.size()) {
        for (int v = 1; v <= n; v++) {
            for (int to : g[v]) {
                gr[to].push_back(v);
            }
        }
    }

    void add_edge(int u, int v) {
        g[u].push_back(v);
        gr[v].push_back(u);
    }

    int Kosaraju() {
        post.clear();
        comps.clear();
        for (int i = 1; i <= n; i++) {
            used[i] = false;
        }
        for (int i = 1; i <= n; i++) {
            if (!used[i]) {
                dfs_inv(i);
            }
        }
        reverse(post.begin(), post.end());
        for (int i = 1; i <= n; i++) {
            used[i] = false;
        }
        for (int v : post) {
            if (!used[v]) {
                vector<int> comp;
                dfs(v, comp);
                comps.push_back(comp);
            }
        }
        reverse(comps.begin(), comps.end());
        // edges go from left to right
        return comps.size();
    }

    vector<vector<int>> get_comps() const {
        return comps;
    }

    bool is_one_scc() {
        return Kosaraju() == 1;
    }
};

vector<vector<int>> generate_graph(int n, bool allow_multiedge = false) {
    vector<vector<int>> g(n + 1);
    SCCGraph scc(n);
    set<pair<int, int>> edges;
    while (!scc.is_one_scc()) {
        int u = rnd() % n + 1;
        int v = rnd() % n + 1;
        if (u == v) {
            continue;
        }
        if (!allow_multiedge && edges.count({u, v})) {
            continue;
        }
        edges.emplace(u, v);
        g[u].push_back(v);
        scc.add_edge(u, v);
    }
    return g;
}

void foo() {
    int n = 5;
    auto g = generate_graph(n);
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    foo();

#ifdef LOCAL
    cout << "\nTime elapsed: " << double(clock()) / CLOCKS_PER_SEC << " s.\n";
#endif
}