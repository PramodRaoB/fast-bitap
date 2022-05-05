#include <iostream>
#include "include.h"
using namespace std;

std::string TEXT = "text.txt";
std::string PATTERN = "pattern.txt";

int main() {
#ifdef BUILD
    TEXT = "../" + TEXT;
    PATTERN = "../" + PATTERN;
#endif
    READ_FILE(TEXT, t);
    READ_FILE(PATTERN, p);

    timeval clTime{};
    vector<int> ans;
    tick(&clTime);

#ifdef BASE
    ans = bitap_base(t, p);
#endif
#ifdef FLIP
    ans = bitap_flipped(t, p);
#endif
#ifdef DP
    ans = bitap_dp(t, p);
#endif

    double calcTime = tock(&clTime);
//    for (auto &i: ans) cout << i << " ";
//    cout << "\n";
//    cout << "***-----***\n";
//    cout << "Length of text: " << t.length() << "\n";
//    cout << "Length of pattern: " << p.length() << "\n";
//    cout << "Number of matches found: " << ans.size() << "\n";
//    cout << "Time Taken(ms): " << calcTime * 1000 << "\n";
    cout << calcTime * 1000;
    return 0;
}