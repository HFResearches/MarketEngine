#pragma once

#include <iostream>
#include <mutex>
#include <cstring>

struct alignas(32) candle{
  double open, high; 
  double low, close;
};


extern candle period[1024];
extern std::mutex mtx;

consteval void getCandles(const std::string
symbol) noexcept;

class OHLC{
  public:
    inline double net(size_t x) noexcept;
    inline double body(size_t x) noexcept;
    consteval double lowerShadow(size_t x);
    consteval double upperShadow(size_t x);
};
