#include <iostream>
#include <omp.h>
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

vector<int> bitap_dp_parallel(string &t, string &p) {
    vector<int> ans;
    long long n = T_LEN - P_LEN + 1;
#pragma omp parallel
    {
        long long seg_size = n / omp_get_num_threads();
        int tid = omp_get_thread_num();
        long long begin = tid * seg_size;
        long long end = (tid + 1) * seg_size;
        if (tid == omp_get_num_threads() - 1)
            end = n;

        vector<int> thread_ans;
        bitset<(T_LEN - P_LEN + 1) / 8 + 7> dp;
        dp.set();
        for (int i = 0; i < P_LEN; i++) {
            for (int j = begin; j < end; j++)
                dp[j - begin] = dp[j - begin] & (p[i] == t[j + i]);
        }
        for (int i = begin; i < end; i++)
            if (dp[i - begin])
                thread_ans.push_back(i);

        if(thread_ans.size() > 0) {
#pragma omp critical
            {
                ans.insert(ans.end(), thread_ans.begin(), thread_ans.end());
            }
        }
    }
    return ans;
}