#include <vector>
#include <map>
#include <tuple>

class Map
{
private:
 size_t size = 0;
 std::vector<std::vector<char>> board;

public:
	void populateBoard(size_t size, std::vector<std::tuple<int, int>> mountains);
	void populateBoard(size_t size, std::vector<std::tuple<int, int>> mountains, int startX, int startY, int endX, int endY);
	void printBoard(int currentx, int currenty, int endx, int endy);
	std::vector<std::tuple<int, int>> aStarSearch(int startx, int starty, int goalx, int goaly);
	std::vector<std::tuple<int, int>> aStarSearchParentStyle(int startx, int starty, int goalx, int goaly, bool drawPath, size_t CELL_SIZE);
	void printPath(std::vector<std::tuple<int, int>> path, int endx, int endy);
	std::vector<std::tuple<int, int>> findPath(std::map< std::pair<int, int>, std::pair<int, int>>& parents, 
		int startx, int starty, int endx, int endy, bool drawPath, size_t CELL_SIZE);
	std::vector<std::vector<char>> getBoard() { return board; }
	void drawGridMap(size_t CELL_SIZE);
	void drawMap(int obsticaleCount, int windowWidth, int windowHeight);
};

