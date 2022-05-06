#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"

#include "include.h"

using namespace std;

vector<int> bitap_base(string &t, string &p) {
    vector<int> ans;
    bitset<P_LEN + 1> R;
    R.set();

    vector<bitset<P_LEN + 1>> pattern_mask(alpha, R);
    R[0] = false;
    //build pattern mask
//#pragma omp parallel for
// TODO: Parallise this by heving diff threads mask diff parts of the string
    for (int i = 0; i < P_LEN; i++)
        pattern_mask[p[i] - 'A'][i] = false;

    for (int i = 0; i < T_LEN; i++) {
        R |= pattern_mask[t[i] - 'A'];
        R <<= 1;
        if (!R[P_LEN]) ans.push_back(i - P_LEN + 1);
    }
    return ans;
}

#pragma clang diagnostic pop