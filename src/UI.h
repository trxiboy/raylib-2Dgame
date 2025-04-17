// Libraries
#include <raylib.h>
#include <iostream>
#include <string>

#include "window.h"

using std::string;

// UI Class
class UI {
    public:
        UI() {
            heartSprite = LoadTexture("../resources/sprites/heart.png");
            emptyHeartSprite = LoadTexture("../resources/sprites/empty_heart.png");
        }
    
        void Update(int *playerHealth, int *maxHealth, Window *window);
    
    private:
        Texture2D heartSprite;  // Declare the textures as members
        Texture2D emptyHeartSprite;
    };
    