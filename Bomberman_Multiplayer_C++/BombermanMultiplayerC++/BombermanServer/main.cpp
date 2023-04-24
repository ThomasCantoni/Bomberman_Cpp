//import socket
//s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
//s.bind(('151.70.135.19', 8888))
//while True:
//    message, sender = s.recvfrom(4096)
//    print(message, sender)
//
//    if message == b'quit':
//        print("QUIT")
//        break
//print(message, sender)


#include <iostream>
#include "BombermanCore.h"
#include "Server.h"
int main(int argc, char* args[])
{
	Server::Initialize("127.0.0.1", 8888, 0);
	Server::Run();
	
}


//class Player :
//    def __init__(self, peer, player_id) :
//    self.peer = peer
//    self.transform = (0, 0)
//    self.player_id = player_id
//    self.last_packet_timestamp = time.time()
//
//    def get_packet_transform(self) :
//    return struct.pack(">II2f", self.player_id, 0, *self.transform)
//
//    def get_packet_announce(self) :
//    return struct.pack(">II2f", self.player_id, 1, *self.transform)
//
//    def get_packet_death(self) :
//    return struct.pack(">II", self.player_id, 2)
//
//    class Tile :
//    def __init__(self, id, x, y, w, h, isStatic) :
//    self.id = id
//    self.x = x
//    self.y = y
//    self.w = w
//    self.h = h
//    self.isStatic = isStatic
//
//    class Server :
//    def __init__(self, address, port, max_packet_size = 1024) :
//    self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
//    self.socket.bind((address, port))
//    self.max_packet_size = max_packet_size
//    self.blacklisted_clients = {}
//    self.known_clients = {}
//    self.socket.settimeout(1)
//    self.players_counter = 1
//    self.actors_to_sync = []
//    self.map_index = 0
//    self.map_names = ["materials\Maps\map1.txt"]
//
//    self.construct_map(0)
//
//    def construct_map(self, id) :
//    map_file = open(self.map_names[id], 'r')
//    lines = map_file.readlines()
//    i = 0
//    for line in lines :
//posx, posy, w, h, isStatic = line.split(',')[0:5]
//tile = Tile(i, posx, posy, w, h, isStatic)
//if (tile.isStatic == False) :
//    self.actors_to_sync.append(tile)
//    i = i + 1
//
//
//
//    def check_status(self) :
//    now = time.time()
//    dead_clients = []
//    for peer in self.known_clients :
//        player = self.known_clients[peer]
//        if now - player.last_packet_timestamp > 5:
//dead_clients.append(peer)
//
//# announce death
//for dead_peer in dead_clients :
//for peer in self.known_clients :
//    current_player = self.known_clients[peer]
//    if current_player.peer == dead_peer :
//        continue
//        self.socket.sendto(
//            self.known_clients[dead_peer].get_packet_death(),
//            current_player.peer,
//            )
//
//        for dead_peer in dead_clients :
//print("killing", dead_peer)
//self.players_counter - 1
//del self.known_clients[dead_peer]
//
//def process_message(self, packet, sender) :
//    # TODO blacklist
//
//    if len(packet) < 4:
//return
//player_id, command_id = struct.unpack("<II", packet[0:8])
//player = self.known_clients[sender]
//if player.player_id != player_id :
//    # TODO blacklist
//    #print(player.player_id)
//    print('player_id mismatch')
//    return
//    if command_id == 0:
//#print("client valid")
//x, y = struct.unpack("<ff", packet[8:16])
//# print("player_id = ", player_id)
//# print("command_id = ", command_id)
//# print("x = ", x)
//# print("y = ", y)
//player.last_packet_timestamp = time.time()
//player.transform = (x, y)
//for peer in self.known_clients:
//current_player = self.known_clients[peer]
//if current_player == player :
//    continue
//    # send my position to all of the other players
//    self.socket.sendto(player.get_packet_transform(), current_player.peer)
//    if command_id == 3:
//x, y = struct.unpack("<ff", packet[8:16])
//message = struct.pack(">IIff", player_id, 3, x, y)
//for peer in self.known_clients :
//    current_player = self.known_clients[peer]
//    # send eggbombs to all of the other players
//    self.socket.sendto(message, current_player.peer)
//
//
//
//    def run(self) :
//    while True :
//
//        #for tile in self.actors_to_sync:
//#    print(tile.x, tile.y, tile.w, tile.h, tile.isStatic)
//
//#os.system('cls')
//try :
//    packet, sender = self.socket.recvfrom(self.max_packet_size)
//    except TimeoutError :
//self.check_status()
//continue
//except :
//    continue
//    if sender in self.blacklisted_clients :
//        continue
//#if sender in self.challenged_clients:
//        #    self.check_challenge(packet, sender)
//        #    continue
//        #self.send_tick()
//        self.check_status()
//        #print(self.players_counter)
//
//
//        if sender in self.known_clients:
//# process message
//#print(sender, self.known_clients[sender].player_id)
//self.process_message(packet, sender)
//continue
//
//if len(self.known_clients) > 23:
//continue
//
//# new client
//if len(packet) < 4:
//self.blacklist_client(sender)
//continue
//#print(sender)
//
//self.set_client_id(sender)
//
//#(client_first_challenge,) = struct.unpack("i", packet[0:4])
//
//# if client_first_challenge < 0 or client_first_challenge > 99999:
//# self.blacklist_client(sender)
//# continue
//
//#self.send_challenge(client_first_challenge, sender)
//
//#def send_tick(self) :
//    #    packet = struct.pack("i", 4)
//    #    for client in self.known_clients:
//#        current_client = self.known_clients[client]
//#        self.socket.sendto(packet, current_client.peer)
//# def send_challenge(self, client_random_value, client_address) :
//    # challenge_value = random.randrange(0, 99999)
//    # self.challenged_clients[client_address] = (client_random_value, challenge_value)
//    # packet = struct.pack("i", challenge_value)
//    # self.socket.sendto(packet, client_address)
//    # print("ready to challenge", client_address)
//
//    # def check_challenge(self, packet, sender) :
//    # client_random_value, server_random_value = self.challenged_clients[sender]
//    # del self.challenged_clients[sender]
//# if len(packet) != 40:
//    # self.blacklist_client(sender)
//    # return
//    # client_plus_server_value = client_random_value + server_random_value
//    # hash = hashlib.sha256(struct.pack("i", client_plus_server_value)).digest()
//# if hash != packet[0:32]:
//    # self.blacklist_client(sender)
//    # return
//    # self.known_clients[sender] = Player(sender, self.players_counter, packet[32:40])
//    # self.players_counter += 1
//    # print("Welcome client", sender, self.known_clients[sender].name)
//    # self.send_world_status(self.known_clients[sender])
//    def set_client_id(self, sender) :
//    self.known_clients[sender] = Player(sender, self.players_counter)
//    self.players_counter + 1
//    print("Welcome client", sender, self.known_clients[sender].player_id)
//    id = len(self.known_clients)
//    self.known_clients[sender].player_id = id
//    info_to_send = struct.pack("II", id, self.map_index)
//    print(info_to_send)
//    self.socket.sendto(info_to_send, sender)
//    self.send_world_status(self.known_clients[sender])
//    print("i have send this NUMERO:", id)
//
//
//
//    def blacklist_client(self, client_address) :
//    print("blacklisted", client_address)
//    self.blacklisted_clients[client_address] = time.time()
//
//    def send_world_status(self, player) :
//    for peer in self.known_clients :
//        current_player = self.known_clients[peer]
//        if current_player == player :
//            continue
//            # send other player announce to the new user
//            self.socket.sendto(current_player.get_packet_announce(), player.peer)
//            # send player announce to the other player
//            self.socket.sendto(player.get_packet_announce(), current_player.peer)
//
//            #send map info
//            packeted_map_info = struct.pack("<iffiifB", self.actors_to_sync)
//            self.socket.sendto(packeted_map_info, player)
//            print("OK")
//
//
//            if __name__ == "__main__" :
//                server = Server(sys.argv[1], int(sys.argv[2]))
//                server.run()