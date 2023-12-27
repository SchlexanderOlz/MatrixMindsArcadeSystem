#ifndef UTILS
#define UTILS

#include <iostream>
#include <random>

using namespace std;

namespace utils {
  template<typename T>
  T getRandomNumber(T min, T max) {
    static random_device rd;
    static mt19937 gen(rd());

    uniform_int_distribution<T> distribution(min, max);

    return distribution(gen);
  }
} 

#endif
