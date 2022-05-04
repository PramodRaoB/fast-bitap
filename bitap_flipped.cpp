#include <iostream>
#include <vector>
#include <bitset>
#include "include.h"
using namespace std;

vector<int> bitap(string &t, string &p) {
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

int main() {
    if (!freopen("../text.txt", "r", stdin)) {
        cerr << "text.txt doesn't exist\n";
        return 1;
    }
    string t, p;
    cin >> t;
    if (!freopen("../pattern.txt", "r", stdin)) {
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