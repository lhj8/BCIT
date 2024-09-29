from scapy.layers.inet import *
from scapy.all import *


def port_scanner(user_input):
    # host_name = socket.gethostname()
    # host_ip = socket.gethostbyname(host_name)
    # print(f"hostname : {host_name}")
    # print(f"host ip : {host_ip}")

    valid_ports = []
    for port in range(user_input['dst_port_start'], user_input['dst_port_end'] + 1):
        send_packet = IP(dst=user_input['dst_ip']) / \
                      TCP(dport=port, flags="S")
        response = sr1(send_packet, timeout=0.1, verbose=0)
        if response and response[TCP].flags == "SA":
            valid_ports.append(port)
        else:
            print("port", port, "[ X ]")

    print("\n========[ VALID PORT ]========")
    for port in valid_ports:
        print("* port", port)
