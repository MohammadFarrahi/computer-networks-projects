#ifndef ROUTER_HPP
#define ROUTER_HPP


#include "Segment.hpp"

#include <vector>
#include <queue>
#include <iostream>
#include <map>

#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <unistd.h>
#include <thread>
#include <mutex>          

using namespace std;

class Router
{
public:
  Router(int port, int receiver_port, int queue_size);
  void start();

private:
  queue<Segment*> segment_queue;
  int port, receiver_port;
  int queue_size;
  map<int, int> port_map;
  mutex queue_mutex;

  int sockfd;
  struct sockaddr_in send_addr, routeraddr;


  void setup_socket();
  void process_incoming();
  void process_outgoing();

  void update_port_map(int application_port, int os_port);
  void add_to_queue(Segment* segment);
};

#endif