import os
from matplotlib import pyplot as plt

BANDWIDTH_LIST = [1.5, 55, 155]
BASE_PS = 512
BASE_ER = 0.000001

bandwidth_change_senarios = [(bandwidth, BASE_PS, BASE_ER*10) for bandwidth in BANDWIDTH_LIST]
error_rate_change_senarios = [(BANDWIDTH_LIST[0], BASE_PS, BASE_ER*alpha) for alpha in range(1,11)]
packet_size_change_senarios = [(BANDWIDTH_LIST[0], BASE_PS * alpha, BASE_ER*10) for alpha in range(1,31,3)]


def run_senarios(senarios):
  results = []
  for senario in senarios:
    if 0 != os.system("ns sim_script.tcl " + str(senario[0]) + " " + str(senario[1]) + " " + str(senario[2])):
      print("Simulation script runnig: Error occured. Aborting ... ")
      exit(1)
    
    stream = os.popen("python3 parser.py sim_tr.tr")
    results.append(tuple(map(float, stream.read().split(' '))))
    stream.close()
  return results


bandwidth_results = run_senarios(bandwidth_change_senarios)
error_rate_results = run_senarios(error_rate_change_senarios)
packet_size_results = run_senarios(packet_size_change_senarios)


fig = plt.figure(figsize=(5, 10))
gs = fig.add_gridspec(3, hspace=0.5)
axes = gs.subplots()
fig.suptitle('Change in Bandwidth(ER=1e-5 & PS=512B)')
axes[0].plot(BANDWIDTH_LIST, [item[0] for item in bandwidth_results], '-o')
axes[0].set_title("Throughput")
axes[0].set_xlabel("Mbps")
axes[0].set_ylabel("Kbps")

axes[1].plot(BANDWIDTH_LIST, [item[1] for item in bandwidth_results], '-o')
axes[1].set_title("Packet Transfer Ratio")
axes[1].set_xlabel("Mbps")
axes[1].set_ylabel("percent")

axes[2].plot(BANDWIDTH_LIST, [item[2] for item in bandwidth_results], '-o')
axes[2].set_title("Avg E-E-Delay")
axes[2].set_xlabel("Mbps")
axes[2].set_ylabel("sec")

# plt.show()


packet_size_list = [item[1] for item in packet_size_change_senarios]
fig = plt.figure(figsize=(5, 10))
gs = fig.add_gridspec(3, hspace=0.5)
axes = gs.subplots()
fig.suptitle('Change in PacketSize(BW=1.5Mbps & ER=1e-5)')
axes[0].plot(packet_size_list, [item[0] for item in packet_size_results], '-o')
axes[0].set_title("Throughput")
axes[0].set_xlabel("Byte")
axes[0].set_ylabel("Kbps")

axes[1].plot(packet_size_list, [item[1] for item in packet_size_results], '-o')
axes[1].set_title("Packet Transfer Ratio")
axes[1].set_xlabel("Byte")
axes[1].set_ylabel("percent")

axes[2].plot(packet_size_list, [item[2] for item in packet_size_results], '-o')
axes[2].set_title("Avg E-E-Delay")
axes[2].set_xlabel("Byte")
axes[2].set_ylabel("sec")

# plt.show()


error_rate_list = [item[2] for item in error_rate_change_senarios]
fig = plt.figure(figsize=(5, 10))
gs = fig.add_gridspec(3, hspace=0.5)
axes = gs.subplots()
fig.suptitle('Change in ErrorRate(BW=1.5Mbps & PS=512B)')
axes[0].plot(error_rate_list, [item[0] for item in error_rate_results], '-o')
axes[0].set_title("Throughput")
axes[0].set_ylabel("Kbps")

axes[1].plot(error_rate_list, [item[1] for item in error_rate_results], '-o')
axes[1].set_title("Packet Transfer Ratio")
axes[1].set_ylabel("percent")

axes[2].plot(error_rate_list, [item[2] for item in error_rate_results], '-o')
axes[2].set_title("Avg E-E-Delay")
axes[2].set_ylabel("sec")

plt.show()

