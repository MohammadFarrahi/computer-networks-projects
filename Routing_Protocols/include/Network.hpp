#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "Node.hpp"

class Network
{
  using Statement = std::vector<std::string>;

public:


  void create_topology(Statement topology);
  void show_network();
  void modify(Statement modification_statement);
  void remove(Statement removal_statement);
  void dvrp_algo(Statement node);
  void lsrp_algo(Statement node);

private:
  std::unordered_map<int, Node*> nodes;

  void create_single_connection(std::string statement);
  Node* find_or_create_node(int index);
  Node* get_node(int index);

  void print_header();
  void print_one_node(Node* node);
  void print_dvrp_for_one(int index);
  void print_dvrp_for_all();

  void init_dvrp_tables();
  int run_dvrp_algo();

  int run_lsrp_flodding();
  void init_lsdbs();
  void print_lsrp_for_one(int index);
  void print_lsrp_for_all();

  void reset_state();
};