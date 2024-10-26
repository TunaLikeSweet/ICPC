#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> 
using namespace std;

long long minCostToReorder(int n, const vector<int>& weights, const vector<int>& initial, const vector<int>& target) {
    vector<int> position(n + 1); 
    vector<bool> visited(n + 1, false); 
    for (int i = 0; i < n; i++) {
        position[target[i]] = i;
    }
    int globalMinWeight = *min_element(weights.begin(), weights.end());

    long long totalCost = 0;

    for (int i = 0; i < n; i++) {
        if (visited[i]) continue; 
        int cycleMinWeight = 10000; 
        long long cycleCost = 0; 
        int cycleLength = 0; 

        int current = i;
        vector<int> cycleElements;
        while (!visited[current]) {
            visited[current] = true;
            int marble = initial[current];
            cycleElements.push_back(marble);
            cycleCost += weights[marble - 1]; 
            cycleMinWeight = min(cycleMinWeight, weights[marble - 1]); 
            cycleLength++;
            current = position[marble];
        }
        long long strategy1Cost = cycleCost + (cycleLength - 2) * cycleMinWeight;
        long long strategy2Cost = cycleCost + cycleMinWeight + (cycleLength + 1) * globalMinWeight;
        totalCost += min(strategy1Cost, strategy2Cost);
    }

    return totalCost;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    int n;
    cin >> n;

    vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }

    vector<int> initial(n), target(n);
    for (int i = 0; i < n; i++) {
        cin >> initial[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> target[i];
    }
    long long result = minCostToReorder(n, weights, initial, target);
    cout << result << endl;

    return 0;
}