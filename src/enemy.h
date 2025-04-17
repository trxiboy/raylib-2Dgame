// Libraries:
#include <raylib.h>
#include <iostream>
#include <map>

using std::string;


// Enemy Class:
class Enemy{
    public:
        // Movement Values:
        float moveSpeed = 2.0f;

        float enemyMoveTimer = 0.0f;
        float enemyMoveInterval = 2.0f;
        bool canMove = false;
        bool isMoving = false;
        bool canFire = false;

        float moveToTimer = 0.0f;
        float moveToFactor = 0.0f;


        Enemy(Vector2 startingPos, int health) {
            enemyPos = startingPos;
            enemyHealth = health;

            MapSprites();

            enemySpriteSheet = LoadTexture("../resources/sprites/enemy.png");
            gunSprite = LoadTexture("../resources/sprites/gun.png");
            spriteRect = {0, 0, 16.0f, 16.0f};
        }

        Vector2 GETPosition();
        void MoveTo(float *deltaTime, const Vector2 startPos, const Vector2 endPos, Window *window, Rectangle *playableArea);

        void MapSprites();
        void IterateSprite(Window *window, float *deltaTime);
        
    private:
        // Enemy Values:
        Vector2 enemyPos{ 0.0f, 0.0f };

        Vector2 startPos;
        Vector2 endPos;

        int enemyHealth;


        // Enemy States:
        char enemyState = 'i';
        string moveState = "idle";

        
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
        
        Texture2D enemySpriteSheet;
        Rectangle spriteRect;

        Texture2D gunSprite;
        Rectangle gunRect;
        Rectangle gunSourceRect{ 0.0f, 0.0f, 16.0f, 16.0f };

        // Sprite Map:
        std::map<std::string, int> spriteMap;
        //==================
};