#include "Map.h"
#include <iostream>
#include <queue>
#include <tuple>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include "raylib.h"
#include "raymath.h"



void Map::populateBoard(size_t size, int startX, int startY, int endX, int endY) {
	this->size = size;
	board.assign(size, std::vector<Tile>(size, { TileType::GRASSLAND, 1.0f }));
	SetRandomSeed(12345);
	int mountainCount = (int)(size * size * 0.10);
	for (int i = 0; i < mountainCount; i++) {
		int r = GetRandomValue(0, size - 1);
		int c = GetRandomValue(0, size - 1);
		if ((r == startX && c == startY) || (r == endX && c == endY)) {
			continue;
		}
		board[r][c] = { TileType::MOUNTAIN, 20.0f };
	}
	float offset = (float)size / 2.0f;
	this->playerWorldPos = {
		(float)startY * size + offset,
		(float)startX * size + offset
	};
	asteroidWorldPos.clear();
	asteroidVel.clear();
	int asteroidCount = size * size * 0.05;
	for (int i = 0; i < asteroidCount; i++) {
		float posX = (float)GetRandomValue(0, (size * size));
		float posY = (float)GetRandomValue(0, (size * size));
		if (CheckCollisionCircles({ posX, posY }, 20, playerWorldPos, 50)) {
			i--; 
			continue;
		}
		asteroidWorldPos.push_back({ posX, posY });
		float velX = (float)GetRandomValue(-100, 100);
		float velY = (float)GetRandomValue(-100, 100);
		asteroidVel.push_back({ velX, velY });
	}
}



void Map::printBoard(int currentx, int currenty, int endx, int endy) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == currentx && j == currenty) {
				std::cout << "X ";
			}
			else if (i == endx && j == endy) {
				std::cout << "O";
			}
			else
            std::cout << board[i][j].symbol() << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


void Map::printPath(std::vector<std::tuple<int, int>> path, int endx, int endy) {
    for (const auto& val : path) {
        int x = std::get<0>(val);
        int y = std::get<1>(val);
        if (x >= 0 && x < size && y >= 0 && y < size) {
            board[x][y].type = TileType::GRASSLAND;
            board[x][y].cost = 1.0f;
            board[x][y].isPath = true;
        }
    }
    printBoard(endx, endy, endx, endy);
}


using aStarNode = std::tuple<double, int, int>;
std::vector<std::tuple<int, int>> Map::aStarSearchParentStyle(int startx, int starty, int goalx, int goaly,
	bool drawPath, size_t CELL_SIZE) {
	std::set<std::pair<int, int>> blockedTiles;
	for (const auto& pos : asteroidWorldPos) {
		int gridRow = (int)roundf(pos.y / (float)CELL_SIZE);
		int gridCol = (int)roundf(pos.x / (float)CELL_SIZE);
		if (gridRow >= 0 && gridRow < (int)size && gridCol >= 0 && gridCol < (int)size) {
			blockedTiles.insert({ gridRow, gridCol });
		}

	}
	std::priority_queue<aStarNode, std::vector< aStarNode>, std::greater<aStarNode>>  pq;
	printBoard(startx, starty, goalx, goaly);
	pq.push(std::make_tuple(0.0, startx, starty));
	std::map<std::pair<int, int>, int> costSoFar;
	costSoFar[{startx, starty}] = 0;
	std::map< std::pair<int, int>, std::pair<int, int>> parents;
	int directions[8][2] = { {0,1}, {1,0}, {0,-1}, {-1,0}, {1,1}, {1, -1}, {-1, 1}, {-1,-1} };
	while (!pq.empty()) {
		auto [score, x, y] = pq.top();
		pq.pop();
		if (x == goalx && y == goaly) {
			return findPath(parents, startx, starty, goalx, goaly, drawPath, CELL_SIZE);
		}

		for (auto& dir : directions) {
			int newX = x + dir[0];
			int newY = y + dir[1];
			if (newX >= 0 && newX < size && newY >= 0 && newY < size) {
				if (blockedTiles.count({ newX, newY })) {
					continue;
				}
				double dirScore = (dir[0] != 0 && dir[1] != 0) ? std::sqrt(2) : 1;
				double terrainScore = (board[newX][newY].symbol() == '^') ? 20 : 1;
				double asteroidPenalty = (blockedTiles.find({ newX, newY }) != blockedTiles.end()) ? 1000.0 : 1.0;
				double g_score = costSoFar[{x, y}] + (dirScore * terrainScore * asteroidPenalty);
				double h_score = std::sqrt(std::pow(goalx - newX, 2) + std::pow(goaly - newY, 2));
				double newCost = g_score + h_score;
				if (costSoFar.find({ newX, newY }) == costSoFar.end() || g_score < costSoFar[{newX, newY}]) {
					costSoFar[{newX, newY}] = g_score;
					parents[{newX, newY}] = { x, y };
					pq.push(std::make_tuple(newCost, newX, newY));
				}
			}
		}
	}
	return std::vector<std::tuple<int, int>>{};
}

