#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <math.h>
#include <netdb.h>
#include <thread>
#include <arpa/inet.h>
#include <assert.h>
#include <chrono>
#include <queue>
#include <mutex>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <limits.h>
#include "packet.h"

using namespace std;

class flow
{
public:
  // To judge whether a flow f is an LDOS attack or a normal
  int indicator;
  // Last time the packet was dropped by the Robust filter
  int T1;

  flow()
  {
    indicator = 10;
    T1 = INT_MIN;
  }
};

class gateway
{
public:
  int sockid, maxNumClients, simTime, portNo, receivedLastPackets;
  struct sockaddr_in addrport, clientAddr;
  socklen_t clilen;
  int *clientsSockid;
  queue<packet> Queue;
  mutex mtx;  // For RED() packet synchronization
  mutex mtx2; // For bufferPackets synchronization
  mutex mtx3; // For receivedLastPacket variable's synchronization
  vector<packet> bufferPackets;
  map<int, int> portId; // For mapping dest port nos to outlink's port no.
  map<int, int> mp;     // Sort of forwarding table
  ofstream fout;

  // RED Algorithm's parameters
  double avg = 0;    // Average queue length
  int count = -1;    // Count of packets since last probabilistic drop
  double wq = 0.003; // Queue weight; standard value of 0.002 for early congestion detection
  int minThreshold = 5, maxThreshold = 17;
  double maxp = 0.02; // Maximum probability of dropping a packet; standard value of 0.02
  double pb = 0;      // Probability of dropping a packet
  time_t qTime;       // Time since the queue was last idle

  // WRED Parameters
  // Thresholds for various priority
  int *WREDminThresholds;
  int *WREDmaxThresholds;

  // TailDrop Parameters
  int maxQueueSize;

  // RRED paramters
  int T2 = INT_MIN;
  int Tstar = 1;
  map<pair<int, int>, flow> mpFlow;

  // Constructor for Gateway object
  gateway(int indexNo, int simulationTime, string traffic, string topologyPath)
  {
    simTime = simulationTime;

    // Reading topology file for getting the info of the gateway
    ifstream fin;
    string fileName = topologyPath;

    assert(fileName.find("topology") != string::npos);

    fin.open(fileName);
    string line;
    while (getline(fin, line))
    {
      if (line == ("#" + to_string(indexNo + 1)))
      {
        break;
      }
    }

    fin >> portNo >> maxNumClients;
    cout << "Port number of gateway = " << portNo << "\nNumber of inlinks = " << maxNumClients << endl;
    int szMap, e1, e2;
    fin >> szMap;

    for (int i = 0; i < szMap; i++)
    {
      fin >> e1 >> e2;
      portId[e1] = e2;
    }

    fin.close();
    cout << "Topology file read\n";
    // Topology reading complete

    // Get output file path(topology must be in topology folder)
    string outputPath = fileName.substr(0, fileName.find("topology"));
    string outFileName = outputPath + "/log/log-" + to_string(indexNo + 1) + ".txt";
    fout.open(outFileName);
    // NOTE: Writing traffic level to log file

    // for plotter to read
    fout << traffic << endl;
  }

  // Destructor for closing the fstream object
  ~gateway()
  {
    fout.close();
  }

  /* Methods for the Gateway */
  void setupConnection();

  // Method for simulating RED algorithm on a packet
  void red(packet &packet);

  // Method for simulating WRED algorithm on a packet
  void wred(packet &packet);

  // Method for simulating taildrop algorithm on a packet
  void taildrop(packet &packet);

  // Deques the queue and also sends the packet to the corresponding outlink
  void dequeQueue();

  // set Thresholds for WRED algorithm
  void setThresholds(const int *minThresholds, const int *maxThresholds, int n_priorities);

  // This method simulates each burst by calling red() on each packet of burst
  void simulateRED();

  // This method simulates each burst by calling wred() on each packet of burst
  void simulateWRED();

  // This method simulates each burst by calling taildrop on each packet of burst
  void simulateTD();

  // RED block internally used by RRED
  bool REDBlock(packet &packet);

  void simulateRRED(int arrivalTime);

  // The gateway creates thread for each client and calls this method
  void receivePackets(int id);

  // setter for max queue size
  void setMaxQueueSize(int size);

  // This method accepts connection from all clients
  // and creates connection to the outlinks as well
  // The simulateRED() method is called from this method
  void acceptMethod(int index, string traffic);

  // Helper method to show the contents of the queue
  void showq(queue<packet *> q);
};