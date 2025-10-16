@ -1,112 +0,0 @@
#include "raylib.h"
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

// Game states
enum GameState { START, PLAYING, GAME_OVER };

// Load jokes from file
std::vector<std::string> LoadJokes(const char* filename) {
    std::vector<std::string> jokes;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            jokes.push_back(line);
        }
    }

    return jokes;
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Raylib Micro-Game: Joke Collector");
    SetTargetFPS(60);

    // Load jokes
    std::vector<std::string> jokes = LoadJokes("jokes.txt");
    std::string currentJoke = "No jokes found!";
    if (!jokes.empty()) {
        srand(time(0));
        currentJoke = jokes[rand() % jokes.size()];
    }

    GameState state = START;

    // Player
    Rectangle player = { 100, 100, 40, 40 };
    float speed = 4.0f;

    // Goal
    Rectangle goal = { 600, 400, 30, 30 };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (state) {
            case START:
                DrawText("Welcome to Joke Collector!", 220, 100, 30, DARKBLUE);
                DrawText(currentJoke.c_str(), 100, 200, 20, GRAY);
                DrawText("Press [ENTER] to start", 260, 400, 20, BLACK);

                if (IsKeyPressed(KEY_ENTER)) {
                    state = PLAYING;
                }
                break;

            case PLAYING:
                // Movement
                if (IsKeyDown(KEY_RIGHT)) player.x += speed;
                if (IsKeyDown(KEY_LEFT)) player.x -= speed;
                if (IsKeyDown(KEY_DOWN)) player.y += speed;
                if (IsKeyDown(KEY_UP)) player.y -= speed;

                // Boundaries
                if (player.x < 0) player.x = 0;
                if (player.y < 0) player.y = 0;
                if (player.x + player.width > screenWidth) player.x = screenWidth - player.width;
                if (player.y + player.height > screenHeight) player.y = screenHeight - player.height;

                // Draw player and goal
                DrawRectangleRec(goal, GOLD);
                DrawRectangleRec(player, BLUE);
                DrawText("Collect the star!", 10, 10, 20, DARKGRAY);

                // Check collision
                if (CheckCollisionRecs(player, goal)) {
                    state = GAME_OVER;
                }
                break;

            case GAME_OVER:
                DrawText("You collected the star!", 240, 200, 30, GREEN);
                DrawText("Press [R] to restart", 270, 400, 20, DARKGRAY);

                if (IsKeyPressed(KEY_R)) {
                    // Reset
                    player.x = 100;
                    player.y = 100;
                    goal.x = 600;
                    goal.y = 400;
                    if (!jokes.empty()) {
                        currentJoke = jokes[rand() % jokes.size()];
                    }
                    state = START;
                }
                break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}