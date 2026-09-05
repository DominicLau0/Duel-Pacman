#include <iostream>

#include "protocol.hh"
#include "server.hh"

constexpr uint16_t SERVER_PORT = 7777;
constexpr size_t MAX_PLAYERS = 32;

Server::Server(){
    if (enet_initialize() != 0){
        fprintf(stderr, "An error occurred while initializing ENet.\n");
    }
}

Server::~Server(){
    stop();
    enet_deinitialize();
}

bool Server::start(uint16_t port, size_t maxClients, size_t channels){
    if(server != nullptr){
        fprintf(stderr, "Server is already running.\n");
        return false;
    }

    //Create an ENet server
    ENetAddress address;

    address.host = ENET_HOST_ANY;
    address.port = port;

    server = enet_host_create(&address, maxClients, channels, 0, 0);

    if(server == nullptr){
        fprintf (stderr, 
            "An error occurred while trying to create an ENet client host.\n");
        return false;
    }
    std::cout << "Server listening on port " << port << std::endl;

    return true;
}

void Server::stop(){
    if(server){
        enet_host_destroy(server);
        server = nullptr;
    }
}

void Server::readPacket(const ENetPacket* packet, std::vector<Pacman>&){
    if(packet == nullptr){
        return;
    }

    Deserialization deserializer(packet->data, packet->dataLength);

    // Read message type
    int32_t messageType = deserializer.readInt32();

    MessageType type = static_cast<MessageType>(messageType);

    switch(type){
        case MessageType::PlayerInput:
            // Compute player
            uint32_t playerCount = deserializer.readUInt32();

            for(uint32_t i = 0; i < playerCount; i++){
                PlayerInput player;

                player.dx = deserializer.readInt8();
                player.dy = deserializer.readInt8();

                pacmans.push_back(player);
            }

        default:
            fprintf(stderr, "Received unknown message type: %d\n", messageType);

            break;
    }
}

void Server::receivePackets(std::vector<Pacman>& pacmans){
    if(server == nullptr){
        return;
    }

    //Retrieve packet from server
    ENetEvent event;

    while(enet_host_service(server, &event, 0) > 0){
        switch(event.type){
            case ENET_EVENT_TYPE_CONNECT:
                // Output client details
                printf("A new client connected from %x:%u.\n",  event.peer->address.host, event.peer->address.port);
                event.peer->data = (void*)(uintptr_t)playerId;

                break;

            case ENET_EVENT_TYPE_RECEIVE:
                // Output client packet
                printf("A packet of length %lu containing %s was received from %s on channel %u.\n",
                        event.packet->dataLength,
                        event.packet->data,
                        event.peer->data,
                        event.channelID);

                // Process packet
                readPacket(event.packet, pacmans);
                
                enet_packet_destroy(event.packet);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                printf("%s Disconnected.\n", event.peer->data);
                event.peer->data = NULL;

                break;
            
            case ENET_EVENT_TYPE_NONE:
                break;
        }
    }
}

void Server::sendPackets(EnetPeer* peer, const char*data){
    EnetPacket* packet = enet_packet_create(data.data(), strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
}