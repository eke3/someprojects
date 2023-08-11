"""
File:    the_internet.py
Author:  Eric Ekey
Date:    12/09/2021
Section: 35
E-mail:  eekey1@umbc.edu
Description:
  the internet
"""


# GLOBAL CONSTANTS FOR USER COMMANDS
CREATE_SERVER = "create-server"
CREATE_CONNECTION = ["create-connection", "connect"]
SET_SERVER = ["set-server", "set"]
IP_CONFIG = ["ip-config", "ip", "where"]
DISPLAY_SERVERS = ["display-servers", "display", "list", "list-servers", "server-list"]
PING = "ping"
TRACEROUTE = ["traceroute", "tracert", "trace", "path", "pathfind", "find-path", "find"]


def create_server(name, ip):
    """
    creates a server with a name and ip
    :param name: name of server
    :param ip: ip of server
    :return:
    """
    if name not in internet:
        invalid = 0
        for server in internet:
            ip_pos = internet[server][0]
            if ip == ip_pos:
                invalid = invalid + 1
        if invalid:
            print("Failed: ip address already exists")
        else:
            internet[name] = [ip, {}]
            print("Success: A server with the name " + name + " was created at ip " + ip)
    else:
        print("Failed: Server name already exists")


def validate_ip(ip):
    """
    validates user input for ip address
    :param ip: user input for ip address
    :return: True or False for whether the ip is valid
    """
    valid = False
    ip = ip.split(".")
    for word in ip:
        word = int(word)
        if 0 <= word <= 255:
            if len(str(word)) <= 3:
                valid = True
            else:
                print("Failed: Invalid ip address")
                return False
        else:
            print("Failed: Invalid ip address")
            return False
        for letter in str(word):
            if ord(letter) < 48 or ord(letter) > 57:
                return False
    for server in internet:
        if ip != server[0]:
            valid = True
        else:
            print("Failed: ip already exists")
            return False
    if len(ip) == 4:
        return valid
    print("Failed: Invalid ip address")
    return False


def set_server(name_or_ip, prev_server):
    """
    sets the current location on the internet
    :param name_or_ip: name or ip of server to set as current location
    :param prev_server: current location immediately before running this command
    :return: new current server or previous current server if input invalid
    """
    if len(internet):
        if name_or_ip in internet:
            print("Server " + name_or_ip + " selected.")
            return name_or_ip
        else:
            for server in internet:
                ip_pos = internet[server][0]
                if name_or_ip == ip_pos:
                    print("Server " + server + " selected.")
                    return server
            print("Failed: Server " + name_or_ip + " does not exist")
    else:
        print("Failed: No servers exist")
        return prev_server


def ip_config(current_server):
    """
    prints the name and ip of the current server
    :param current_server: the current server
    :return: what to display to the user
    """
    if current_server:
        ip_pos = internet[current_server][0]
        return current_server + "\t" + ip_pos
    else:
        return "Failed: Not connected to a server"


def display_servers():
    """
    prints a list of all servers, their ip addresses, and their connections
    :return:
    """
    for server in internet:
        ip_pos = internet[server][0]
        connection_dict = internet[server][1]
        print("\t" + server + "\t" + ip_pos)
        if len(connection_dict):
            for connection in connection_dict:
                print("\t\t" + connection + "\t" + internet[connection][0])


def validate_connection(ping_time):
    """
    validates connection time for letters
    :param ping_time: connection time
    :return: true or false for whether number is valid
    """
    for number in str(ping_time):
        if 48 <= ord(number) <= 57:
            valid = True
        else:
            return False
        return valid


def create_connection(srv_1, srv_2, ping):
    """
    creates a connection between 2 servers
    :param srv_1: first server input by user
    :param srv_2: second server input by user
    :param ping: connection time between the 2 servers input by user
    :return:
    """
    if srv_1 != srv_2:  # if the user does not enter the same servername twice
        if srv_1 in internet and srv_2 in internet:  # if both servers exist
            if srv_2 not in internet[srv_1][1]:
                valid = validate_connection(ping)
                if valid:
                    internet[srv_1][1][srv_2] = [[internet[srv_2][0], ping]]
                    internet[srv_2][1][srv_1] = [[internet[srv_1][0], ping]]
                    print("Success: A server with name " + srv_1 + " is now connected to " + srv_2)
                else:
                    print("Failed: Invalid connect time")
            elif srv_2 in internet[srv_1][1]:  # if the servers are already connected
                internet[srv_1][1][srv_2].append([internet[srv_2][0], ping])
                internet[srv_2][1][srv_1].append([internet[srv_1][0], ping])
                print("Failed: A server with name " + srv_1 + " is already connected to " + srv_2)
        else:
            print("Failed: Servers " + srv_1 + " and " + srv_2 + " do not both exist")
    else:
        print("Failed: Server cannot connect to itself")