std::vector<std::tuple<int, int>> Map::findPath(std::map<std::pair<int, int>, std::pair<int, int>>& parents,
	int startx, int starty, int endx, int endy, bool drawPath, size_t CELL_SIZE) {
	float offset = static_cast<float>(CELL_SIZE) / 2.0f;
	if (drawPath) {
		Vector2 endCenter = {
			static_cast<float>(endy * CELL_SIZE) + offset,
			static_cast<float>(endx * CELL_SIZE) + offset
		};
		DrawCircleV(endCenter, 10.0f, RED);
	}
	int x = endx;
	int y = endy;
	std::vector<std::tuple<int, int>> path;
	while (!(x == startx && y == starty)) {
		path.push_back(std::make_tuple(x, y));
		auto parent = parents[{x, y}];
		if (drawPath) {
			Vector2 cellCenter = {
				static_cast<float>(y * CELL_SIZE) + offset,
				static_cast<float>(x * CELL_SIZE) + offset
			};
			Vector2 parentCenter = {
				static_cast<float>(parent.second * CELL_SIZE) + offset,
				static_cast<float>(parent.first * CELL_SIZE) + offset
			};
			DrawLineEx(cellCenter, parentCenter, 1.0f, RED);
		}
		x = parent.first;
		y = parent.second;
	}
	path.push_back(std::make_tuple(startx, starty));
	if (drawPath) {
		Vector2 startCenter = {
			static_cast<float>(starty * CELL_SIZE) + offset,
			static_cast<float>(startx * CELL_SIZE) + offset
		};
		DrawCircleV(startCenter, 10.0f, RED);
	}
	std::reverse(path.begin(), path.end());
	printPath(path, endx, endy);
	return path;
}

void Map::update(float dt, int screenW, int screenH, size_t CELL_SIZE) {
	for (size_t i = 0; i < asteroidWorldPos.size(); i++) {
		asteroidWorldPos[i].x += asteroidVel[i].x * dt;
		asteroidWorldPos[i].y += asteroidVel[i].y * dt;
		if (asteroidWorldPos[i].x < 0 || asteroidWorldPos[i].x > screenW) asteroidVel[i].x *= -1;
		if (asteroidWorldPos[i].y < 0 || asteroidWorldPos[i].y > screenH) asteroidVel[i].y *= -1;
	}
	if (targetIndex != -1 && targetIndex < (int)currentPath.size()) {
		auto [tx, ty] = currentPath[targetIndex];
		Vector2 targetPos = {
			ty * (float)CELL_SIZE + (CELL_SIZE / 2.0f),
			tx * (float)CELL_SIZE + (CELL_SIZE / 2.0f)
		};

		float distance = Vector2Distance(playerWorldPos, targetPos);

		if (distance > 1.0f) {
			Vector2 direction = Vector2Normalize(Vector2Subtract(targetPos, playerWorldPos));
			playerWorldPos = Vector2Add(playerWorldPos, Vector2Scale(direction, playerSpeed * dt));
		}
		else {
			targetIndex++;
			if (targetIndex >= (int)currentPath.size()) {
				targetIndex = -1; 
			}
		}
	}
}

void Map::drawGridMap(size_t CELL_SIZE) {
	// Draw Terrain
	for (int i = 0; i < (int)size; i++) {
		for (int j = 0; j < (int)size; j++) {
			Rectangle rect = { (float)j * CELL_SIZE, (float)i * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE };
			Color c = (board[i][j].type == TileType::MOUNTAIN) ? BROWN : LIME;
			DrawRectangleRec(rect, c);
		}
	}

	// Draw A* Path Line
	if (!currentPath.empty()) {
		for (size_t i = 0; i < currentPath.size() - 1; i++) {
			Vector2 p1 = { std::get<1>(currentPath[i]) * (float)CELL_SIZE + CELL_SIZE / 2, std::get<0>(currentPath[i]) * (float)CELL_SIZE + CELL_SIZE / 2 };
			Vector2 p2 = { std::get<1>(currentPath[i + 1]) * (float)CELL_SIZE + CELL_SIZE / 2, std::get<0>(currentPath[i + 1]) * (float)CELL_SIZE + CELL_SIZE / 2 };
			DrawLineEx(p1, p2, 3.0f, RED);
		}
	}
	// Draw Goal
	if (goalX != -1) {
		DrawCircle(goalY * CELL_SIZE + CELL_SIZE / 2, goalX * CELL_SIZE + CELL_SIZE / 2, 5.0f, GOLD);
	}
	// Draw Asteroids
	for (const auto& pos : asteroidWorldPos) {
		DrawCircleV(pos, (float)CELL_SIZE * 0.4f, BLACK);
	}
	// Draw Player
	float pSize = (float)CELL_SIZE * 0.7f;
	DrawRectangleV({ playerWorldPos.x - pSize / 2, playerWorldPos.y - pSize / 2 }, { pSize, pSize }, BLUE);
}
