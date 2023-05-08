#pragma once

#include <utility>
#include <vector>
#include <string>
#include <unordered_map>

typedef struct
{
  int destination; /* address of destination */
  int nextHop;     /* address of next hop */
  int cost;
  std::vector<int> path;
} Route;

class Node
{
  using RouteTable = std::unordered_map<int, Route>;
  using LSA = std::unordered_map<int, int>;
  using LinkStateDB = std::unordered_map<int, LSA>;
  using LsrpTable = std::unordered_map<int, Route>;

public:
  Node(int index);
  void add_neighbor(Node *node, int cost);
  std::string list_neighbors();
  int get_cost_to_node(int index);
  void remove_neighbor(Node *node);

  void reset();

  void create_dvrp_table();
  bool exchange_dvrp_table();
  void print_dvrp_table();

  void init_lsdb();
  bool exchange_lsdb();
  void print_lsdb();
  void run_lsrp_algo();
  void print_lsrp_table();

private:
  int index;
  std::vector<std::pair<Node *, int>> neighbors;

  RouteTable dvrp_table;
  void add_route(int index, int cost);
  void add_route(int next_hop, int destination, int cost, std::vector<int> path);
  void replace_route(int next_hop, int destination, int cost, std::vector<int> path);
  bool compare_dvrp_table(RouteTable other_table, int source_index, int cost_from_source);
  bool is_dest_in_dvrp_table(int index);
  std::string print_path(std::vector<int> path);
  std::vector<int> append_to_path(std::vector<int> path);

  LinkStateDB lsdb;
  LsrpTable lsrp_table;
  bool add_and_broadcast_lsa(int index, int recieve_index, LSA lsa);
  void broadcast_lsa(int index, int recieve_index, LSA lsa);
  std::vector<int> get_all_nodes();
  std::unordered_map<int, int> get_init_cost_nodes(std::vector<int> N);
  std::unordered_map<int, std::vector<int>> get_init_path_map(std::vector<int> N);
  int get_min_node(std::vector<int> N, std::vector<int> M, std::unordered_map<int, int> C);
  void update_cost(std::vector<int> N,
                   std::vector<int> M,
                   std::unordered_map<int, int> &C,
                   std::unordered_map<int, std::vector<int>> &path_map);
  void print_cost_map(int itter, std::unordered_map<int, int> C);
  int get_cost_from_lsdb(int source, int dest);
  std::vector<int> prepend_to_path(std::vector<int> path, int index);
  void make_lsrp_table(std::unordered_map<int, int> C, std::unordered_map<int, std::vector<int>> path_map);
  Route get_lsrp_route(int dest, int cost, std::vector<int> path);
};