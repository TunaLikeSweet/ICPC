#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;
const int dx[] = { -1, 1, 0, 0 }; // Up, Down, Left, Right
const int dy[] = { 0, 0, -1, 1 }; // Up, Down, Left, Right

struct State {
    int x, y, dir, changes;
};

int n;
int m;
vector<vector<bool>> is_obstacle;
vector<vector<vector<int>>> dist;

void bfs(int xs, int ys, vector<vector<vector<int>>>& dist) {
    deque<State> q;
    for (int i = 0; i < 4; i++) {
        q.push_back({ xs, ys, i, 0 });
        dist[xs][ys][i] = 0;
    }
    while (!q.empty()) {
        State u = q.front();
        q.pop_front();
        int x = u.x;
        int y = u.y;
        int dir = u.dir;
        int changes = u.changes;
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && !is_obstacle[nx][ny]) {
            if (dist[nx][ny][dir] > changes) {
                dist[nx][ny][dir] = changes;
                q.push_front({ nx, ny, dir, changes });
            }
        }
        for (int i = 0; i < 4; i++) {
            if (i != dir) {
                int new_changes = changes + 1;
                if (dist[x][y][i] > new_changes) {
                    dist[x][y][i] = new_changes;
                    q.push_back({ x, y, i, new_changes });
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int k, q;
    cin >> n >> m >> k >> q;
    is_obstacle.resize(n + 1, vector<bool>(m + 1, false));
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        is_obstacle[x][y] = true;
    }
    int xs, ys;
    cin >> xs >> ys;
    if (is_obstacle[xs][ys]) {
        while (q--) cout << "-1\n";
        return 0;
    }
    dist.resize(n + 1, vector<vector<int>>(m + 1, vector<int>(4, INF)));
    bfs(xs, ys, dist);
    while (q--) {
        int xt, yt;
        cin >> xt >> yt;
        int ans = INF;
        for (int i = 0; i < 4; i++) {
            ans = min(ans, dist[xt][yt][i]);
        }
        cout << (ans == INF ? "-1" : to_string(ans)) << '\n';
    }
    return 0;
}