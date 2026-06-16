#pragma once
#define max 1024;

#include <iostream>
#include <mutex>
#include <cstring>
struct candle{
  double open, high; 
  double low, close;
};

extern candle period[max];
extern std::mutex mtx;

void getCandles(const std::string symbol);
