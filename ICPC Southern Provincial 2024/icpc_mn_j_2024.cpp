#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

int count_distinct_characters(const string& S) {
    unordered_set<char> distinct_chars(S.begin(), S.end());
    return distinct_chars.size();
}

bool all_frequencies_equal(const unordered_map<char, int>& freq) {
    int count = -1;
    for (const auto& entry : freq) {
        if (count == -1) {
            count = entry.second;
        } else if (entry.second != count) {
            return false;
        }
    }
    return true;
}

int count_beautiful_substrings(const string& S, int distinct_count) {
    int N = S.length();
    int beautiful_count = 0;

    for (int start = 0; start < N; ++start) {
        unordered_map<char, int> freq;

        for (int end = start; end < N; ++end) {
            char current_char = S[end];
            freq[current_char]++;

            if (freq.size() == distinct_count) {
                int first_freq = freq.begin()->second;

                bool is_beautiful = true;
                for (const auto& entry : freq) {
                    if (entry.second != first_freq) {
                        is_beautiful = false;
                        break;
                    }
                }

                if (is_beautiful) {
                    beautiful_count++;
                }
            }

            if (freq.size() > distinct_count) {
                break;
            }
        }
    }

    return beautiful_count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int N;
    string S;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> N;
    cin >> S;
    int distinct_count = count_distinct_characters(S);
    cout << count_beautiful_substrings(S, distinct_count) << endl;

    return 0;
}