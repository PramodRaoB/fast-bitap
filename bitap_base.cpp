#include <iostream>
#include "include.h"
using namespace std;

vector<int> bitap_base(string &t, string &p) {
    int m = t.length();
    vector<int> ans;
    bitset<P_LEN + 1> R;
    R.set();

    vector<bitset<P_LEN + 1>> pattern_mask(alpha, R);
    R[0] = false;
    //build pattern mask
    for (int i = 0; i < P_LEN; i++)
        pattern_mask[p[i] - 'A'][i] = false;

    for (int i = 0; i < m; i++) {
        R |= pattern_mask[t[i] - 'A'];
        R <<= 1;
        cout << R.to_string() << "\n";
        if (!R[P_LEN]) ans.push_back(i - P_LEN + 1);
    }
    return ans;
}
