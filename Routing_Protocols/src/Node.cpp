#include "Node.hpp"

#include <sstream>
#include <iostream>
#include <limits>
#include <algorithm>

const int INFINITY = 1000000000;

using namespace std;

Node::Node(int index)
{
  this->index = index;
}

void Node::add_neighbor(Node *node, int cost)
{
  for (int i = 0; i < neighbors.size(); i++)
  {
    if (neighbors[i].first->index == node->index)
    {
      neighbors[i].second = cost;
      return;
    }
  }
  neighbors.push_back(pair<Node *, int>(node, cost));
}

void Node::remove_neighbor(Node *node)
{
  for (auto i = neighbors.begin(); i != neighbors.end(); i++)
  {
    if ((*i).first->index == node->index)
    {
      neighbors.erase(i);
      return;
    }
  }
}

void Node::create_dvrp_table()
{
  add_route(this->index, 0);
  for (auto neighbor : neighbors)
  {
    add_route(neighbor.first->index, neighbor.second);
  }
}

void Node::add_route(int index, int cost)
{
  Route route;
  route.cost = cost;
  route.destination = index;
  route.nextHop = index;
  route.path.push_back(this->index);
  route.path.push_back(index);
  dvrp_table.insert(pair<int, Route>(index, route));
}

void Node::add_route(int next_hop, int destination, int cost, vector<int> path)
{
  Route route;
  route.cost = cost;
  route.destination = destination;
  route.nextHop = next_hop;
  route.path = path;
  dvrp_table.insert(pair<int, Route>(destination, route));
}

void Node::replace_route(int next_hop, int destination, int cost, vector<int> path)
{
  dvrp_table[destination].cost = cost;
  dvrp_table[destination].nextHop = next_hop;
  dvrp_table[destination].path = path;
}

string Node::list_neighbors()
{
  stringstream ss;
  for (auto neighbor : neighbors)
  {
    ss << neighbor.first->index << "(" << neighbor.second << ")";
    ss << ", ";
  }
  return ss.str();
}

int Node::get_cost_to_node(int index)
{
  if (index == this->index)
    return 0;

  for (auto neighbor : neighbors)
    if (neighbor.first->index == index)
      return neighbor.second;

  return -1;
}

bool Node::exchange_dvrp_table()
{
  bool changed = false;
  for (auto neighbor : neighbors)
  {
    changed = neighbor.first->compare_dvrp_table(this->dvrp_table,
                                                 this->index,
                                                 neighbor.second) ||
              changed;
  }
  return changed;
}

bool Node::compare_dvrp_table(RouteTable other_table, int source_index, int cost_from_source)
{
  bool changed = false;
  for (auto r : other_table)
  {
    if (is_dest_in_dvrp_table(r.second.destination))
    {
      if (dvrp_table[r.second.destination].cost <= r.second.cost + cost_from_source)
        continue;
      changed = true;
      replace_route(source_index, r.second.destination, r.second.cost + cost_from_source, append_to_path(r.second.path));
    }
    else
    {
      changed = true;
      add_route(source_index, r.second.destination, cost_from_source + r.second.cost, append_to_path(r.second.path));
    }
  }
  return changed;
}

bool Node::is_dest_in_dvrp_table(int index)
{
  return dvrp_table.find(index) != dvrp_table.end();
}

void Node::print_dvrp_table()
{
  cout << "\n\nPrinting dvrp table for node: " << this->index << endl;
  cout << "DEST\t"
       << "Next Hop\t"
       << "Dist\t"
       << "Shortest Path\t" << endl;
  cout << "---------------------------------------" << endl;
  for (auto r : dvrp_table)
  {
    cout << r.second.destination << "\t";
    cout << r.second.nextHop << "\t\t";
    cout << r.second.cost << "\t";
    cout << print_path(r.second.path) << "\t";
    cout << endl;
  }
}

vector<int> Node::append_to_path(vector<int> path)
{
  vector<int> new_path;
  new_path.push_back(this->index);
  for (auto index : path)
  {
    new_path.push_back(index);
  }
  return new_path;
}

string Node::print_path(vector<int> path)
{
  if (path.size() == 0)
    return "";
  stringstream ss;
  ss << "[" << path[0];
  for (int i = 1; i < path.size(); i++)
  {
    if (path[i] == this->index)
      continue;
    ss << " -> " << path[i];
  }
  ss << "]";
  return ss.str();
}

// lsrp

void Node::init_lsdb()
{
  LSA self_lsa;
  for (auto neighbor : neighbors)
  {
    self_lsa.insert(pair<int, int>(neighbor.first->index, neighbor.second));
  }
  lsdb.insert(pair<int, LSA>(this->index, self_lsa));
}

bool Node::exchange_lsdb()
{
  bool changed = false;
  for (auto neighbor : neighbors)
  {
    changed = neighbor.first->add_and_broadcast_lsa(this->index, this->index, this->lsdb[this->index]) || changed;
  }
  return changed;
}

bool Node::add_and_broadcast_lsa(int index, int recieve_index, LSA lsa)
{
  if (lsdb.find(index) != lsdb.end())
    return false;
  lsdb.insert(pair<int, LSA>(index, lsa));
  broadcast_lsa(index, recieve_index, lsa);
  return true;
}

