#include <iostream>
#include "protocol.hh"

#include "serialization.hh"
#include "deserialization.hh"

#include <enet/enet.h>

static int CLIENT_ID = -1;

void writePlayerInput(Serialization& serializer, const PlayerState& player){
    serializer.writeInt32(player.id);
    serializer.writeFloat(player.x);
    serializer.writeFloat(player.y);
    serializer.writeInt32(player.health);
}

PlayerState readPlayerState(Deserializer& deserializer){
    PlayerState player;

    player.id = deserializer.readInt32();
    player.x = deserializer.readFloat();
    player.y = deserializer.readFloat();

    return player;
}

void SendPacket(EnetPeer* server, const char*data, bool reliable){
    if(reliable == true){
        EnetPacket* packet = enet_packet_create(data. strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
    }else{
        EnetPacket* packet = enet_packet_create(data. strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
    }
    enet_peer_send(server, 0, packet);
}

void ParseData(EnetHost* server, int id, char* data){

}

int main(){
    //Initialize ENet
    if (enet_initialize () != 0)
    {
        fprintf (stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }

    // Create an ENet Client
    ENetHost* client;

    client = enet_host_create(NULL, 1, 2, 0, 0);

    if(client == NULL){
        fprintf (stderr, 
                "An error occurred while trying to create an ENet client host.\n");
        exit (EXIT_FAILURE);
    }

    //Connect to an ENet host
    ENetAddress address;
    ENetEvent event;
    ENetPeer *peer;

    enet_address_set_host(&address, "127.0.0.1");
    address.port = 3000;
    
    peer = enet_host_connect(client, &address, 2, 0);

    if (peer == NULL){
        fprintf (stderr, 
                "No available peers for initiating an ENet connection.\n");
        exit (EXIT_FAILURE);
    }

    /* Wait up to 5 seconds for the connection attempt to succeed. */
    if (enet_host_service (client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT){
        puts ("Connection to some.server.net:3000 succeeded.");
    }
    else{
        enet_peer_reset (peer);
        puts ("Connection to some.server.net:3000 failed.");
    }

    while (enet_host_service(client, &event, 0) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                // Deserialize the data and extract message type
                Deserialization deserialize(event.packet->data, event.packet->dataLength);

                MessageType type = ;

                if(type == MessageType::PlayerState){
                    PlayerState player;

                }else if(){

                }

                enet_packet_destroy(event.packet);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                puts("Disconnection succeeded.");
                disconnected = true;
                break;
        }
    }

    // Close client
    enet_host_destroy(client);
    atexit (enet_deinitialize);

    return 0;
}