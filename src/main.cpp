
#include "raylib.h"
#include <stdio.h>
#include "raymath.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
Font text;
const int screenWidth = 800;
const int screenHeight = 450;
typedef struct Coin{
  Vector2 pos;
  Color color = WHITE;
  Texture2D texture = LoadTexture("res/gfx/coin.png");
  bool isCollected = false;
  Rectangle coincol;
} Coin;
typedef struct floatingPlatform{
  Vector2 pos;
  Color color = WHITE;
  Texture2D texture = LoadTexture("res/gfx/platform.png");
  Rectangle platform = {pos.x, pos.y, 128, 16};
  bool isTouching = false;
}floatingPlatform;
void DrawEndMessage(void){
    DrawTextEx(text, "You won!", {screenWidth/2, screenHeight/2}, 24, 5, GREEN);
}
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "hdfsyu - KeyMaster");

    // TODO: Load resources / Initialize variables at this point
    Vector2 playerPos = {0.0f,350.0f};
    Vector2 playerSize = {64,64};
    float velocityY = 15.0f;
    bool isJumping = false;
    const float gravity = 0.5f;
    const float groundLevel = 350.0f;
    bool isGrounded = true;
    Coin coin;
    floatingPlatform platform1;
    floatingPlatform platform2;
    floatingPlatform platform3;
    coin.pos = {120.0f,368.0f};
    platform1.pos = {120.0f,268.0f};
    platform2.pos = {510.0f, 268.0f};
    platform3.pos = {330.0f, 150.0f};
    Vector2 doorPos = {380.0f, 86.0f};
    Rectangle player = {playerPos.x, playerPos.y, 12, 24};
    Rectangle door = {doorPos.x, doorPos.y, 32, 64};
    coin.coincol = {coin.pos.x, coin.pos.y, 32, 32};
    Image playerImg = LoadImage("res/gfx/player.png");
    ImageResize(&playerImg, 32, 64);
    Texture2D playerTex = LoadTextureFromImage(playerImg);
    int score = 0;
    bool showEndMsg = false;
    text = LoadFont("res/fnt/text.ttf");
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update variables / Implement example logic at this point
        //----------------------------------------------------------------------------------
        if(IsKeyDown(KEY_RIGHT)){
          playerPos.x += 3.5f;
        }
        if(IsKeyDown(KEY_LEFT)){
          playerPos.x -= 3.5f;
        }
        if(IsKeyDown(KEY_SPACE) && !isJumping && isGrounded){
          isJumping = true;
          velocityY = 12.0f; // Add upward force
        }
        if(isJumping){
          playerPos.y -= velocityY;
          velocityY -= gravity;
          if(playerPos.y >= groundLevel){
              playerPos.y = groundLevel;
              isJumping = false;
          }
        }
        // Check if player is colliding with platform1
        if (CheckCollisionRecs(player, platform1.platform)) {
            isGrounded = true;
            float xOverlap = fminf(playerPos.x + playerSize.x, platform1.platform.x + 128) - fmaxf(playerPos.x, platform1.platform.x);
            float yOverlap = fminf(playerPos.y + playerSize.y, platform1.platform.y + 16) - fmaxf(playerPos.y, platform1.platform.y);

            if (xOverlap > 0 && yOverlap > 0) { // Check for overlap
                if (xOverlap < yOverlap) { // Resolve overlap horizontally
                    if (playerPos.x < platform1.platform.x) { // Player is to the left of the platform
                        playerPos.x -= xOverlap; // Move player to the left by the amount of overlap
                    }
                    else { // Player is to the right of the platform
                        playerPos.x += xOverlap; // Move player to the right by the amount of overlap
                    }
                } 
                else { // Resolve overlap vertically
                    if (playerPos.y < platform1.platform.y) { // Player is above the platform
                        playerPos.y -= yOverlap; // Move player up by the amount of overlap
                        isJumping = false; // Set isJumping to false since the player has landed on a platform
                    }
                    else { // Player is below the platform
                        playerPos.y += yOverlap; // Move player down by the amount of overlap
                    }
                }

                // Update player rectangle with new position
                player.x = playerPos.x;
                player.y = playerPos.y;
            }
        }else if(!CheckCollisionRecs(player, platform1.platform) && playerPos.y == 350.0f){
          isJumping = false;
        }
        if (CheckCollisionRecs(player, platform2.platform)) {
            isGrounded = true;
            float xOverlap = fminf(playerPos.x + playerSize.x, platform2.platform.x + 128) - fmaxf(playerPos.x, platform2.platform.x);
            float yOverlap = fminf(playerPos.y + playerSize.y, platform2.platform.y + 16) - fmaxf(playerPos.y, platform2.platform.y);

            if (xOverlap > 0 && yOverlap > 0) { // Check for overlap
                if (xOverlap < yOverlap) { // Resolve overlap horizontally
                    if (playerPos.x < platform2.platform.x) { // Player is to the left of the platform
                        playerPos.x -= xOverlap; // Move player to the left by the amount of overlap
                    }
                    else { // Player is to the right of the platform
                        playerPos.x += xOverlap; // Move player to the right by the amount of overlap
                    }
                } 
                else { // Resolve overlap vertically
                    if (playerPos.y < platform2.platform.y) { // Player is above the platform
                        playerPos.y -= yOverlap; // Move player up by the amount of overlap
                        isJumping = false; // Set isJumping to false since the player has landed on a platform
                    }
                    else { // Player is below the platform
                        playerPos.y += yOverlap; // Move player down by the amount of overlap
                    }
                }

                // Update player rectangle with new position
                player.x = playerPos.x;
                player.y = playerPos.y;
            }
        }else if(!CheckCollisionRecs(player, platform2.platform) && playerPos.y == 350.0f){
          isJumping = false;
        }
        if (CheckCollisionRecs(player, platform3.platform)) {
            isGrounded = true;
            float xOverlap = fminf(playerPos.x + playerSize.x, platform3.platform.x + 128) - fmaxf(playerPos.x, platform3.platform.x);
            float yOverlap = fminf(playerPos.y + playerSize.y, platform3.platform.y + 16) - fmaxf(playerPos.y, platform3.platform.y);

            if (xOverlap > 0 && yOverlap > 0) { // Check for overlap
                if (xOverlap < yOverlap) { // Resolve overlap horizontally
                    if (playerPos.x < platform3.platform.x) { // Player is to the left of the platform
                        playerPos.x -= xOverlap; // Move player to the left by the amount of overlap
                    }
                    else { // Player is to the right of the platform
                        playerPos.x += xOverlap; // Move player to the right by the amount of overlap
                    }
                } 
                else { // Resolve overlap vertically
                    if (playerPos.y < platform3.platform.y) { // Player is above the platform
                        playerPos.y -= yOverlap; // Move player up by the amount of overlap
                        isJumping = false; // Set isJumping to false since the player has landed on a platform
                    }
                    else { // Player is below the platform
                        playerPos.y += yOverlap; // Move player down by the amount of overlap
                    }
                }

                // Update player rectangle with new position
                player.x = playerPos.x;
                player.y = playerPos.y;
            }
        }else if(!CheckCollisionRecs(player, platform3.platform) && playerPos.y == 350.0f){
          isJumping = false;
        }
        if(CheckCollisionRecs(player, coin.coincol)){
          score++;
          coin.coincol = {0,0,0,0};
          coin.texture = LoadTexture("");
        }
        if(CheckCollisionRecs(player, door)){
            showEndMsg = true;
        }
        // Update platform1 rectangle with new position
        platform1.platform = { platform1.pos.x, platform1.pos.y, 128, 16 };
        platform2.platform = { platform2.pos.x, platform2.pos.y, 128, 16 };
        platform3.platform = { platform3.pos.x, platform3.pos.y, 128, 16 };
        player = {playerPos.x, playerPos.y, 64, 64};

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GRAY);
            if(!showEndMsg){
                DrawRectangle(0,414,800,450,BLACK);
                DrawTextureV(playerTex, playerPos, WHITE);
                DrawTextureV(coin.texture, coin.pos, coin.color);
                DrawTextureV(platform1.texture, platform1.pos, platform1.color);
                DrawTextureV(platform2.texture, platform2.pos, platform2.color);
                DrawTextureV(platform3.texture, platform3.pos, platform3.color);
                DrawRectangle(380,86,32,64,GREEN);
                DrawText(TextFormat("Coins: %i", score), 10, 10, 20, YELLOW);
            }
            if(showEndMsg){
                ClearBackground(BLACK);
                DrawEndMessage();
            }
            //DrawRectangleRec(coin.coincol, YELLOW);
            //DrawRectangleRec(player, BLUE);
            //DrawRectangleRec(platform1.platform, PURPLE);
            // TODO: Draw everything that requires to be drawn at this point:
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded resources at this point

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    UnloadImage(playerImg);
    UnloadTexture(playerTex);
    UnloadTexture(platform1.texture);
    UnloadTexture(platform2.texture);
    UnloadTexture(platform3.texture);
    return 0;
}
