#include <iostream>
#include <vector>
#include <bitset>
#include "include.h"
using namespace std;

vector<int> bitap(string &t, string &p) {
    vector<int> ans;
    vector<vector<bool>> dp(P_LEN + 1, vector<bool>(T_LEN, false));
    dp[0] = vector<bool>(T_LEN, true);
    for(int i = 0; i < P_LEN; i++) {
//#pragma omp parallel for
// 4x faster with parallizing for loop
#pragma omp simd
// more than 20x faster with simd

//#pragma omp distribute parallel for simd
// same as using only simd?

        for(int j = 0; j < T_LEN; j++)
            dp[i+1][j+1] = dp[i][j] & (p[i] == t[j]);
    }

    for(int i = 0; i < T_LEN; i++)
        if(dp[P_LEN][i+1])
            ans.push_back(i - P_LEN + 1);

    return ans;
}

int main() {
    if (!freopen("./text.txt", "r", stdin)) {
        cerr << "text.txt doesn't exist\n";
        return 1;
    }
    string t, p;
    cin >> t;
    if (!freopen("./pattern.txt", "r", stdin)) {
        cerr << "pattern.txt doesn't exist\n";
        return 1;
    }
    cin >> p;
    timeval clTime{};
    tick(&clTime);
    vector<int> ans = bitap(t, p);
    double calcTime = tock(&clTime);
    for (auto &i: ans) cout << i << " ";
    cout << "\n";
    cout << "***-----***\n";
    cout << "Length of text: " << t.length() << "\n";
    cout << "Length of pattern: " << p.length() << "\n";
    cout << "Number of matches found: " << ans.size() << "\n";
    cout << "Time Taken(ms): " << calcTime * 1000 << "\n";
    return 0;
}