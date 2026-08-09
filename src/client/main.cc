#include <iostream>
#include "enet/enet.h"

static int CLIENT_ID = -1;

void SendPacket(EnetPeer* server, const char*data){
    EnetPacket* packet = enet_packet_create(data. strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
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

    while (enet_host_service(client, &event, 3000) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy(event.packet);
            break;
            case ENET_EVENT_TYPE_DISCONNECT:
                puts("Disconnection succeeded.");
            disconnected = true;
            break;
      }
  }

    return 0;
}