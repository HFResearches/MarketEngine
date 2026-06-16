#pragma once

#include <iostream>
#include <mutex>
#include <cstring>

#define max 1024

struct candle{
  double open, high; 
  double low, close;
};


extern candle period[max]{nullptr};
extern std::mutex mtx;

void getCandles(const std::string symbol);
