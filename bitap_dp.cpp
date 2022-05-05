#include <iostream>
#include "include.h"

using namespace std;

vector<int> bitap_dp(string &t, string &p) {
    vector<int> ans;
//    vector<vector<bool>> dp(2, vector<bool>(T_LEN, false));
//    dp[0] = vector<bool>(T_LEN, true);
    vector<bitset<T_LEN>> dp(2, 0);
    dp[0].set();
    int ind = 0;
    for (int i = 0; i < P_LEN; i++, ind ^= 1) {
// 4x faster with parallizing for loop
//#pragma omp simd
// more than 20x faster with simd

//#pragma omp distribute parallel for simd
// same as using only simd?

#pragma omp parallel for
        for (int j = 0; j < T_LEN; j++)
            dp[ind ^ 1][j + 1] = dp[ind][j] & (p[i] == t[j]);
        dp[ind ^ 1][0] = false;
    }

    for (int i = 0; i < T_LEN; i++)
        if (dp[ind][i + 1])
            ans.push_back(i - P_LEN + 1);

    return ans;
}
