#ifndef SERVER_HH
#define SERVER_HH

#include "/gamestate.hh"

class Server{
    public:
        bool start(uint16_t port);
        void run();

    private:
        EnetHost* host = nullptr;

        void pollNetwork();
        void handlePacket(EnetPeer* peer, EnetPacket* packet);

        void handlePlayerInput(ENetPeer* peer, const PlayerInput& input);

        void sendGameState();

        GameState gamestate;
}
#endif