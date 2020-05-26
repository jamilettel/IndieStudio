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
import uuid

lobbys = [] 

def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.setblocking(0)
    server_address = ('localhost', 8000)
    server.bind(server_address)
    server.listen(5)

    inputs = [server]

    while inputs:
        readable, writable, exceptional = select.select(inputs, [], inputs)
        for s in readable:
            if s is server:
                connection, client_address = s.accept()
                connection.setblocking(0)
                inputs.append(connection)
            else:
                try:
                    data = s.recv(1024)
                    if data:
                        clientCommandHandler(data.decode(), s)
                    else:
                        inputs.remove(s)
                        s.close()
                except:
                    pass
        for s in exceptional:
            inputs.remove(s)
            s.close()


def clientCommandHandler(request, connection):
    if request == "create lobby\n":
        lobbys.append({
            "uuid": uuid.uuid4(),
            "players": [connection]
        })
        connection.send("lobby created\n".encode())
    if request == "list lobbys\n":
        response = ""
        for lobby in lobbys:
            response += lobby["uuid"] + " "
        connection.send(response + "\n".encode())
    if request.startswith("join lobby"):
        #idx = int(request.split(" ")[2])
        lobbys[0]["players"].append(connection)
        connection.send("lobby joined\n".encode())
    if request == "start game\n":
        for lobby in lobbys:
            for player in lobby["players"]:
                if (player == connection):
                    i = 0
                    for player in lobby["players"]:
                        print(player)
                        player.send(("p" + str(i) + "\n").encode())
                        i += 1


