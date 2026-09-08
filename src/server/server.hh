#ifndef SERVER_HH
#define SERVER_HH

#include <enet/enet.h>

#include "serialization.hh"
#include "deserialization.hh"

#include "game.hh"
#include <vector>

class Server{
    public:
        Server();
        ~Server();

        bool start(uint16_t port, size_t maxClients = 32, size_t channels = 2);
        void update();
        void stop();

        void sendPackets(std::vector<Pacman>&, std::vector<Pellet>&, std::vector<Ghost>&);
        void receivePackets(std::vector<Pacman>&);
        void readPacket(const ENetPacket*, uint8_t playerId, std::vector<Pacman>&);

        void playerJoinedPacket(const PlayerJoined& playerJoined, ENetPeer*);

    private:
        ENetHost* host = nullptr;
        ENetHost* server = nullptr;

        uint8_t nextPlayerId = 1;
};
#endif