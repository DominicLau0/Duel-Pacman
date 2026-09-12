#ifndef CLIENT_HH
#define CLIENT_HH

#include <cstdint>
#include <enet/enet.h>
#include <string>
#include <vector>

#include "protocol.hh"

class Client{
    public:
        ~Client();

        bool connect(const char* host, uint16_t port);
        void poll();
        void sendInputPacket(const PlayerInput&);

        const std::vector<PlayerState>& getPlayers() const;

    private:
        uint8_t pacmanId = 0;
        ENetHost* client = nullptr;
        ENetPeer* server = nullptr;

        std::vector<PlayerState> players;
        std::vector<PelletState> pellets;
        std::vector<GhostState> ghosts;

        bool enetInitialized = false;

        void readPacket(const ENetPacket* packet);
};

#endif