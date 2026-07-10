#include <iostream>
#include "MarketData.hpp"
#include <optional>
#include <mutex>

OHLC i;
std::optional <constexpr size_t> idx{0uz};
std::mutex mtx;

bool goes[]{};

explicit bool TopuntillLowTrend()noexcept{
  {
    std::lock_guard<std::mutex> mtx(lock)
    goes[1] = (period[1].high - 
    period[16].close) <= (period[1].high * 
    0.10);
  }

  return goes[1];
}
