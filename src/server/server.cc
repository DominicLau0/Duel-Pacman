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

void Server::readPacket(const ENetPacket* packet, uint8_t playerId, std::vector<Pacman>& pacmans){
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
            PlayerInput player;

            player.dx = deserializer.readInt8();
            player.dy = deserializer.readInt8();

            for(auto& pacman: pacmans){
                if(playerId == pacman.id){
                    pacman.direction.x = player.dx;
                    pacman.direction.y = player.dy;
                }
            }

            break;

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

                //Assign playerId to enet peer.
                uint8_t playerId = nextPlayerId++;

                event.peer->data = (void*)(uintptr_t)playerId;

                for(auto& pacman: pacmans){
                    if(pacman.id == 0){
                        pacman.id == playerId;
                        break;
                    }
                }

                // Return the id of the pacman to the client.
                PlayerJoined joinedMessage{playerId};
                playerJoinedPacket(joinedMessage, event.peer);

                // Broadcast to all pacmans, so that we can start the game.

                break;

            case ENET_EVENT_TYPE_RECEIVE:
                // Output client packet
                printf("A packet of length %lu containing %s was received from %s on channel %u.\n",
                        event.packet->dataLength,
                        event.packet->data,
                        event.peer->data,
                        event.channelID);

                int8_t playerId = (uint8_t)(uintptr_t)event.peer->data;

                // Process packet
                readPacket(event.packet, playerId, pacmans);
                
                enet_packet_destroy(event.packet);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                printf("%s Disconnected.\n", event.peer->data);
                event.peer->data = nullptr;

                break;
            
            case ENET_EVENT_TYPE_NONE:
                break;
        }
    }
}

void Server::playerJoinedPacket(const PlayerJoined& playerJoined, ENetPeer* enetPeer){
    Serialization serializer;

    serializer.writeUInt8(static_cast<uint8_t>(MessageType::PlayerJoined));
    
    serializer.writeUInt8(playerJoined.id);

    const std::vector<uint8_t>& data = serializer.getSerializedData();

    ENetPacket* packet = enet_packet_create(data.data(), data.size(), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(enetPeer, 0, packet);
}

void Server::sendPackets(std::vector<Pacman>& pacmans, std::vector<Pellet>& pellets, std::vector<Ghost>& ghosts){
    Serialization serializer;

    // Serialize pacman data
    serializer.writeUInt32(pacmans.size());

    for(auto& pacman: pacmans){
        serializer.writeUInt32(pacman.id);
        serializer.writeFloat(pacman.coordinate.x);
        serializer.writeFloat(pacman.coordinate.y);
        serializer.writeInt32(pacman.score);
    }

    // Serialize pellet data
    serializer.writeUInt32(pellets.size());

    for(auto& pellet: pellets){
        serializer.writeFloat(pellet.coordinate.x);
        serializer.writeFloat(pellet.coordinate.y);
        serializer.writeBool(pellet.eaten);
    }

    // Serialize ghost data
    serializer.writeUInt32(ghosts.size());

    for(auto& ghost: ghosts){
        serializer.writeFloat(ghost.coordinate.x);
        serializer.writeFloat(ghost.coordinate.y);
    }

    const std::vector<uint8_t>& data = serializer.getSerializedData();

    ENetPacket* packet = enet_packet_create(data.data(), data.size(), 0);
    enet_host_broadcast(server, 0, packet);
}