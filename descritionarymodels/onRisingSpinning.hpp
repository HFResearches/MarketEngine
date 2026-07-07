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

consteval bool onRisingSpinning() noexcept{
  
  idx[1] = idxload(1024, 32);
  idx[2] = idxload(1024, 1);

  constexpr double somaLiquida = 
  std::accumulate(net(idx[1], net(idx[2]]), 
  0);

  constexpr double somacorpo =
  std::accumulate(body(idx[1], body[idx[2]),
  0);

  constexpr float mediaLiquida =  somaLiquida /
  30;
  
  constexpr double mediacorpo = somacorpo / 30;

  return mediaLiquida > 0 &&
  (body(idx[2]) * 4 <= mediacorpo); 
}
