#pragma once

#include <iostream>
#include <mutex>
#include <cstring>

struct candle{
  double open, high; 
  double low, close;
};


extern candle period[1024];
extern std::mutex mtx;

void getCandles(const std::string symbol);

class OHLC{
  public:
    inline double net(size_t x);
    inline double body(size_t x);
    inline double lowerShadow(size_t x);
    inline double upperShadow(size_t x);
};
