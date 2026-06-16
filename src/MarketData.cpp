#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include <openssl/ssl.h>

#include <iostream>
#include <cstddef>
#include <mutex>
#include <cstring>

#include <nlohmann/json.hpp>

#include "MarketData.hpp"

candle period[max];
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
    endereco->h__length);

  connect(pacote, (sockaddr*) &ipv4,
    sizeof(ipv4));

  SSL* ssl = SSL_new(ctx);
  SSL_set_fd(ssl, pacote);
  
  SSL_connect(ssl);
  unsigned char chave[16];
  RAND_bytes(chave, sizeof(chave));

  char chave64[64];
  EVP_EncodeBlock(
    reinterpret_cast<unsigned char*> 
    (chave64);
  
    sizeof(chave16);
  );  

  const char* get = "GET /hubs/tick HTTP/1.1"
    "Host: biquote.io"
    "Upgrade: websocket"
    "Connection: Upgrade"
    "Sec-WebSocket-Version: 13"
    "Sec-WebSocket-Key: " + 
    std::string(chave64) + "\r\n\r\n";

  SSL_write(ssl, get.c_str(), get.size());
  char buffermemoria[4096];
  
  int bytes;
  while((bytes = SSL_read(ssl, buffermemoria,
    sizeof(buffermemoria) - 1)) > 0){
    std::lock_guard <mutex> lockar(mtx);
    for(size_t x : max){
      buffermemoria[bytes] = '\0';
      resposta += buffermemoria;   
      
      json j = json::parse(resposta);
      period[x].open = j["open"].get<double>;
      period[x].high = j["high"].get<double>;
      period[x].low = j["low"].get<double>;
      period[x].close = j["close"].get<double>; 
    }
    
    for(size_t x : max)
      period[x].clear();
  }

  SSL_shutdown(ssl);
  SSL_free(ssl);

  close(pacote);
  SSL_free(ctx);
  
}
