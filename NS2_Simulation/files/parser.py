import sys
import os

from numpy import sort

def get_file_lines(filename):
  lines = []
  with open(filename, 'r') as f:
    lines = f.readlines()
  return lines


def get_packets_info(src, dst, type, trace_info):
  def predicate(line):
    node = src
    if type == 'r':
      node = dst
    if (line[0] == type) and ('_' + node + '_ AGT ' in line):
      src_dst_info = line.split('] ------- [')[1].split(']')[0]
      src_dst_info = src_dst_info.split(' ')
      if src_dst_info[0].split(':')[0] == src and src_dst_info[1].split(':')[0] == dst:
        return True
    return False

  def info_extrcator(line):
    splited = line.split(' ')
    return (int(splited[6]) ,(float(splited[1]), int(splited[8])))
  
  return dict(map(info_extrcator, filter(predicate, trace_info)))


def get_throughput(recieved, sent):
  transfer_size, max_time, min_time = 0.0, 0.0, 100.0
  for pckt in recieved.items():
    pckt_s = sent[pckt[0]]
    if not pckt[1][1] == pckt_s[1]:
      print("Throughput: Invalid info in tr file")
      exit(1)
    transfer_size += pckt_s[1]
    min_time = min(min_time, pckt_s[0])
    max_time = max(max_time, pckt[1][0])
    # transfer_time += pckt[1][0] - pckt_s[0]
  
  return (8*transfer_size/1000) / (max_time - min_time)

def get_packet_transfer_ratio(recieved, sent):
  return 100 * len(recieved) / len(sent)

def get_average_delay(recieved, sent):
  sum_of_delays = 0.0
  for pckt in recieved.items():
    pckt_s = sent[pckt[0]]
    if not pckt[1][0] > pckt_s[0]:
      print("AvgDelay: Invalid info in tr file")
      exit(1)
    sum_of_delays += pckt[1][0] - pckt_s[0]
  
  return sum_of_delays / len(recieved)



  

if len(sys.argv) != 2:
  print("This parser requires a TraceFilePath argument to be passed. Aborting ...")
  exit(1)
if not os.path.isfile(sys.argv[1]):
  print("The FilePath argument is not valid. Aborting ...")
  exit(1)


file_lines = get_file_lines(sys.argv[1])

A_to_H_sent = get_packets_info('0', '7', 's', file_lines)
A_to_L_sent = get_packets_info('0', '8', 's', file_lines)
D_to_H_sent = get_packets_info('3', '7', 's', file_lines)
D_to_L_sent = get_packets_info('3', '8', 's', file_lines)

A_to_H_recieved = get_packets_info('0', '7', 'r', file_lines)
A_to_L_recieved = get_packets_info('0', '8', 'r', file_lines)
D_to_H_recieved = get_packets_info('3', '7', 'r', file_lines)
D_to_L_recieved = get_packets_info('3', '8', 'r', file_lines)

# print(len(A_to_H_sent), len(A_to_H_recieved))
# print(len(A_to_L_sent), len(A_to_L_recieved))
# print(len(D_to_H_sent), len(D_to_H_recieved))
# print(len(D_to_L_sent), len(D_to_L_recieved))

# print(sorted(A_to_H_sent.keys()) == sorted(A_to_H_recieved.keys()))
# print(sorted(A_to_L_sent.keys()) == sorted(A_to_L_recieved.keys()))
# print(sorted(D_to_L_sent.keys()) == sorted(D_to_L_recieved.keys()))
# print(sorted(D_to_H_sent.keys()) == sorted(D_to_H_recieved.keys()))


# print(all(item in A_to_H_sent.keys() for item in A_to_H_recieved.keys()))
# print(all(item in A_to_L_sent.keys() for item in A_to_L_recieved.keys()))
# print(all(item in D_to_L_sent.keys() for item in D_to_L_recieved.keys()))
# print(all(item in D_to_H_sent.keys() for item in D_to_H_recieved.keys()))

recieved = {**A_to_H_recieved, **A_to_L_recieved, **D_to_H_recieved, **D_to_L_recieved}
sent = {**A_to_H_sent, **A_to_L_sent, **D_to_H_sent, **D_to_L_sent}

x = get_throughput(recieved, sent)
y = get_packet_transfer_ratio(recieved, sent)
z = get_average_delay(recieved, sent)

print(x,y,z, end='')