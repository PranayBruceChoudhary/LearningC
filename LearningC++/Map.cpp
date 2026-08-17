#include "Map.h"
#include <iostream>
#include <queue>
#include <tuple>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
#include "raylib.h"
#include "raymath.h"

void Map::populateBoard(size_t size, int startX, int startY, int endX, int endY) {
    this->size = size;
    board.assign(size, std::vector<Tile>(size, { TileType::GRASSLAND, 1.0f }));
    SetRandomSeed(12345);

    // 1. BIGGER & FEWER OBSTACLES: Generate 2x2 clusters
    int clusterCount = (int)(size * size * 0.02); // 2% chance to start a cluster
    for (int i = 0; i < clusterCount; i++) {
        int r = GetRandomValue(0, (int)size - 2);
        int c = GetRandomValue(0, (int)size - 2);

        // Fill 2x2 area
        for (int dr = 0; dr < 2; dr++) {
            for (int dc = 0; dc < 2; dc++) {
                int currR = r + dr;
                int currC = c + dc;
                // Don't block start or end points
                if ((currR == startX && currC == startY) || (currR == endX && currC == endY)) continue;
                board[currR][currC] = { TileType::MOUNTAIN, 20.0f };
            }
        }
    }

    // 2. Set Player Position
    float offset = 20.0f / 2.0f; // Assuming CELL_SIZE 20
    this->playerWorldPos = { (float)startY * 20 + offset, (float)startX * 20 + offset };

    // 3. Initialize Asteroids
    asteroidWorldPos.clear();
    asteroidVel.clear();
    int asteroidCount = (int)(size * size * 0.02); // Slightly fewer asteroids for clarity
    for (int i = 0; i < asteroidCount; i++) {
        float posX = (float)GetRandomValue(0, (size * 20));
        float posY = (float)GetRandomValue(0, (size * 20));

        int gridR = (int)(posY / 20);
        int gridC = (int)(posX / 20);

        // Ensure asteroids don't spawn in mountains or on player
        if (gridR >= size || gridC >= size || board[gridR][gridC].type == TileType::MOUNTAIN ||
            CheckCollisionCircles({ posX, posY }, 10, playerWorldPos, 50)) {
            i--; continue;
        }

        asteroidWorldPos.push_back({ posX, posY });
        asteroidVel.push_back({ (float)GetRandomValue(-150, 150), (float)GetRandomValue(-150, 150) });
    }
}

void Map::update(float dt, int screenW, int screenH, size_t CELL_SIZE) {
    // --- 1. ASTEROID BOUNCING LOGIC ---
    for (size_t i = 0; i < asteroidWorldPos.size(); i++) {
        // Calculate potential new positions
        float nextX = asteroidWorldPos[i].x + asteroidVel[i].x * dt;
        float nextY = asteroidWorldPos[i].y + asteroidVel[i].y * dt;

        // Current Grid Row/Col
        int currR = (int)(asteroidWorldPos[i].y / CELL_SIZE);
        int currC = (int)(asteroidWorldPos[i].x / CELL_SIZE);

        // Next Grid Row/Col
        int nextR = (int)(nextY / CELL_SIZE);
        int nextC = (int)(nextX / CELL_SIZE);

        // X-axis Bounce (Wall or Mountain)
        if (nextX < 0 || nextX > screenW ||
            (nextC >= 0 && nextC < (int)size && board[currR][nextC].type == TileType::MOUNTAIN)) {
            asteroidVel[i].x *= -1;
        }
        else {
            asteroidWorldPos[i].x = nextX;
        }

        // Y-axis Bounce (Wall or Mountain)
        if (nextY < 0 || nextY > screenH ||
            (nextR >= 0 && nextR < (int)size && board[nextR][currC].type == TileType::MOUNTAIN)) {
            asteroidVel[i].y *= -1;
        }
        else {
            asteroidWorldPos[i].y = nextY;
        }
    }

    // --- 2. PLAYER CONTROL LOGIC ---
    if (targetIndex != -1) { // Override Mode
        auto [tx, ty] = currentPath[targetIndex];
        Vector2 targetPos = { ty * (float)CELL_SIZE + (CELL_SIZE / 2.0f), tx * (float)CELL_SIZE + (CELL_SIZE / 2.0f) };
        float distance = Vector2Distance(playerWorldPos, targetPos);
        if (distance > 1.5f) {
            Vector2 direction = Vector2Normalize(Vector2Subtract(targetPos, playerWorldPos));
            playerWorldPos = Vector2Add(playerWorldPos, Vector2Scale(direction, playerSpeed * dt));
        }
        else {
            targetIndex++;
            if (targetIndex >= (int)currentPath.size()) { targetIndex = -1; currentPath.clear(); }
        }
    }
    else { // Manual Mode
        Vector2 move = { 0, 0 };
        if (IsKeyDown(KEY_W)) move.y -= 1;
        if (IsKeyDown(KEY_S)) move.y += 1;
        if (IsKeyDown(KEY_A)) move.x -= 1;
        if (IsKeyDown(KEY_D)) move.x += 1;

        if (Vector2Length(move) > 0) {
            move = Vector2Scale(Vector2Normalize(move), playerSpeed * dt);
            Vector2 nextP = Vector2Add(playerWorldPos, move);
            int nR = (int)roundf(nextP.y / (float)CELL_SIZE);
            int nC = (int)roundf(nextP.x / (float)CELL_SIZE);

            if (isTileBlocked(nR, nC, CELL_SIZE)) {
                if (goalX != -1) {
                    int cR = (int)roundf(playerWorldPos.y / (float)CELL_SIZE);
                    int cC = (int)roundf(playerWorldPos.x / (float)CELL_SIZE);
                    currentPath = aStarSearchParentStyle(cR, cC, goalX, goalY, false, CELL_SIZE);
                    if (!currentPath.empty()) targetIndex = 0;
                }
            }
            else {
                playerWorldPos = nextP;
            }
        }
    }
}

