#include "raylib.h" 
#include "raymath.h" 
#include "../LearningC++/Map.h"
#include <tuple>
#include <vector>
#include <iostream>

const int windowWidth = 1000;
const int windowHeight = 1000;
const size_t CELL_SIZE = 20;
int main()
{
    InitWindow(windowWidth, windowHeight, "Deep Space Miners - A* Pathfinding");
    SetTargetFPS(60);

    Map map;
    size_t gridSize = windowHeight / CELL_SIZE;
    int startX = 1, startY = 1;
    int endX = (int)gridSize - 2, endY = (int)gridSize - 2;
    map.populateBoard(gridSize, startX, startY, endX, endY);
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 m = GetMousePosition();
            int gX = (int)(m.y / CELL_SIZE);
            int gY = (int)(m.x / CELL_SIZE);
            int pX = (int)(map.getPlayerWorldPos().y / CELL_SIZE);
            int pY = (int)(map.getPlayerWorldPos().x / CELL_SIZE);
            if (gX >= 0 && gX < gridSize && gY >= 0 && gY < gridSize) {
                map.setGoal(gX, gY);
                auto newPath = map.aStarSearchParentStyle(pX, pY, gX, gY, false, CELL_SIZE);
                map.setCurrentPath(newPath);
            }
        }
        map.update(dt, windowWidth, windowHeight, CELL_SIZE);
        BeginDrawing();
        ClearBackground(BLACK);
        map.drawGridMap(CELL_SIZE);
        EndDrawing();
    }


    CloseWindow();
    return 0;
}
