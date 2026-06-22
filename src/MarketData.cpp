#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#include <openssl/rand.h>
#include <openssl/ssl.h>

#include <iostream>
#include <cstddef>
#include <mutex>
#include <cstring>

#include "MarketData.hpp"

extern constexpr size_t max = 1024;

/*now down bellow period is only initialized 
at get Candle*/

candle period[1024]{};
std::mutex mtx;

extern size_t a{0};

void getCandles(const std::string symbol){
  while(true){
    SSL_library_init();
    SSL_CTX* ctx = 
      SSL_CTX_new(TLS_client_method());

    std::string resposta{};
    int pacote = 
      socket(AF_INET, SOCK_STREAM, 0);

    hostent* endereco = 
      gethostbyname("biquote.io");
  
    sockaddr_in ipv4{};
    ipv4.sin_family = AF_INET;
    ipv4.sin_port = htons(443);

    memcpy(&ipv4.sin_addr, endereco->h_addr,
    endereco->h_length);

    connect(pacote, (sockaddr*) &ipv4,
      sizeof(ipv4));

    SSL* ssl = SSL_new(ctx);
    SSL_set_fd(ssl, pacote);
  
    SSL_connect(ssl);
  
    std::string get = "GET /api/" + symbol +
    "/ohlc?interval=1m&limit=1"+
    " HTTP/1.1\r\nHost: biquote.io\r\nConnection: close\r\n\r\n";  
    SSL_write(ssl, get.c_str(), get.size());
    char buffermemoria[4096];
  
    int bytes;
    while((bytes = SSL_read(ssl, buffermemoria,
      sizeof(buffermemoria) - 1)) > 0){
      std::lock_guard <std::mutex> lock(mtx);
      buffermemoria[bytes] = '\0';
      resposta += buffermemoria;
    }
 
    size_t endHeader = resposta.find("\r\n\r\n");

    if(endHeader != std::string::npos){
      std::string body = 
      resposta.substr(endHeader + 4);
    
      auto open = body.find("\"open\":");
      auto high = body.find("\"high\":");
      auto low =  body.find("\"low\":");
      auto close = body.find("\"close\":");
    
      size_t startOpen = open +
      strlen("\"open\":");
   
      size_t endOpen = body.find_first_of(
      ",}", startOpen);

      size_t startHigh = high +
      strlen("\"open\":");

      size_t endHigh = body.find_first_of(
      ",}", startHigh);
     
      size_t startLow = low + 
      strlen("\"low\":");

      size_t endLow = body.find_first_of(
      ",}", startLow);

      size_t startClose = close + 
      strlen("\"close\":");
 
      size_t endClose = body.find_first_of(
      ",}", startClose);
            
      if(open && high && low && close 
      != std::string::npos){
        std::lock_guard<std::mutex> lock(mtx);
  
        period[a].open = 
        std::stod(body.substr(startOpen, 
        endOpen - startOpen));
        
        period[a].high = 
        std::stod(body.substr(startHigh, 
        endHigh - startHigh));

        period[a].low =
        std::stod(body.substr(startLow,
        endLow - startLow));

        period[a].close =
        std::stod(body.substr(startClose, 
        endClose - startClose));
    
       std::cout << period[a].open << ":" <<
       ":" << period[a].high << ":" <<
       period[a].low << ":" << period[a].close
       << std::endl;
   
      a = (a + 1) % max;
    }
    
    
    SSL_shutdown(ssl);
    SSL_free(ssl);

    ::close(pacote);
    SSL_CTX_free(ctx);
   
    }
  }
}
