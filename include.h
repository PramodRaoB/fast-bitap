#ifndef FAST_BITAP_INCLUDE_H
#define FAST_BITAP_INCLUDE_H

#include <bitset>
#include <fstream>
#include <vector>

const int alpha = 4;
#define P_LEN 542
#define T_LEN 309043

#define READ_FILE(f, str)                                                      \
  string str;                                                                  \
  file.open((f).c_str());                                                      \
  file >> (str);                                                               \
  file.close();

void tick(struct timeval *t);
double tock(struct timeval *t);

std::vector<int> bitap_base(std::string &t, std::string &p);
std::vector<int> bitap_flipped(std::string &t, std::string &p);
std::vector<int> bitap_dp(std::string &t, std::string &p);

#endif // FAST_BITAP_INCLUDE_H
