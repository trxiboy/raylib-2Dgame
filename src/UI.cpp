// Libraries
#include <raylib.h>
#include <iostream>
#include <string>
#include <cmath>

#include "window.h"
#include "UI.h"


// UI Class Functions:
void UI::Update(int *playerHealth, int *maxHealth, Window *window) {
    for (int i=0; i<*maxHealth; i++) {
        Vector2 heartPosition({ i*window->worldScale+10*window->worldScale*i, 0 });
        
        if (i+1 > *playerHealth) {
            DrawTextureEx(emptyHeartSprite, heartPosition, 0.0f, window->worldScale/1.25f, WHITE);
        } else {
            DrawTextureEx(heartSprite, heartPosition, 0.0f, window->worldScale/1.25f, WHITE);
        }
    }
}