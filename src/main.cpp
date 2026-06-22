#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

#include "MarketData.hpp"
#include <iterator>

size_t x{'\0'};
size_t as{'\0'};
int main(){
  std::string symbol;
  
  std::cin >> symbol;
  std::thread c(getCandles, symbol);
  c.detach(); 
  bool f{};
  while(true){
    {
      {       
        std::lock_guard<std::mutex> lock(mtx);

        as = std::size(period);
        for(size_t x{'\0'}; x < as; x++){
          size_t ptrIDX = x;
                 
          std::cout << period[ptrIDX].open
          << ":" << period[ptrIDX].high << 
          ":" << period[ptrIDX].low << ":"
          << period[ptrIDX].close << ":" << std::endl;
        }
      }
    }
  }

  return 0;
}