void Node::broadcast_lsa(int index, int recieve_index, LSA lsa)
{
  for (auto neighbor : neighbors)
  {
    if (neighbor.first->index == index)
      continue;
    if (neighbor.first->index == recieve_index)
      continue;

    neighbor.first->add_and_broadcast_lsa(index, this->index, lsa);
  }
}

void Node::print_lsdb()
{
  cout << "\nPrinting for node: " << this->index << endl;
  for (auto ls : lsdb)
  {
    cout << "Node:" << ls.first << " ";
    cout << "LSA: ";
    for (auto a : ls.second)
    {
      cout << a.first << "(" << a.second << ")"
           << "  ";
    }
    cout << endl;
  }
}

void Node::run_lsrp_algo()
{
  vector<int> N = get_all_nodes();
  unordered_map<int, int> C = get_init_cost_nodes(N);
  unordered_map<int, vector<int>> path_map = get_init_path_map(N);
  vector<int> M;
  M.push_back(this->index);

  int ittr = 1;

  while (M.size() != N.size())
  {
    auto value = get_min_node(N, M, C);
    M.push_back(value);
    update_cost(N, M, C, path_map);
    print_cost_map(ittr, C);
    ittr++;
  }
  make_lsrp_table(C, path_map);
}

vector<int> Node::get_all_nodes()
{
  vector<int> result;
  for (auto node : this->lsdb)
  {
    result.push_back(node.first);
  }
  return result;
}

unordered_map<int, int> Node::get_init_cost_nodes(vector<int> N)
{
  unordered_map<int, int> result;
  for (auto n : N)
  {
    result.insert(pair<int, int>(n, get_cost_to_node(n)));
  }
  return result;
}

unordered_map<int, vector<int>> Node::get_init_path_map(vector<int> N)
{
  unordered_map<int, vector<int>> result;
  for (auto n : N)
  {
    if (get_cost_to_node(n) == -1)
      continue;
    vector<int> path;
    path.push_back(index);
    path.push_back(n);
    result.insert(pair<int, vector<int>>(n, path));
  }
  return result;
}

int Node::get_min_node(vector<int> N, vector<int> M, unordered_map<int, int> C)
{
  int value = 0;
  int cost = INFINITY;

  for (auto n : N)
  {
    if (find(M.begin(), M.end(), n) != M.end())
      continue;

    if (C[n] == -1)
      continue;

    if (cost > C[n])
    {
      cost = C[n];
      value = n;
    }
  }
  return value;
}

void Node::update_cost(vector<int> N, vector<int> M, unordered_map<int, int> &C, unordered_map<int, vector<int>> &path_map)
{
  auto w = M[M.size() - 1];
  for (auto n : N)
  {
    if (find(M.begin(), M.end(), n) != M.end())
      continue;

    if ((C[n] == -1 && get_cost_from_lsdb(w, n) != INFINITY) || (C[n] > C[w] + get_cost_from_lsdb(w, n)))
    {
      C[n] = C[w] + get_cost_from_lsdb(w, n);
      path_map[n] = prepend_to_path(path_map[w], n);
    }
  }
}

vector<int> Node::prepend_to_path(vector<int> path, int index)
{
  vector<int> new_path;
  for (auto index : path)
  {
    new_path.push_back(index);
  }
  new_path.push_back(index);
  return new_path;
}

int Node::get_cost_from_lsdb(int src, int dest)
{
  auto src_lsa = lsdb[src];
  if (src_lsa.find(dest) != src_lsa.end())
    return src_lsa[dest];
  return INFINITY;
}

// std::vector<int> update_path(std::vector<int> path, int new_index)
// {
//   vector<int> res;

// }
void Node::print_cost_map(int itter, unordered_map<int, int> C)
{
  cout << "\n\t"
       << "Iter: " << itter << "\t\t" << endl;
  cout << "Dest\t";
  for (auto c : C)
  {
    cout << c.first << "\t";
  }
  cout << endl;
  cout << "Cost\t";

  for (auto c : C)
  {
    cout << c.second << "\t";
  }
  cout << endl;
  cout << "-----------------------------------" << endl;
}

void Node::make_lsrp_table(std::unordered_map<int, int> C, unordered_map<int, vector<int>> path_map)
{
  for (auto c : C)
  {
    lsrp_table.insert(pair<int, Route>(c.first, get_lsrp_route(c.first, c.second, path_map[c.first])));
  }
}

Route Node::get_lsrp_route(int dest, int cost, vector<int> path)
{
  Route route;
  route.cost = cost;
  route.destination = dest;
  route.path = path;
  return route;
}

void Node::print_lsrp_table()
{
  cout << "\n\nPrinting lsrp table for node: " << this->index << endl;
  cout << "Dest\t"
       << "Min-Cost\t"
       << "Shortest Path\t" << endl;
  cout << "---------------------------------" << endl;
  for (auto r : lsrp_table)
  {
    if (r.first == index)
      continue;
    cout << r.second.destination << "\t";
    cout << r.second.cost << "\t";
    cout << print_path(r.second.path) << "\t";
    cout << endl;
  }
}


void Node::reset()
{
  dvrp_table.clear();
  lsrp_table.clear();
  lsdb.clear();
}