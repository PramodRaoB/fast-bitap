#include <iostream>
#include "include.h"
using namespace std;

vector<int> bitap_flipped(string &t, string &p) {
    vector<int> ans;
    bitset<T_LEN + 1> R;
    R.reset();

    vector<bitset<T_LEN + 1>> pattern_mask(alpha, R);
    R.set();
    //build pattern mask
    for (int i = 0; i < T_LEN; i++)
        pattern_mask[t[i] - 'A'][i] = true;
    for(int i = 0; i < alpha; i++)
        cout << pattern_mask[i].to_string() << "\n";
    cout << "\n";

    for (int i = 0; i <  P_LEN; i++) {
        R &= pattern_mask[p[i] - 'A'];
        R <<= 1;
        cout << R.to_string() << "\n";
    }

    for (int i = 0; i < T_LEN; i++)
        if (R[i + 1]) ans.push_back(i - P_LEN + 1);
    return ans;
}
