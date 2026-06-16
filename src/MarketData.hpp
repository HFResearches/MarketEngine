#pragma once

#include <iostream>
#include <mutex>
#include <cstring>

struct candle{
  double open, high; 
  double low, close;
};


extern candle period[];
extern std::mutex mtx;

void getCandles(const std::string symbol);
