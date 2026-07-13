#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <random>
#include "MarketData.hpp"

int main(){
  std::srand(time(0));
  std::string symbol;
  
  std::cin >> symbol;
  std::thread c(getCandles, symbol);
  OHLC* i = new OHLC[3];
  while(true){
    std::cout << "engolfo:" << 
    (i[1].net(1) < 0 && i[2].body(2)
    < i[3].body(3)) << std::endl;
  }

  return 0;
}
