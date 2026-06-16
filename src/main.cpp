#include <iostream>
#include <mutex>
#include <thread>

#include "MarketData.hpp"

std::mutex mtx;
int main(){
  std::thread c(getCandles, "DXY");
  c.detach();
 
  while(true){
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << period[sizeof(period)].close <<
    ":close\n";
  }

  return 0;
}
