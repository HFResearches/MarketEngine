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

void getCandles(const std::string
symbol) noexcept;

class OHLC{
  public:
    double net(size_t x) noexcept;
    double body(size_t x) noexcept;
   
    inline bool doji(size_t x, 
      size_t shift) noexcept;
    inline bool spinning(size_t x, 
      size_t shift) noexcept;
    inline bool marobozu(size_t x,
      size_t shift) noexcept;
    
    double lowerShadow(size_t x);
    double upperShadow(size_t x);
};
