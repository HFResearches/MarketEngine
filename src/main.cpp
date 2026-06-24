#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <random>
#include "MarketData.hpp"
#include "ringbuffer.hpp"

size_t x{'\0'};
size_t as{'\0'};

int main(){
  std::srand(time(0));
  std::string symbol;
  
  std::cin >> symbol;
  std::thread c(getCandles, symbol);
  c.detach(); 

  std::random_device rd;
  std::mt19937 generate(rd())
;
  bool f{};
  while(true){
    std::uniform_int_distribution<size_t> distribution(0, 1024);
    x = distribution(generate);

    {
      std::lock_guard<std::mutex> lock(mtx);

      std::cout << period[x].open
      << ":" << period[x].high << 
      ":" << period[x].low << ":"
      << period[x].close << ":" << std::endl;
    }
  }

  return 0;
}
