#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP

#include <iostream>

size_t RingBuffer(size_t initsize, size_t endsize){
  if(initsize < endsize) {
    for(size_t x{initsize}; x < endsize; x++){
      return x;
    }
          
    return {'\0'};
          
  } else if(initsize > endsize) {
    for(size_t x{initsize}; x > endsize; x--){ 
       return x; 
    }
            
    return initsize;
  }  
}

#endif //RINGBUFFER_HPP
