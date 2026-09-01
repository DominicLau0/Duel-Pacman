#ifndef CLIENTNETWORK_HH
#define CLIENTNETWORK_HH

#include <enet/enet.h>
#include <string>

class ClientNetwork{
    public:
        ClientNetwork();
        ~ClientNetwork();

        bool connect(const std::string& host, uint16_t port);
        void poll();
        void sendInputPacket(const void* data, size_t size, bool reliable = true);


        const std::vector<PlayerState>& getPlayers() const;

    private:
        ENetHost* client = nullptr;
        ENetPeer* server = nullptr;

        std::vector<PlayerState> players;
        std::vector<PelletState> pellets;
        std::vector<GhostState> ghosts;

        bool enetInitialized = false;

        void readPacket(const ENetPacket* packet);
}

#endif