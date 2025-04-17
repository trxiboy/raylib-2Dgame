// Libraries:
#include <raylib.h>

#include <algorithm>
#include <iostream>
#include <map>

#include "window.h"
#include "player.h"

using std::string;


// Player Class Functions:
void Player::SETPosition(Window* window, Rectangle* playableArea, Vector2 newPos) {
    newPos.x = std::max(playableArea->x, std::min(newPos.x, playableArea->x + playableArea->width - window->defaultPixel * window->worldScale));
    newPos.y = std::max(playableArea->y, std::min(newPos.y, playableArea->y + playableArea->height - window->defaultPixel * window->worldScale));

    playerPos = newPos;
}


Vector2 Player::GETPosition() {
    return playerPos;
}


// Sprite Functions:
//==================
void Player::MapSprites() {
    spriteMap["up"] = 1;
    spriteMap["down"] = 2;
    spriteMap["left"] = 3;
    spriteMap["right"] = 4;
    spriteMap["idle"] = 5;
}

void Player::IterateSprite(Window* window, float* deltaTime) {
    spriteTimer += *deltaTime;

    // Change Grid:
    currentGrid.y = spriteMap[moveState];
    if (playerState == 'i' && spriteTimer > .6f * ANIM_SPEED) {
        spriteTimer = .0f;
        currentGrid.x++;
    } else if (playerState == 'm' && spriteTimer > 0.1 * ANIM_SPEED) {
        spriteTimer = .0f;
        currentGrid.x++;
    }
    if (currentGrid.x >= spriteGrid.x) { currentGrid.x = 0; }
    //-----------------

    // Grid Position:
    spriteRect.x = (currentGrid.x-1) * 16.0f;
    spriteRect.y = (currentGrid.y-1) * 16.0f;
    //-----------------

    // Draw Sprite:
    Rectangle playerRect = { playerPos.x, playerPos.y, window->defaultPixel*window->worldScale, window->defaultPixel*window->worldScale };
    DrawTexturePro(playerSpriteSheet, spriteRect, playerRect, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);
    //-----------------
}

//==================