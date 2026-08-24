#include <iostream>
#include "protocol.hh"

#include "serialization.hh"
#include "deserialization.hh"

#include "ClientNetwork.hh"

#include <enet/enet.h>

static int CLIENT_ID = -1;

ClientNetwork::ClientNetwork(){

}

ClientNetwork::~ClientNetwork(){
    if(server != nullptr){
        enet_peer_disconnect(server, 0);
        server = nullptr;
    }

    if(client != nullptr){
        enet_host_destroy(client);
        client = nullptr;
    }

    if(enetInitialized){
        atexit (enet_deinitialize);
        enetInitialized = false;
    }
}

bool ClientNetwork::connect(const std::string& host, uint16_t port){
    // Initialize ENet and create an ENet client
    if(enetInitialized == false){
        if (enet_initialize() != 0){
            fprintf(stderr, "An error occurred while initializing ENet.\n");
            return false;
        }
        enetInitialized = true;
    }
    client = enet_host_create(nullptr, 1, 2, 0, 0);

    if(client == NULL){
        fprintf (stderr, 
                "An error occurred while trying to create an ENet client host.\n");
        return false;
    }

    // Resolve server address
    ENetAddress address;

    enet_address_set_host(&address, host);
    address.port = port;
    
    // Connect to server
    server = enet_host_connect(client, &address, 2, 0);

    if (server == NULL){
        fprintf (stderr, 
                "No available peers for initiating an ENet connection.\n");
        exit (EXIT_FAILURE);
    }

    /* Wait up to 5 seconds for the connection attempt to succeed. */
    ENetEvent event;
    if (enet_host_service (client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT){
        puts ("Connection to some.server.net:3000 succeeded.");

        return true;
    }
    else{
        enet_peer_reset (peer);
        puts ("Connection to some.server.net:3000 failed.");
        server = nullptr;

        return false;
    }
}

void ClientNetwork::poll(){
    if(client == nullptr){
        return;
    }

    //Retrieve packet from server
    ENetEvent event;

    while (enet_host_service(client, &event, 0) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                puts("Connected.\n")
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                // Deserialize the data and extract message type
                handlePacket(event.packet);
                enet_packet_destroy(event.packet);
                
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                puts("Disconnection succeeded.");

                if(event.peer == server){
                    server = nullptr;
                }

                break;
            
            default:
                break;
        }
    }
}

void ClientNetwork::sendInputPacket(const PlayerInput& input){
    if(server == nullptr){
        return;
    }

    Serialization serializer;

    // Packet message type
    serializer.writeUInt8(MessageType::PlayerInput);

    // Player Input
    serializer.writeBool(player.up);
    serializer.writeBool(player.down);
    serializer.writeBool(player.left);
    serializer.writeBool(player.right);

    // Get serialization data
    const std::vector<uint8_t>& data = serialier.getSerializedData();
    
    enet_uint32 flag = reliable ? ENET_PACKET_FLAG_RELIABLE : ENET_PACKET_FLAG_UNSEQUENCED;

    EnetPacket* packet = enet_packet_create(data.data(), data.size(), flag);

    if(packet == nullptr){
        return;
    }

    enet_peer_send(server, 0, packet);
    enet_host_flush(client);
}

void ClientNetwork::readPacket(const ENetPacket* packet){
    if(packet == nullptr){
        return;
    }

    Deserialization deserializer(packet->data, packet->dataLength);

    // Read message type
    int32_t messageType = deserializer.readInt32();

    MessageType type = static_cast<MessageType>(messageType);

    switch(type){
        case MessageType::PlayerState:
            PlayerState playerState;

            playerState.id = deserializer.readInt32();
            playerState.x = deserializer.readFloat();
            playerState.y = deserializer.readFloat();
            playerState.score = deserializer.readInt32();

            bool found = false;

            for(PlayerState& player : players){
                if(player.id == playerState.id){
                    player = playerState;
                    found = true;
                    break;
                }
            }

            if(!found){
                players.push_back(state);
            }

        default:
            puts(stderr, "Received unknown message type: %d\n", messageType);

            break;
    }
}

const std::vector<PlayerState>& ClientNetwork::getPlayers() const{
    return players;
}