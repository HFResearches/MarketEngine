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
    std::cout << "Running main.\n";
  }

  return 0;
}
