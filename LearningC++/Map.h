#include <vector>
#include <map>
#include <tuple>
#include "raylib.h"
#include "raymath.h"

class Map
{
private:
enum class TileType { GRASSLAND, MOUNTAIN, START, END };
struct Tile {
    TileType type;
    float cost;
    bool isPath = false;
    char symbol() const {
        switch (type) {
        case TileType::GRASSLAND:
            return '~';
        case TileType::MOUNTAIN:
            return '^';
        case TileType::START:
            return 'X';
        case TileType::END:
            return 'O';
        default:
            return '?';
        }
    }                
};
std::vector<std::tuple<int, int>> currentPath;
int targetIndex = -1;
int goalX = -1, goalY = -1;
float playerSpeed = 150.0f;
 size_t size = 0;
 std::vector<std::vector<Tile>> board;
 Vector2 playerWorldPos;               
 std::vector<Vector2> asteroidWorldPos;
 std::vector<Vector2> asteroidVel;
 bool isOverridden = false;
public:
    bool isTileBlocked(int r, int c, size_t CELL_SIZE);
	void populateBoard(size_t size, int startX, int startY, int endX, int endY);
	void update(float dt, int screenW, int screenH, size_t CELL_SIZE);
	void drawGridMap(size_t CELL_SIZE);
	std::vector<std::tuple<int, int>> aStarSearchParentStyle(int startx, int starty, int goalx, int goaly, bool drawPath, size_t CELL_SIZE);
	std::vector<std::tuple<int, int>> findPath(std::map<std::pair<int, int>, std::pair<int, int>>& parents, int startx, int starty, int endx, int endy, bool drawPath, size_t CELL_SIZE);
	void setGoal(int gx, int gy) { goalX = gx; goalY = gy; }
	Vector2 getPlayerWorldPos() { return playerWorldPos; }
	void setCurrentPath(std::vector<std::tuple<int, int>> path) { currentPath = path; targetIndex = 0; }
	void printBoard(int currentx, int currenty, int endx, int endy);
	void printPath(std::vector<std::tuple<int, int>> path, int endx, int endy);
};

