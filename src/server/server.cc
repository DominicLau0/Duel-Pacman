#include <iostream>
#include "protocol.hh"

#include <enet/enet.h>

constexpr uint16_t SERVER_PORT = 7777;
constexpr size_t MAX_PLAYERS = 32;

constexpr double TICK_RATE = 16.0;
constexpr double TICK_DT = 1.0 / TICK_RATE;

constexpr double SNAPSHOT_RATE = 20.0;
constexpr double SNAPSHOT_DT = 1.0 / SNAPSHOT_RATE;

void SendPacket(EnetPeer* peer, const char*data){
    EnetPacket* packet = enet_packet_create(data. strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
}

void ParseData(EnetHost* server, int id, char* data){

}

void Server::handlePacket(){
    if(type == MessageType::PlayerInput){
        PlayerInput input;

        int32_t playerId = getPlayerId(peer);
        world.processInput(playerId, input);
    }
}
 
int main(){
    //Initialize ENet
    if (enet_initialize () != 0)
    {
        fprintf (stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }

    //Create an ENet server
    ENetAddress address;
    ENetHost * server;

    address.host = ENET_HOST_ANY;
    address.port = 3000;

    server = enet_host_create(&address, 32, 2, 0, 0);

    if(server == NULL){
        fprintf (stderr, 
            "An error occurred while trying to create an ENet client host.\n");
        exit (EXIT_FAILURE);
    }

    //Managing ENet host
    ENetEvent event;
    while(enet_host_service(client, &event, 0) > 0){
        switch(event.type){
            case ENET_EVENT_TYPE_CONNECT:
                printf("A new client connected from %x:%u.\n",  event.peer->address.host, event.peer->address.port);
                event.peer->data = "Client information";

                break;

            case ENET_EVENT_TYPE_RECIEVE:
                printf("A packet of length %lu containing %s was received from %s on channel %u.\n",
                        event.packet->dataLength,
                        event.packet->data,
                        event.peer->data,
                        event.channelID);

                enet_packet_destroy(event.packet);

                // Extract message type from packet

                // Parse message from packet
                MessageType type = protocol.readMessageType();

                switch(type){
                    case MessageType::PlayerState:
                        bool 
                        break;
                    case MessageType::PlayerJoined:
                        break;
                    case MessageType::PlayerLeft:
                        break;
                }
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                printf("%s Disconnected.\n", event.peer->data);
                event.peer->data = NULL;

                break;
            
            case ENET_EVENT_DISCONNECT_TIMEOUT:
                printf("%s Disconnected due to timeout.\n", event.peer->data);
                event.peer->data = NULL;

                break;

            case ENET_EVENT_TYPE_NONE:
                break;
                
        }
    }

    //Close server
    enet_host_destroy(client);
    atexit (enet_deinitialize);

    return 0;
}
