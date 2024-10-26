#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 101;

int fenwick[MAXN][MAXN][MAXN];
int n;

void update(int x, int y, int z, int val) {
    for (int i = x; i <= n; i += i & -i) {
        for (int j = y; j <= n; j += j & -j) {
            for (int k = z; k <= n; k += k & -k) {
                fenwick[i][j][k] += val;
            }
        }
    }
}

int query(int x, int y, int z) {
    int sum = 0;
    for (int i = x; i > 0; i -= i & -i) {
        for (int j = y; j > 0; j -= j & -j) {
            for (int k = z; k > 0; k -= k & -k) {
                sum += fenwick[i][j][k];
            }
        }
    }
    return sum;
}

int query(int x1, int y1, int z1, int x2, int y2, int z2) {
    return query(x2, y2, z2)
        - query(x1 - 1, y2, z2)
        - query(x2, y1 - 1, z2)
        - query(x2, y2, z1 - 1)
        + query(x1 - 1, y1 - 1, z2)
        + query(x1 - 1, y2, z1 - 1)
        + query(x2, y1 - 1, z1 - 1)
        - query(x1 - 1, y1 - 1, z1 - 1);
}

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int m;
        cin >> n >> m;
        memset(fenwick, 0, sizeof(fenwick));
        while (m--) {
            string op;
            cin >> op;
            if (op == "UPDATE") {
                int x, y, z, W;
                cin >> x >> y >> z >> W;
                int current_val = query(x, y, z, x, y, z);
                update(x, y, z, W - current_val);
            } else if (op == "QUERY") {
                int x1, y1, z1, x2, y2, z2;
                cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
                cout << query(x1, y1, z1, x2, y2, z2) << '\n';
            }
        }
    }
    return 0;
}