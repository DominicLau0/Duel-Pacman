struct Player
{
    uint32_t id=0;

    ENetPeer* pper = nullptr;

    bool connected = false;

    float x = 0.0f;
    float y = 0.0f;

    float speed = 100.0f;

    PlayerInput input;

    int score = 0;
}

struct Ghost
{

}

struct Pellets
{

}