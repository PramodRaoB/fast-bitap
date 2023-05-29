#ifndef FAST_BITAP_INCLUDE_H
#define FAST_BITAP_INCLUDE_H

#include <bitset>
#include <fstream>
#include <vector>

#ifdef SMALL
#define INP 0
#define P_LEN 100
#define T_LEN 10035
#endif
#ifdef MED
#define P_LEN 490
#define T_LEN 3147090
#define INP 1
#endif
#ifdef LARGE
// #define P_LEN 1750
#define P_LEN 3365
// #define T_LEN 23011544
#define T_LEN 5154862

#define INP 2
#endif

const int alpha = 4;
// Below chunk size for DP
//#define CHUNK_SIZE 256
// Below chunk size for flip
//#define CHUNK_SIZE (32768 - P_LEN)
// Below chunk size for base
#define CHUNK_SIZE (262144)
//#define P_LEN 542
//#define T_LEN 309043

const long long text_len[] = {10035, 3147090, 23011544};
const long long pattern_len[] = {100, 490, 1750};

const std::string text_file[] = {"sequences/small_t.txt", "sequences/med_t.txt",
                                 "sequences/temp_t.txt"};
const std::string pattern_file[] = {
    "sequences/small_p.txt", "sequences/med_p.txt", "sequences/temp.txt"};

const std::string TEXT = text_file[INP];
const std::string PATTERN = pattern_file[INP];

#define READ_FILE(f, str)                                                      \
  string __attribute__((aligned(16))) (str);                                   \
  file.open((f).c_str());                                                      \
  while (!file.eof()) {                                                        \
    string line;                                                               \
    file >> line;                                                              \
    (str).append(line);                                                        \
  }                                                                            \
  file.close();

void tick(struct timeval *t);

double tock(struct timeval *t);

std::vector<int> bitap_base(std::string &t, std::string &p);

std::vector<int> bitap_base_parallel(std::string &t, std::string &p);

std::vector<int> bitap_flipped(std::string &t, std::string &p);

std::vector<int> bitap_flipped_vectorized(std::string &t, std::string &p);

std::vector<int> bitap_flipped_parallel(std::string &t, std::string &p);

std::vector<int> bitap_dp(std::string &t, std::string &p);

std::vector<int> bitap_dp_parallel(std::string &t, std::string &p);

std::vector<int> bitap_dp_scheduling(std::string &t, std::string &p);

#endif // FAST_BITAP_INCLUDE_H
