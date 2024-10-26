#include <bits/stdc++.h>
using namespace std;

int minColoringAction(vector<string>& matrix, int n, int m) {
    vector<vector<int>> colored(n, vector<int>(m, 0));
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == '#') {
                if (colored[i][j]) continue;
                for (int k = j; k < m && matrix[i][k] == '#'; k++) {
                    colored[i][k] = 1;
                }
                for (int k = i; k < n && matrix[k][j] == '#'; k++) {
                    colored[k][j] = 1;
                }
                count++;
            }
        }
    }
    return count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    cin >> n >> m;
    vector<string> matrix(n);
    for (int i = 0; i < n; i++) {
        cin >> matrix[i];
    }
    cout << minColoringAction(matrix, n, m) << endl;
    return 0;
}