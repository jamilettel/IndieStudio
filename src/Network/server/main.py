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

'''

Rentre dans menu multiplayer -> connection au serveur

    -> creer lobby = crée un room dans le serveur
    -> rejoindre lobby = list des lobby

    -> menu lobby avec le nombre de personnes connectés

    -> lancer game

'''

def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.setblocking(0)
    server_address = ('localhost', 8000)
    server.bind(server_address)
    server.listen(5)

    inputs = [server]
    outputs = []

    readCmdQueue = {}
    writeCmdQueue = {}

    while inputs:
        readable, writable, exceptional = select.select(inputs, outputs, inputs)
        for s in writable:
            try:
                next_msg = writeCmdQueue[s].get_nowait()
            except queue.Empty:
                pass
            else:
                print(next_msg)
                s.send(next_msg.encode())
                print(s)

        for s in readable:
            if s is server:
                connection, client_address = s.accept()
                connection.setblocking(0)
                inputs.append(connection)
                readCmdQueue[connection] = queue.Queue()
                writeCmdQueue[connection] = queue.Queue()
                print(connection)
            else:
                data = s.recv(1024)
                if data:
                    clientCommandHandler(data.decode(), writeCmdQueue[s])
                    readCmdQueue[s].put(data.decode())
                    if s not in outputs:
                        outputs.append(s)
                else:
                    if s in outputs:
                        outputs.remove(s)
                    inputs.remove(s)
                    s.close()
                    del readCmdQueue[s]
                    del writeCmdQueue[s]
        for s in exceptional:
            inputs.remove(s)
            if s in outputs:
                outputs.remove(s)
            s.close()
            del readCmdQueue[s]
            del writeCmdQueue[s]

def clientCommandHandler(request, queue):
    if request == "create lobby\n":
        queue.put("lobby created\n")
