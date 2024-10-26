#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

class Matrix {
public:
    long long bitsOne;
    long long bitsZero;
    long long lenght;
    long long matrix[2][2];
    Matrix(bool isIdentity) {
        matrix[0][0] = 1;
        matrix[0][1] = 0;
        matrix[1][0] = 0;
        matrix[1][1] = 1;
    }
    Matrix() {
        matrix[0][0] = 1;
        matrix[0][1] = 1;
        matrix[1][0] = 1;
        matrix[1][1] = 0;
    }
    Matrix multiply(Matrix& a, Matrix& b) { // O(1)
        Matrix result(true);
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                result.matrix[i][j] = 0;
                for (int k = 0; k < 2; k++) {
                    result.matrix[i][j] = (result.matrix[i][j] + a.matrix[i][k] * b.matrix[k][j]) % MOD;
                }
            }
        }
        return result;
    }

    Matrix power(Matrix& base, long long expo, long long MOD) { // O(log n)
        Matrix result(true);
        while (expo > 0) {
            if (expo % 2 == 1) {
                result = multiply(result, base);
            }
            base = multiply(base, base);
            expo /= 2;
        }
        return result;
    }
    long long compute(long long n);
    long long power(long long base, long long exp, long long mod);
};

long long Matrix::power(long long base, long long exp, long long mod) { // O(log n)
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

long long Matrix::compute(long long n) { // O(log n)
    Matrix base;
    Matrix identity(true);
    Matrix result = base.power(base, n, MOD);
    bitsOne = result.matrix[0][1] % MOD;
    lenght = result.matrix[0][0] % MOD;
    bitsZero = (lenght - bitsOne + MOD) % MOD;
    long long beautyScore = 0;
    long long ones = bitsOne;
    long long zeros = bitsZero;
    long long term1 = (ones * (ones - 1) % MOD) * power(2, ones + zeros - 2, MOD) % MOD;
    long long term2 = ones * power(2, ones + zeros - 1, MOD) % MOD;
    long long term3 = (ones * zeros % MOD) * power(2, ones + zeros - 2, MOD) % MOD;
    beautyScore = (term1 + term2 + term3) % MOD;
    return beautyScore;
}

// long long ones = countOne[i];
// long long zeros = (len[i] - countOne[i] + MOD) % MOD;
// long long term1 = (ones * (ones - 1) % MOD) * power(2, ones + zeros - 2, MOD) % MOD;
// long long term2 = ones * power(2, ones + zeros - 1, MOD) % MOD;
// long long term3 = (ones * zeros % MOD) * power(2, ones + zeros - 2, MOD) % MOD;
// beautyScore[i] = (term1 + term2 + term3) % MOD;

// Overal time complexity: O(t * log n)

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    vector<int> query(t);
    Matrix matrix;
    for (int i = 0; i < t; i++) {
        cin >> query[i];
        cout << matrix.compute(query[i]) << endl;
    }
    return 0;
}
