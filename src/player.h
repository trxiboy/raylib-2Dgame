// Libraries:
#include <raylib.h>
#include <iostream>
#include <map>

using std::string;


// Player Class:
class Player{
    public:
        // Player Values:
        float moveSpeed = 7.0f;

        int playerHealth;
        int playerMaxHealth;


        // Player States:
        char playerState = 'i';
        string moveState = "idle";


        //==================
        Player(Vector2 startingPos, int health) {
            playerPos = startingPos;
            playerHealth = health;
            playerMaxHealth = health;

            MapSprites();

            playerSpriteSheet = LoadTexture("../resources/sprites/player.png");
            spriteRect = {0, 0, 16.0f, 16.0f};
        }
        //==================

        
        Vector2 GETPosition();
        void SETPosition(Window window, Rectangle playableArea, Vector2 newPostion);

        void MapSprites();
        void IterateSprite(Window window, float deltaTime);

    private:
        Vector2 playerPos{ .0f, .0f };

        //==================
        // Sprite Values:
        float spriteTimer = 0.0f;
        int ANIM_SPEED = 1.0f;

        // Sprite Sheet:
        Vector2 spriteGrid{3, 5};
        Vector2 currentGrid{1, 1};
        /*
            [1], [2], [3] | 1
            [1], [2], [3] | 2
            [1], [2], [3] | 3
            [1], [2], [3] | 4
        */

        Texture2D playerSpriteSheet;
        Rectangle spriteRect;

        // Sprite Map:
        std::map<std::string, int> spriteMap;
        //==================
};