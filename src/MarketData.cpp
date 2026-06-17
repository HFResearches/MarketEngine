#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include <openssl/rand.h>
#include <openssl/ssl.h>

#include <iostream>
#include <cstddef>
#include <mutex>
#include <cstring>

#include <nlohmann/json.hpp>

#include "MarketData.hpp"

constexpr size_t max = 1024;

/*now down bellow period is only initialized 
at get Candle*/

candle period[1024]{};
std::mutex mtx;

using json = nlohmann::json;

void getCandles(const std::string symbol){
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
  " HTTP/1.1\r\nHost: biquote.io\r\nConnection: close\r\n\r\n";  
  SSL_write(ssl, get.c_str(), get.size());
  char buffermemoria[4096];
  
  int bytes;
  while((bytes = SSL_read(ssl, buffermemoria,
    sizeof(buffermemoria) - 1)) > 0){
    std::lock_guard <std::mutex> lockar(mtx);

    size_t a{1024};     
    for(size_t x{0}; x < a; x++){
      buffermemoria[bytes] = '\0';
      resposta += buffermemoria;   
      
      json j = json::parse(resposta);
      period[x].open = j["open"].get<double>();
      period[x].high = j["high"].get<double>();
      period[x].low = j["low"].get<double>();
      period[x].close = j["close"].get<double>();

      std::cout << period[x].open << "|"<< period[x].high 
      << "|" << period[x].low << "|" << period[x].close <<
      std::endl; 
    }
    
    for(size_t x{0}; x < a; x++)
      period[x] = {};
  }

  SSL_shutdown(ssl);
  SSL_free(ssl);

  close(pacote);
  SSL_CTX_free(ctx);
  
}