def traceroute(destination_name_or_ip, current_location, visited):
    """
    finds a route from the current server to a destination server via connections
    :param destination_name_or_ip: ip or name of destination server
    :param current_location: current server
    :param visited: dictionary containing list of visited servers
    :return:
    """
    if destination_name_or_ip == current_location:  # termination case
        return
    else:
        for loc in internet[current_location][1]:  # recursive case
            if loc not in visited:
                visited.append(loc)
                visited_ips["visited ips"].append(internet[loc][0])
                if current_location in internet[loc][1]:
                    ping_times["ping times"].append(int(internet[loc][1][current_location][0][1]))
                    traceroute(destination_name_or_ip, loc, visited)


if __name__ == "__main__":
    internet = {}  # dictionary with a key for every server
    current_server = None

    command = input(">>> ")
    command = command.strip().lower().split()

    while command != ["quit"]:
        if command[0] == CREATE_SERVER and len(command) == 3:
            valid_ip = validate_ip(command[2])  # True or False
            if valid_ip:
                create_server(command[1], command[2])
        elif command[0] in CREATE_CONNECTION and len(command) == 4:
            create_connection(command[1], command[2], command[3])
        elif command[0] in SET_SERVER and len(command) == 2:
            current_server = set_server(command[1], current_server)
        elif command[0] in IP_CONFIG and len(command) == 1:
            print(ip_config(current_server))
        elif command[0] in DISPLAY_SERVERS and len(command) == 1:
            display_servers()
        elif command[0] in TRACEROUTE and len(command) == 2:
            if current_server:
                visited_dict = {}
                ip = None
                for i in internet:
                    if command[1] == i:
                        visited_dict = {"visited": [current_server]}
                        visited_ips = {"visited ips": [internet[current_server][0]]}
                        ping_times = {"ping times": [0]}
                        traceroute(command[1], current_server, visited_dict["visited"])
                    elif command[1] == internet[i][0]:
                        ip = str(i)  # storing the ip for use outside this loop
                        visited_dict = {"visited": [current_server]}
                        visited_ips = {"visited ips": [internet[current_server][0]]}
                        ping_times = {"ping times": [0]}
                        traceroute(i, current_server, visited_dict["visited"])
                if command[1] in visited_dict["visited"]:
                    print("Tracing route to " + command[1])
                    for each in range(len(visited_dict["visited"])):
                        print("\t", each, "\t" + str(ping_times["ping times"][each]) + "\t["
                              + str(visited_ips["visited ips"][each]) + "]\t" + visited_dict["visited"][each])
                    print("Trace complete.")
                elif command[1] in visited_ips["visited ips"]:  # if user inputs ip address instead of server name
                    print("Tracing route to " + command[1])
                    for i in internet:
                        if internet[i][0] == command[1]:
                            command[1] = str(i)
                    for each in range(len(visited_dict["visited"])):
                        print("\t", each, "\t" + str(ping_times["ping times"][each]) + "\t["
                              + str(visited_ips["visited ips"][each]) + "]\t" + visited_dict["visited"][each])
                    print("Success: Trace complete.")
                else:
                    print("Failed: Unable to resolve target system name " + command[1])
            else:
                print("Failed: No starting point")
        elif command[0] == PING and len(command) == 2:
            if current_server:
                visited_dict = {}
                ip = None
                for i in internet:
                    if command[1] == i:
                        visited_dict = {"visited": [current_server]}
                        visited_ips = {"visited ips": [internet[current_server][0]]}
                        ping_times = {"ping times": [0]}
                        traceroute(command[1], current_server, visited_dict["visited"])
                    elif command[1] == internet[i][0]:
                        ip = str(i)  # storing the ip for use outside this loop
                        visited_dict = {"visited": [current_server]}
                        visited_ips = {"visited ips": [internet[current_server][0]]}
                        ping_times = {"ping times": [0]}
                        traceroute(i, current_server, visited_dict["visited"])
                if command[1] in visited_dict["visited"]:
                    ping_ms = 0
                    for num in ping_times["ping times"]:
                        ping_ms = ping_ms + num
                    print("Pong!\nReply from " + str(internet[command[1]][0]) + "\ttime =", ping_ms, "ms")
                elif command[1] in visited_ips["visited ips"]:  # if user inputs ip address instead of server name
                    ping_ms = 0
                    for num in ping_times["ping times"]:
                        ping_ms = ping_ms + num
                    print("Pong!\nReply from " + str(internet[command[1]][0]) + "\ttime =", ping_ms, "ms")
                else:
                    print("Failed: Unable to resolve target system name " + command[1])
            else:
                print("Failed: No starting point")
        else:
            print("Error: Invalid command")

        command = input(">>> ")
        command = command.strip().lower().split()

