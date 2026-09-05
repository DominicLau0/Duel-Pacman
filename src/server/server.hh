#ifndef SERVER_HH
#define SERVER_HH

#include <enet/enet.h>

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

        bool sendPackets();
        void receivePackets(std::vector<Pacman>&);
        void readPacket(const ENetPacket*, std::vector<Pacman>&);

    private:
        ENetHost* host = nullptr;
        ENetHost* server = nullptr;
};
#endif