#include <iostream>
#include <omp.h>
#include "include.h"

using namespace std;

std::string text = TEXT;
std::string pattern = PATTERN;
std::ifstream file;

int main() {
#ifdef BUILD
    text = "../" + text;
    pattern = "../" + pattern;
#endif
    READ_FILE(text, t);
    READ_FILE(pattern, p);

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
//    ans = bitap_dp(t, p);

//#pragma omp parallel
//    {
//        long long seg_size = T_LEN / omp_get_num_threads();
//        int tid = omp_get_thread_num();
//        long long begin = max(tid * seg_size - P_LEN + 1, 0ll);
//        long long end = (tid + 1) * seg_size - 1;
//        end = min(end, (long long) T_LEN - 1);
//        string str = t.substr(begin, end - begin + 1);
//        vector<int> t_ans = bitap_dp(str, p);
//        for(auto &ind: t_ans)
//            ind += begin;
//#pragma omp critical
//        {
//            cout << begin << " " << end << "\n";
//            for(auto x:t_ans)
//                cout << x << ", ";
//            cout << "\n";
//            ans.insert(ans.end(), t_ans.begin(), t_ans.end());
//        }
//    }

    long long n = T_LEN - P_LEN + 1;
#pragma omp parallel
    {
        long long seg_size = T_LEN / omp_get_num_threads();
        int tid = omp_get_thread_num();
        long long begin = tid * seg_size;
        long long end = (tid+1) * seg_size;
        if (tid == omp_get_num_threads() - 1)
            end = T_LEN;

        vector<int> thread_ans = bitap_dp_parallel(t, p, begin, end);
#pragma omp critical
        {
            cout << "Thread: " << tid << "\n";
            cout << begin << " " << end << "\n";
            for(auto x:thread_ans)
                cout << x << ", ";
            cout << "\n";
            ans.insert(ans.end(), thread_ans.begin(), thread_ans.end());
        }
    }

#endif

    double calcTime = tock(&clTime);
    for (auto &i: ans) cout << i << " ";
    cout << "\n";
    cout << "***-----***\n";
    cout << "Length of text: " << t.length() << "\n";
    cout << "Length of pattern: " << p.length() << "\n";
    cout << "Number of matches found: " << ans.size() << "\n";
    cout << "Time Taken(ms): " << calcTime * 1000 << "\n";
    cout << calcTime * 1000;
    return 0;
}