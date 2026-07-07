#include <iostream>
#include <optional>
#include <numeric>
#include "MarketData.hpp"

std::optional <constexpr size_t> idx[];
constexpr size_t idxload(size_t x, 
size_t b) noexcept{
  static size_t beingpulled = 
  x - b;

  for(size_t a{}; a < beingpulled; a++){
    return a;
  }
}

consteval bool hasRisingMovement(){
  
  idx[1] = idxload(1024, 32);
  idx[2] = idxload(1024, 1);

  constexpr float soma = 
  std::accumulate(net(idx[1], net(idx[2]]), 
  0);

  constexpr float average =  soma / 30; 
  constexpr bool condition = average < 0;

  return condition; 
}
