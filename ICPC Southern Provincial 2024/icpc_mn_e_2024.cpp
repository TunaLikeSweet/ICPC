#include <iostream>
#include <vector>

using namespace std;

vector<int> parent; 
vector<vector<int>> children; 
vector<int> in_time, out_time;
int timer = 0;

void dfs(int node) {
    in_time[node] = ++timer;
    for (int child : children[node]) {
        dfs(child);
    }
    out_time[node] = ++timer; 
}

bool is_ancestor(int u, int v) {
    if (u == v) return true; 
    return in_time[u] < in_time[v] && out_time[u] > out_time[v];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    int n;
    cin >> n;

    parent.resize(n + 1, -1);
    children.resize(n + 1); 
    in_time.resize(n + 1);
    out_time.resize(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        parent[b] = a;
        children[a].push_back(b);
    }

    int root = -1;
    for (int i = 1; i <= n; i++) {
        if (parent[i] == -1) {
            root = i;
            break;
        }
    }
    dfs(root);
    int T;
    cin >> T;
    vector<bool> flag(T, false);
    for (int i = 0; i < T; i++) {
        int x, y;
        cin >> x >> y;
        flag[i] = is_ancestor(x, y);
    }
    for (int i = 0; i < T; i++) {
        cout << (flag[i] ? "Yes" : "No") << '\n';
    }
    return 0;
}