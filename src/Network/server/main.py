##
## EPITECH PROJECT, 2020
## OOP_indie_studio_2019
## File description:
## main
##

import select
import socket
import sys
import queue
import random

lobbys = [] 

def main():
    server, server_udp = networkInit()
    selectLoop(server, server_udp)

def selectLoop(server, server_udp):
    inputs = [server, server_udp]

    while inputs:
        readable, writable, exceptional = select.select(inputs, [], inputs)
        for s in readable:
            if s is server:
                connection, client_address = s.accept()
                connection.setblocking(0)
                inputs.append(connection)
            elif s is server_udp:
                message, adress = s.recvfrom(1024)
            else:
                try:
                    data = s.recv(1024)
                    if data:
                        for req in data.decode().split("\n"):
                            clientCommandHandler(req, s)
                    else:
                        inputs.remove(s)
                        s.close()
                except Exception as e:
                    print(e)
        for s in exceptional:
            inputs.remove(s)
            s.close()

def clientCommandHandler(request, connection):

    # request create a lobby
    if request.startswith("req cl"):
        nb = int(request.split(" ")[2])
        time = float(request.split(" ")[3])
        while True:
            ranid = random.randint(10000, 99999)
            exist = False
            for lobby in lobbys:
                if (ranid == lobby["id"]):
                    exist = True
            if exist is False:
                break;
        lobbys.append({
            "id": ranid,
            "players": [connection],
            "max": nb,
            "time": time
        })
        print("Create lobby with index " + str(ranid))
        connection.send(("res cl " + str(ranid) + " \n").encode())
    
    # request join a lobby
    elif request.startswith("req jl"):
        try:
            idx = int(request.split(" ")[2])
            exist = False
            for lobby in lobbys:
                if (idx == lobby["id"] or idx == -1) and len(lobby["players"]) < lobby["max"]:
                    idx = lobby["id"]
                    lobby["players"].append(connection)
                    exist = True
            if not exist:
                raise Exception('ID not exist')
            print("Join lobby with index " + str(idx))
            connection.send(("res jl " + str(idx) + " \n").encode())
        except:
            print("Lobby " + str(idx) + " not found")
            connection.send("err lnf \n".encode())

    # request start the game
    elif request.startswith("req sg"):
        try:
            idx = int(request.split(" ")[2])
            exist = False
            for lobby in lobbys:
                if (idx == lobby["id"]):
                    i = 0
                    print("Start game for lobby " + str(idx))
                    for player in lobby["players"]:
                        print("a")
                        print(lobby["max"] - len(lobby["players"]))
                        player.send(("res sg " + str(i) + " " + str(lobby["max"]) + " " + str(lobby["max"] - len(lobby["players"])) + " " + str(lobby["time"]) + " \n").encode())
                        i += 1
                    exist = True
            if not exist:
                raise Exception('ID not exist')
        except:
            print("Lobby " + idx + " not found")
            connection.send("err lnf \n".encode())

    # share events
    elif request.startswith("evt"):
        print("Event received: " + request)
        lobbyIdx = int(request.split(" ")[2])
        for lobby in lobbys:
            if (lobbyIdx == lobby["id"]):
                for player in lobby["players"]:
                    if (player != connection):
                        player.send((request).encode())
    

def networkInit():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    server.setblocking(0)

    server_udp.setblocking(0)
    server_udp.settimeout(5)

    if (len(sys.argv) != 3):
        print("./BombermanServer adress port")
        exit(84)
    server_address = (sys.argv[1], int(sys.argv[2]))

    server.bind(server_address)
    server_udp.bind(server_address)

    server.listen(5)

    return (server, server_udp)