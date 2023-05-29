#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"

#include "include.h"
#include <iostream>

using namespace std;

vector<int> bitap_base(string &t, string &p) {
  vector<int> ans;
  bitset<P_LEN + 1> R;
  R.set();

  vector<bitset<P_LEN + 1>> pattern_mask(alpha, R);
//   build pattern mask
//   #pragma omp parallel for
//     for (int it = 0; it < 4; it++) {
//       vector<bitset<P_LEN + 1>> t_pattern_mask(alpha, R);
//
//       int begin = it * (P_LEN / 4);
//       int end = min((it + 1) * (P_LEN / 4), P_LEN);
//       if (it == 3)
//         end = P_LEN;
//       for (int i = begin; i < end; i++)
//         t_pattern_mask[p[i] - 'A'][i] = false;
//
//   #pragma omp critical
//       {
//         for (int i = 0; i < alpha; i++) {
//           pattern_mask[i] &= t_pattern_mask[i];
//         }
//       };
//     };

  for (int i = 0; i < P_LEN; i++)
    pattern_mask[p[i] - 'A'][i] = false;

  R[0] = false;

  for (int i = 0; i < T_LEN; i++) {
    R |= pattern_mask[t[i] - 'A'];
    R <<= 1;
    if (!R[P_LEN])
      ans.push_back(i - P_LEN + 1);
  }
  return ans;
}

vector<int> bitap_base_parallel(string &t, string &p) {
    vector<int> ans;
    bitset<P_LEN + 1> R;
    R.set();

    vector<bitset<P_LEN + 1>> pattern_mask(alpha, R);
//   build pattern mask
#pragma omp parallel for
    for (int it = 0; it < 4; it++) {
        vector<bitset<P_LEN + 1>> t_pattern_mask(alpha, R);

        int begin = it * (P_LEN / 4);
        int end = min((it + 1) * (P_LEN / 4), P_LEN);
        if (it == 3)
            end = P_LEN;
        for (int i = begin; i < end; i++)
            t_pattern_mask[p[i] - 'A'][i] = false;

#pragma omp critical
        {
            for (int i = 0; i < alpha; i++) {
                pattern_mask[i] &= t_pattern_mask[i];
            }
        };
    };

    int n = T_LEN - P_LEN + 1;
#pragma omp parallel for schedule(static, 1)
    for (int chunk_start = 0; chunk_start < n; chunk_start += CHUNK_SIZE) {
        int end = min(chunk_start + CHUNK_SIZE, n);
        int begin = max(chunk_start - P_LEN + 1, 0);
        vector<int> thread_ans;
        bitset<P_LEN + 1> S;
        S.set();

        S[0] = false;
        for (int i = begin; i < end; i++) {
            S |= pattern_mask[t[i] - 'A'];
            S <<= 1;
            if (!S[P_LEN])
                thread_ans.push_back(i - P_LEN + 1);
        }

        if (!thread_ans.empty()) {
#pragma omp critical
            {
                ans.insert(ans.end(), thread_ans.begin(), thread_ans.end());
            }
        }
    }
    return ans;
}

#pragma clang diagnostic pop
