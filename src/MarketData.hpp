#pragma once

#include <iostream>
#include <mutex>
#include <cstring>
struct candle{
  double open, high; 
  double low, close;
}

size_t buffer(size_t a);

extern candle period[x(a)];
extern std::mutex mtx;

void getCandles(const std::string symbol);
