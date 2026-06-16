#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

#include "MarketData.hpp"

using namespace std::chrono_literals;
int main(){
  std::thread c(getCandles, "DXY");
  c.detach();
 
  while(true){
    std::lock_guard<std::mutex> lock(mtx);

    size_t length = sizeof(period); 
    if(length <= 0){
      std::this_thread::sleep_for(20ms);
    
      std::cerr << "candle buffer empty\n";
    }

    std::cout << period[sizeof(period)].close <<
    ":close\n";
  }

  return 0;
}
