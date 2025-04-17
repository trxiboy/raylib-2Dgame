// Libraries:
#include <raylib.h>

#include "calculations.h"

#include "window.h"

#include "UI.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <cmath>

using std::string;


// Window Properties:
Vector2 windowSize = {1280, 720};
string windowTitle = "Dodge.exe [WIP]";


// GameObject Vectors:
std::vector<Enemy> gameEnemies = {};
std::vector<Bullet> gameBullets = {};


// Game Functions:
void UnloadAssets() { // [UNFINISHED]
    
}


// Game Main Loop:
int main() {
    Window window(windowSize, windowTitle); // Set up window

    //==================
    // Playable Area:
    int currentColumn;
    int currentRow;

    const int gridSize = 72;
    const int columnSize = 12;

    int mapGrid[gridSize] = { // 12x6
        0, 0, 0, 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0,  // [1]
        0, 0, 0, 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0,  // [2]
        0, 0, 0, 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0,  // [3]
        0, 0, 0, 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0,  // [4]
        0, 0, 0, 0, 0 ,0 ,0 ,0 ,0, 0, 0, 0,  // [5]
        1, 1, 1, 1, 1 ,1 ,1 ,1 ,1, 1, 1, 1,  // [6]
    };
    Vector2 gridStartPos{100, 100};

    Rectangle playableArea{
        gridStartPos.x,
        gridStartPos.y,
        (columnSize-1) * 16.0f * window.worldScale + (columnSize * 1.0f * window.worldScale/3),
        5 * 16.0f * window.worldScale - (columnSize * 1.0f * window.worldScale/3),
    };

    Texture2D grassTopSprite = LoadTexture("../resources/sprites/grass_top.png");
    Texture2D grassFrontSprite = LoadTexture("../resources/sprites/grass_front.png");
    //==================


    // User Interface:
    UI userInterface;
    

    // Player Setup:
    Vector2 startingPosition{ windowSize.x/2+window.defaultPixel*window.worldScale/2, windowSize.y/2+window.defaultPixel*window.worldScale/2 };
    Player player(startingPosition, 3);


    // Enem-(y)|(ies):
    Enemy enemy(Vector2({ 100, 100 }), 2);
    gameEnemies.push_back(enemy);


    // Load Bullet Class:
    Bullet newBullet(enemy.GETPosition(), player.GETPosition());
    gameBullets.push_back(newBullet);

    // Game Loop Variables:
    float deltaTime;

    Vector2 playerPos;
    Vector2 moveVector;


    while (!WindowShouldClose()) {
        deltaTime = GetFrameTime();
        
        //==================
        // Draw Map:
        currentColumn = 0;
        currentRow = 0;

        //DrawRectangle(playableArea.x, playableArea.y, playableArea.width, playableArea.height, WHITE);
        
        for (int i=0; i<gridSize; i++) {
            Vector2 grassPosition{
                gridStartPos.x + (currentColumn * 16.0f * window.worldScale) - (1.0f * window.worldScale * currentColumn),
                gridStartPos.y + static_cast<float>(currentRow * (16.0f * window.worldScale) - (1.0f * window.worldScale * currentRow))
            };     
            
            if (mapGrid[i] == 0) {
                DrawTextureEx(grassTopSprite, grassPosition, 0.0f, window.worldScale, WHITE);
            } else if (mapGrid[i] == 1) {
                DrawTextureEx(grassFrontSprite, grassPosition, 0.0f, window.worldScale, WHITE);
            }

            currentColumn++;
            if (currentColumn > columnSize-1) {
                currentColumn=0;
                currentRow++;
            }
        }
        //==================

        //==================
        // Player Movement:
        playerPos = player.GETPosition();
        moveVector = { .0f, .0f };

        player.playerState = 'i';
        player.moveState = "idle";

        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) { player.playerState = 'm'; moveVector.y -= playerPos.y; player.moveState = "up"; }
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) { player.playerState = 'm'; moveVector.y += playerPos.y; player.moveState = "down"; }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) { player.playerState = 'm'; moveVector.x -= playerPos.y;player.moveState = "left";}
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) { player.playerState = 'm'; moveVector.x += playerPos.y; player.moveState = "right";}

        Vector2 normalizedMove = NormalizeVector(moveVector);
        Vector2 scaledMove = { normalizedMove.x * player.moveSpeed, normalizedMove.y * player.moveSpeed };
        
        player.SETPosition(&window, &playableArea, { playerPos.x + scaledMove.x, playerPos.y + scaledMove.y });
        //==================


        BeginDrawing();
        //==================
            window.Clear();

            for (size_t i=0; i<gameEnemies.size(); i++) {
                gameEnemies[i].IterateSprite(&window, &deltaTime);

                if (!gameEnemies[i].canMove) {
                    gameEnemies[i].enemyMoveTimer += deltaTime;
                    if (gameEnemies[i].canFire) {
                        gameEnemies[i].canFire = false;

                        //newPos = 
                        Bullet newBullet(gameEnemies[i].GETPosition(), player.GETPosition());
                        gameBullets.push_back(newBullet);
                    }
                }

                if (gameEnemies[i].enemyMoveTimer > gameEnemies[i].enemyMoveInterval) gameEnemies[i].enemyMoveTimer = 0.0f, gameEnemies[i].canMove = true;
                if (gameEnemies[i].canMove) gameEnemies[i].MoveTo(&deltaTime, gameEnemies[i].GETPosition(), GetRectRandomPosition(playableArea), &window, &playableArea);
            }
            
            for (int i = gameBullets.size() - 1; i >= 0; i--) {
                bool reachedEnd = gameBullets[i].Fire(&window);
                if (reachedEnd) {
                    gameBullets.erase(gameBullets.begin() + i);
                }
            }

            player.IterateSprite(&window, &deltaTime);
            userInterface.Update(&player.playerHealth, &player.playerMaxHealth, &window);
            
        //==================
        EndDrawing();
    }

    UnloadAssets();
    CloseWindow();
}