#ifndef FAST_BITAP_INCLUDE_H
#define FAST_BITAP_INCLUDE_H

#include <vector>
#include <bitset>

const int alpha = 4;
//#define P_LEN 108
//#define T_LEN 345600
#define T_LEN 20
#define P_LEN 3

void tick(struct timeval *t);
double tock(struct timeval *t);

std::vector<int> bitap_base(std::string &t, std::string &p);
std::vector<int> bitap_flipped(std::string &t, std::string &p);
std::vector<int> bitap_dp(std::string &t, std::string &p);

#endif //FAST_BITAP_INCLUDE_H
