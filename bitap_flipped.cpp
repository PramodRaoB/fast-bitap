#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"

#include <iostream>
#include <immintrin.h>
#include "include.h"

using namespace std;

vector<int> bitap_flipped(string &t, string &p) {
    vector<int> ans;
    bitset<T_LEN + 1> R;
    R.reset();

    vector<bitset<T_LEN + 1>> pattern_mask(alpha, R);
    R.set();
    //build pattern mask
//#pragma omp parallel for
    for (int i = 0; i < T_LEN; i++)
        pattern_mask[t[i] - 'A'][i] = true;

    for (int i = 0; i < P_LEN; i++) {
        R &= pattern_mask[p[i] - 'A'];
        R <<= 1;
    }

    for (int i = 0; i < T_LEN; i++)
        if (R[i + 1]) ans.push_back(i - P_LEN + 1);
    return ans;
}

vector<int> bitap_flipped_vectorized(string &t, string &p) {
    vector<int> ans;
    int *pattern_mask[alpha];
    //TODO: Make pattern mask
    //Make pattern mask a multiple of chunk_size
    int n = T_LEN - P_LEN + 1;
    const int lane_size = 128;
    const int num_iter = lane_size - CHUNK_SIZE + 1;
#pragma omp parallel for schedule(dynamic, 1)
    for (int chunk_start = 0; chunk_start < n; chunk_start += CHUNK_SIZE) {
        int end = min(chunk_start + CHUNK_SIZE, n);
        int begin = chunk_start;
        vector<int> thread_ans;
        /*
        for (int i = 0; i < P_LEN; i += num_iter) {
            unshift R num_iter number of times
            load A, B, C, D
            A <- [begin + i, begin + i + 256 - 1]
            for (int j = 0; j < num_iter; j++) {
                R[begin : end - 1] &= pattern_mask[p[i] - 'A'][begin + i : begin + i + CHUNK_SIZE - 1];
                R >>= 1;
            }
        }
         */
        __m256i R = _mm256_set1_epi64x(0ll);
        for (int i = 0; i < P_LEN; i += num_iter) {
//            _mm256_bslli_epi128(R, )
        }
    }
    return ans;
}

vector<int> bitap_flipped_parallel(string &t, string &p) {
    vector<int> ans;
    int n = T_LEN - P_LEN + 1;
#pragma omp parallel for schedule(dynamic, 1)
    for (int chunk_start = 0; chunk_start < n; chunk_start += CHUNK_SIZE) {
        int end = min(chunk_start + CHUNK_SIZE, n);
        int begin = max(chunk_start - P_LEN + 1, 0);
        vector<int> thread_ans;
        bitset<CHUNK_SIZE + P_LEN> R;
        R.set();
        vector<bitset<CHUNK_SIZE + P_LEN>> pattern_mask(alpha, bitset<CHUNK_SIZE + P_LEN>(0));
        for (int i = begin; i < end; i++)
            pattern_mask[t[i] - 'A'][i - begin] = true;

        for (int i = 0; i < P_LEN; i++) {
            R &= pattern_mask[p[i] - 'A'];
            R <<= 1;
        }

        for (int i = begin; i < end; i++)
            if (R[i - begin + 1]) thread_ans.push_back(i - P_LEN + 1);

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