bool Map::isTileBlocked(int r, int c, size_t CELL_SIZE) {
    if (r < 0 || r >= (int)size || c < 0 || c >= (int)size) return true;
    if (board[r][c].type == TileType::MOUNTAIN) return true;
    for (const auto& pos : asteroidWorldPos) {
        if (r == (int)roundf(pos.y / CELL_SIZE) && c == (int)roundf(pos.x / CELL_SIZE)) return true;
    }
    return false;
}

void Map::drawGridMap(size_t CELL_SIZE) {
    for (int i = 0; i < (int)size; i++) {
        for (int j = 0; j < (int)size; j++) {
            Color c = (board[i][j].type == TileType::MOUNTAIN) ? DARKBROWN : LIME;
            DrawRectangle(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE, c);
        }
    }
    if (targetIndex != -1) {
        for (size_t i = targetIndex; i < currentPath.size() - 1; i++) {
            Vector2 p1 = { std::get<1>(currentPath[i]) * (float)CELL_SIZE + CELL_SIZE / 2, std::get<0>(currentPath[i]) * (float)CELL_SIZE + CELL_SIZE / 2 };
            Vector2 p2 = { std::get<1>(currentPath[i + 1]) * (float)CELL_SIZE + CELL_SIZE / 2, std::get<0>(currentPath[i + 1]) * (float)CELL_SIZE + CELL_SIZE / 2 };
            DrawLineEx(p1, p2, 2.0f, RED);
        }
    }
    if (goalX != -1) DrawCircle(goalY * CELL_SIZE + CELL_SIZE / 2, goalX * CELL_SIZE + CELL_SIZE / 2, 6, GOLD);
    for (const auto& pos : asteroidWorldPos) DrawCircleV(pos, (float)CELL_SIZE * 0.4f, BLACK);
    DrawRectangleV({ playerWorldPos.x - 7, playerWorldPos.y - 7 }, { 14, 14 }, BLUE);
}
using aStarNode = std::tuple<double, int, int>;

std::vector<std::tuple<int, int>> Map::aStarSearchParentStyle(int startx, int starty, int goalx, int goaly,
    bool drawPath, size_t CELL_SIZE) {

    // 1. Snapshot dynamic obstacles (Asteroids)
    std::set<std::pair<int, int>> blockedTiles;
    for (const auto& pos : asteroidWorldPos) {
        int gridRow = (int)roundf(pos.y / (float)CELL_SIZE);
        int gridCol = (int)roundf(pos.x / (float)CELL_SIZE);
        if (gridRow >= 0 && gridRow < (int)size && gridCol >= 0 && gridCol < (int)size) {
            blockedTiles.insert({ gridRow, gridCol });
        }
    }

    std::priority_queue<aStarNode, std::vector< aStarNode>, std::greater<aStarNode>>  pq;
    pq.push(std::make_tuple(0.0, startx, starty));

    std::map<std::pair<int, int>, float> costSoFar;
    costSoFar[{startx, starty}] = 0.0f;
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
                // Skip if blocked by asteroid
                if (blockedTiles.count({ newX, newY })) continue;

                double dirScore = (dir[0] != 0 && dir[1] != 0) ? std::sqrt(2) : 1.0;
                double terrainScore = (board[newX][newY].type == TileType::MOUNTAIN) ? 20.0 : 1.0;

                double g_score = costSoFar[{x, y}] + (dirScore * terrainScore);
                double h_score = std::sqrt(std::pow(goalx - newX, 2) + std::pow(goaly - newY, 2));
                double newCost = g_score + h_score;

                if (costSoFar.find({ newX, newY }) == costSoFar.end() || g_score < costSoFar[{newX, newY}]) {
                    costSoFar[{newX, newY}] = (float)g_score;
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

    int x = endx;
    int y = endy;
    std::vector<std::tuple<int, int>> path;

    while (!(x == startx && y == starty)) {
        path.push_back(std::make_tuple(x, y));
        auto it = parents.find({ x, y });
        if (it == parents.end()) break; // Safety break
        x = it->second.first;
        y = it->second.second;
    }
    path.push_back(std::make_tuple(startx, starty));
    std::reverse(path.begin(), path.end());
    return path;
}