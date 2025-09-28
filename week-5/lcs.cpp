#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class LCS {
public:
    void longestCommonSubstring(const string& X, const string& Y) {
        int m = X.size();
        int n = Y.size();

        // DP table
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        int maxLength = 0;
        int endIndex = 0;

        // Fill DP table
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (X[i - 1] == Y[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    if (dp[i][j] > maxLength) {
                        maxLength = dp[i][j];
                        endIndex = i - 1;
                    }
                } else {
                    dp[i][j] = 0;
                }
            }
        }

        // Print DP table
        cout << "Dynamic Programming Table:" << endl;
        cout << "    ";
        for (char c : Y) cout << setw(3) << c;
        cout << endl;

        for (int i = 0; i <= m; i++) {
            if (i == 0) cout << "  ";
            else cout << X[i - 1] << " ";
            for (int j = 0; j <= n; j++) {
                cout << setw(3) << dp[i][j];
            }
            cout << endl;
        }

        // Extract longest substring
        string result = X.substr(endIndex - maxLength + 1, maxLength);

        cout << "\nLongest Common Substring: " << result << endl;
        cout << "Length: " << maxLength << endl;
    }
};

int main() {
    string s1, s2;
    cout << "Enter first string: ";
    cin >> s1;
    cout << "Enter second string: ";
    cin >> s2;

    LCS solver;
    solver.longestCommonSubstring(s1, s2);

    return 0;
}
