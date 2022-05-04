#include <iostream>
#include "include.h"
using namespace std;

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
    vector<int> ans;

#ifdef BASE
    cout << "Base :)\n";
    ans = bitap_base(t, p);
#endif
#ifdef FLIP
    cout << "Flip :)\n";
    ans = bitap_flipped(t, p);
#endif
#ifdef DP
    cout << "DP :)\n";
    ans = bitap_dp(t, p);
#endif

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