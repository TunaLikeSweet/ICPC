#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to build the suffix array
vector<int> buildSuffixArray(const string& s) {
    int n = s.size();
    vector<int> suffix_array(n), rank(n), temp(n);
    for (int i = 0; i < n; i++) {
        suffix_array[i] = i;
        rank[i] = s[i];
    }

    for (int k = 1; k < n; k *= 2) {
        auto cmp = [&](int i, int j) {
            if (rank[i] != rank[j]) return rank[i] < rank[j];
            int ri = (i + k < n) ? rank[i + k] : -1;
            int rj = (j + k < n) ? rank[j + k] : -1;
            return ri < rj;
            };
        sort(suffix_array.begin(), suffix_array.end(), cmp);

        temp[suffix_array[0]] = 0;
        for (int i = 1; i < n; i++) {
            temp[suffix_array[i]] = temp[suffix_array[i - 1]] + cmp(suffix_array[i - 1], suffix_array[i]);
        }
        rank = temp;
    }
    return suffix_array;
}

// Function to build the LCP array using Kasai's algorithm
vector<int> buildLCPArray(const string& s, const vector<int>& suffix_array) {
    int n = s.size();
    vector<int> lcp(n, 0), rank(n, 0);
    for (int i = 0; i < n; i++) rank[suffix_array[i]] = i;

    int h = 0;
    for (int i = 0; i < n; i++) {
        if (rank[i] > 0) {
            int j = suffix_array[rank[i] - 1];
            while (i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
            lcp[rank[i]] = h;
            if (h > 0) h--;
        }
    }
    return lcp;
}

// Segment tree to support range maximum query
class SegmentTree {
    vector<int> tree;
    int n;

public:
    SegmentTree(const vector<int>& data) {
        n = data.size();
        tree.resize(4 * n);
        build(data, 0, 0, n - 1);
    }

    void build(const vector<int>& data, int node, int start, int end) {
        if (start == end) {
            tree[node] = data[start];
        } else {
            int mid = (start + end) / 2;
            build(data, 2 * node + 1, start, mid);
            build(data, 2 * node + 2, mid + 1, end);
            tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    int query(int L, int R, int node, int start, int end) {
        if (R < start || L > end) return 0;
        if (L <= start && end <= R) return tree[node];
        int mid = (start + end) / 2;
        return max(query(L, R, 2 * node + 1, start, mid), query(L, R, 2 * node + 2, mid + 1, end));
    }

    int query(int L, int R) {
        return query(L, R, 0, 0, n - 1);
    }
};

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, Q;
    cin >> n >> Q;
    string s;
    cin >> s;

    vector<int> suffix_array = buildSuffixArray(s);
    vector<int> lcp = buildLCPArray(s, suffix_array);
    SegmentTree segTree(lcp);

    for (int q = 0; q < Q; q++) {
        int L, R;
        cin >> L >> R;
        L--, R--;

        int D = 0;
        for (int i = L; i < R; i++) {
            D += segTree.query(i + 1, R);
        }
        cout << D << endl;
    }

    return 0;
}