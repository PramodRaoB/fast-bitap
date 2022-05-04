#ifndef FAST_BITAP_INCLUDE_H
#define FAST_BITAP_INCLUDE_H

#include <bitset>
#include <vector>

const int alpha = 4;
//#define P_LEN 108
//#define T_LEN 345600
#define T_LEN 20
#define P_LEN 3

#define READ_FILE(f, str)                                                      \
  string str;                                                                  \
  if (!freopen(f.c_str(), "r", stdin)) {                                               \
    cerr << (f) << " doesn't exist\n";                                         \
    return 1;                                                                  \
  }                                                                            \
  cin >> (str);

void tick(struct timeval *t);
double tock(struct timeval *t);

std::vector<int> bitap_base(std::string &t, std::string &p);
std::vector<int> bitap_flipped(std::string &t, std::string &p);
std::vector<int> bitap_dp(std::string &t, std::string &p);

#endif // FAST_BITAP_INCLUDE_H
