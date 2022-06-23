#ifndef RECEIVER_HPP
#define RECEIVER_HPP

#include "Segment.hpp"
#include "ClientReceiver.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <unistd.h>
#include <map>

using namespace std;

class Receiver
{
public:
  Receiver(int port, int router_port);
  void start();

private:
  int port;
  int router_port;
	int sockfd;
  struct sockaddr_in servaddr, router_addr;
  map<int, ClientReceiver*> clients;



  void setup_socket();
};

#endif