#include "raylib.h" 
#include "raymath.h" 
#include "../LearningC++/Map.h"
#include <tuple>
#include <vector>
#include <iostream>

const int windowWidth = 1280;
const int windowHeight = 1280;
const size_t CELL_SIZE = 10;

int main()
{
	Map map;
	size_t gridSize = windowHeight/CELL_SIZE;
	std::vector<std::tuple<int, int>> mountains = { {0,1}, {1,1}, {2,3}, {3,2}, { 3, 4 }, {4,4}, { 6,4 }, { 5,5 }, { 6,7 }, { 1,9 }, { 6,3 }, { 8,8 }, { 9,8 }, { 7,9 }};
	int startX = 0, startY = 0;
	int endX = gridSize - 1, endY = gridSize - 1;
	map.populateBoard(gridSize, mountains, startX, startY, endX, endY);
	InitWindow(windowWidth, windowHeight, "Deep Space Miners");
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		map.drawGridMap(CELL_SIZE);
		map.aStarSearchParentStyle(startX, startY, endX, endY, true, CELL_SIZE);
		DrawText("Grid Map", 10, 10, 20, WHITE);
		EndDrawing();
	}
	CloseWindow();
    std::cout << "Hello World!\n";
}
