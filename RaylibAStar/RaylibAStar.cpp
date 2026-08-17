#include "raylib.h" 
#include "raymath.h" 
#include "../LearningC++/Map.h"

const int windowWidth = 1000;
const int windowHeight = 1000;
const size_t CELL_SIZE = 20;

int main() {
    InitWindow(windowWidth, windowHeight, "Deep Space Miners - Big Obstacles & Bouncing");
    SetTargetFPS(60);

    Map map;
    size_t gridSize = windowHeight / CELL_SIZE;

    // Initialize map with player at 1,1
    map.populateBoard(gridSize, 1, 1, gridSize - 2, gridSize - 2);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // 1. Mouse Click sets the Safe Goal for the AI takeover
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 m = GetMousePosition();
            map.setGoal((int)(m.y / CELL_SIZE), (int)(m.x / CELL_SIZE));
        }

        // 2. Logic Update: Bouncing meteorites, WASD, and AI Collision Avoidance
        map.update(dt, windowWidth, windowHeight, CELL_SIZE);

        // 3. Render
        BeginDrawing();
        ClearBackground(BLACK);

        map.drawGridMap(CELL_SIZE);

        DrawRectangle(5, 5, 450, 60, Fade(BLACK, 0.5f));
        DrawText("WASD to move. Mouse to set AI Destination.", 10, 10, 20, RAYWHITE);
        DrawText("Meteorites now bounce off screen and mountains!", 10, 35, 20, GREEN);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}