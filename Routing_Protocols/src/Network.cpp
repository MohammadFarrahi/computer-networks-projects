#include "Network.hpp"
#include "Util.hpp"
#include <iostream>

using namespace std;

void Network::create_topology(Statement topology)
{
  for (auto statement : topology)
  {
    create_single_connection(statement);
  }
}

void Network::create_single_connection(string statement)
{
  auto statement_parts = Util::tokenize(statement, "-");

  int node_index_1 = stoi(statement_parts[0]);
  int node_index_2 = stoi(statement_parts[1]);
  int cost = stoi(statement_parts[2]);

  if (node_index_1 == node_index_2)
    throw DUPLICATE_NODE_EXCEPTION_CODE;

  auto node1 = find_or_create_node(node_index_1);
  auto node2 = find_or_create_node(node_index_2);

  node1->add_neighbor(node2, cost);
  node2->add_neighbor(node1, cost);
}

Node *Network::find_or_create_node(int index)
{
  if (nodes.find(index) == nodes.end())
  {
    nodes[index] = new Node(index);
  }
  return nodes[index];
}

Node *Network::get_node(int index)
{
  if (nodes.find(index) == nodes.end())
  {
    throw NO_NODE_EXCEPTION_CODE;
  }
  return nodes[index];
}

void Network::show_network()
{
  print_header();
  for (auto node : nodes)
  {
    cout << node.first << "|\t";
    print_one_node(node.second);
  }
}

void Network::print_header()
{
  cout << "\nShowing network..." << endl;
  cout << "*|\t";
  for (auto node : nodes)
    cout << node.first << "\t";
  cout << endl;
  cout << "-----------------------------------" << endl;
}

void Network::print_one_node(Node *node)
{
  for (auto n : nodes)
  {
    cout << node->get_cost_to_node(n.first) << "\t";
  }
  cout << endl;
}

void Network::modify(Statement modification_statement)
{
  auto statement_parts = Util::tokenize(modification_statement[0], "-");

  int node_index_1 = stoi(statement_parts[0]);
  int node_index_2 = stoi(statement_parts[1]);
  int cost = stoi(statement_parts[2]);

  if (node_index_1 == node_index_2)
    throw DUPLICATE_NODE_EXCEPTION_CODE;

  auto node1 = get_node(node_index_1);
  auto node2 = get_node(node_index_2);

  node1->add_neighbor(node2, cost);
  node2->add_neighbor(node1, cost);
  reset_state();
}

void Network::remove(Statement removal_statement)
{
  auto statement_parts = Util::tokenize(removal_statement[0], "-");

  int node_index_1 = stoi(statement_parts[0]);
  int node_index_2 = stoi(statement_parts[1]);

  if (node_index_1 == node_index_2)
    throw DUPLICATE_NODE_EXCEPTION_CODE;

  auto node1 = get_node(node_index_1);
  auto node2 = get_node(node_index_2);

  node1->remove_neighbor(node2);
  node2->remove_neighbor(node1);
  reset_state();
}

void Network::dvrp_algo(Statement node_statement)
{
  auto convergence_count = run_dvrp_algo();
  if (node_statement.size() > 0)
    print_dvrp_for_one(stoi(node_statement[0]));
  else
    print_dvrp_for_all();

  cout << "\nCONVERGENCE COUNT: " << convergence_count << endl;
}

int Network::run_dvrp_algo()
{
  init_dvrp_tables();
  bool changed = true;
  int convergence_count = 0;
  while (changed)
  {
    changed = false;
    for (auto node_pair : nodes)
    {
      changed = node_pair.second->exchange_dvrp_table() || changed;
    }
    convergence_count++;
  }
  return convergence_count;
}

void Network::init_dvrp_tables()
{
  for (auto node_pair : nodes)
  {
    node_pair.second->create_dvrp_table();
  }
}

void Network::print_dvrp_for_one(int node_index)
{
  auto node = find_or_create_node(node_index);
  node->print_dvrp_table();
}

void Network::print_dvrp_for_all()
{
  for (auto n : nodes)
  {
    n.second->print_dvrp_table();
  }
}

void Network::lsrp_algo(Statement node_statement)
{
  int convergence_count = run_lsrp_flodding();
  if (node_statement.size() > 0)
    print_lsrp_for_one(stoi(node_statement[0]));
  else
    print_lsrp_for_all();
  cout << "\nCONVERGENCE COUNT: " << convergence_count << endl;
}

int Network::run_lsrp_flodding()
{
  init_lsdbs();
  bool changed = true;
  int convergence_count = 0;
  while (changed)
  {
    changed = false;
    for (auto node_pair : nodes)
    {
      changed = node_pair.second->exchange_lsdb() || changed;
    }
    convergence_count++;
  }
  return convergence_count;
}

void Network::init_lsdbs()
{
  for (auto n : nodes)
  {
    n.second->init_lsdb();
  }
}

void Network::print_lsrp_for_one(int index)
{
  auto node = find_or_create_node(index);
  node->run_lsrp_algo();
  node->print_lsrp_table();
}

void Network::print_lsrp_for_all()
{
  for (auto n : nodes)
  {
    n.second->run_lsrp_algo();
    n.second->print_lsrp_table();
  }
}

void Network::reset_state()
{
  for (auto n : nodes)
  {
    n.second->reset();
  }
}