#pragma once

#include <iostream>
#include <mutex>
#include <cstring>

#define size_t max = 1024;

struct candle{
  double open, high; 
  double low, close;
};

extern candle period[max];
extern std::mutex mtx;

void getCandles(const std::string symbol);
