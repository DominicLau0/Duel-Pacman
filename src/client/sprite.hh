#ifndef SPRITE_HH
#define SPRITE_HH

class Sprite
{
    public:
        Sprite();
        ~Sprite();
        void draw();
        void update();
        
    private:
        int texture;
        int position;
        int speed;
        int direction;
};

#endif