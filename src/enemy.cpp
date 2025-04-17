// Libraries:
#include <raylib.h>

#include <algorithm>
#include <iostream>
#include <cmath>
#include <map>

#include "calculations.h"
#include "window.h"

#include "enemy.h"


// Enemy Class Functions:
Vector2 Enemy::GETPosition() {
    return enemyPos;
}


void Enemy::MoveTo(float* deltaTime, const Vector2 start, const Vector2 end, Window* window, Rectangle* playableArea) {
    moveToTimer += *deltaTime;

    float verticalDiff = startPos.y - endPos.y, horizontalDiff = startPos.x - endPos.x;
    if (std::abs(verticalDiff) >= 1.5 * std::abs(horizontalDiff)) {
        if (verticalDiff > 0) {
            moveState = "up";
        } else {
            moveState = "down";
        }
    } else {
        if (horizontalDiff > 0) {
            moveState = "left";
        } else {
            moveState = "right";
        }
    }

    if (!isMoving) {
        startPos = start;
        endPos = end;
        moveToFactor = 0.0f;
        moveToTimer = 0.0f;
        isMoving = true;
        enemyState = 'm';
    }
    
    moveToFactor += 1.0f * moveSpeed / Distance(startPos, endPos);
    if (moveToFactor >= 1.0f) {
        moveToFactor = 1.0f;
        canMove = false;
        isMoving = false;
        canFire = true;
        enemyState = 'i';
        moveState = "idle";
    }

    enemyPos = LerpPosition(startPos, endPos, moveToFactor);
    enemyPos.x = std::max(playableArea->x, std::min(enemyPos.x, playableArea->x + playableArea->width - window->defaultPixel * window->worldScale));
    enemyPos.y = std::max(playableArea->y, std::min(enemyPos.y, playableArea->y + playableArea->height - window->defaultPixel * window->worldScale));
}


// Sprite Functions:
//==================
void Enemy::MapSprites() {
    spriteMap["up"] = 1;
    spriteMap["down"] = 2;
    spriteMap["left"] = 3;
    spriteMap["right"] = 4;
    spriteMap["idle"] = 5;
}

void Enemy::IterateSprite(Window* window, float* deltaTime) {
    spriteTimer += *deltaTime;

    // Change Grid:
    currentGrid.y = spriteMap[moveState];
    if (enemyState == 'i' && spriteTimer > .6f * ANIM_SPEED) {
        spriteTimer = .0f;
        currentGrid.x++;
    } else if (enemyState == 'm' && spriteTimer > 0.1 * ANIM_SPEED) {
        spriteTimer = .0f;
        currentGrid.x++;
    }
    if (currentGrid.x >= spriteGrid.x) { currentGrid.x = 0; }
    //-----------------

    // Grid Position:
    spriteRect.x = (currentGrid.x-1) * 16.0f;
    spriteRect.y = (currentGrid.y-1) * 16.0f;
    //-----------------

    // Draw Enemy:
    Rectangle enemyRect = { enemyPos.x, enemyPos.y, window->defaultPixel*window->worldScale, window->defaultPixel*window->worldScale };
    DrawTexturePro(enemySpriteSheet, spriteRect, enemyRect, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);
    //-----------------

    // Draw Gun:
    if (moveState == "left") {
        gunRect = { enemyPos.x, enemyPos.y+window->defaultPixel*window->worldScale/3, window->defaultPixel*window->worldScale/2, window->defaultPixel*window->worldScale/2 };
        gunSourceRect.width = -16.0f;
        DrawTexturePro(gunSprite, gunSourceRect, gunRect, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);
    } else if (moveState == "up" || moveState == "down") {
        ;
    } else {
        gunRect = { enemyPos.x+window->defaultPixel*window->worldScale/2, enemyPos.y+window->defaultPixel*window->worldScale/3, window->defaultPixel*window->worldScale/2, window->defaultPixel*window->worldScale/2 };
        gunSourceRect.width = 16.0f;
        DrawTexturePro(gunSprite, gunSourceRect, gunRect, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);
    }
    //-----------------
}
//==================