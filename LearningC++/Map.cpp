#include "Map.h"
#include <iostream>
#include <queue>
#include <tuple>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include "raylib.h"

void Map::populateBoard(size_t s, std::vector<std::tuple<int, int>> mountains) {
	this->size = s;
	board.assign(size, std::vector<char>(size, '~'));
	for (auto& mountain : mountains) {
		int x = std::get<0>(mountain);
		int y = std::get<1>(mountain);
		if (x >= 0 && x < size && y >= 0 && y < size) {
			board[x][y] = '^';
		}
	}
}

void Map::populateBoard(size_t s, std::vector<std::tuple<int, int>> mountains, int startX, int startY, int endX, int endY) {
	this->size = s;
	int mountainCount = size * size * 0.10;
	board.assign(size, std::vector<char>(size, '~'));
	SetRandomSeed(12345);
	for (int i = 0; i < mountainCount; i++) {
		int x = GetRandomValue(0, size - 1);
		int y = GetRandomValue(0, size - 1);
		if ((x == startX && y == startY) || (x == endX && y == endY)) {
			continue;
		}
		board[x][y] = '^';
	}/*
	for (auto& mountain : mountains) {
		int x = std::get<0>(mountain);
		int y = std::get<1>(mountain);
		if (x >= 0 && x < size && y >= 0 && y < size) {
			board[x][y] = '^';
		}
	}*/
	board[startX][startY] = 'X';
	board[endX][endY] = 'O';
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
			std::cout << board[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

using AStarNode = std::tuple<double, int, int, std::vector<std::tuple<int, int>>>;

std::vector<std::tuple<int, int>> Map::aStarSearch(int startx, int starty, int goalx, int goaly) {
	printBoard(startx, starty, goalx, goaly);
	std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<AStarNode>> pq;
	pq.push(std::make_tuple(0, startx, starty, std::vector<std::tuple<int, int>>{{0, 0}}));
	std::map<std::pair<int, int>, int> costSoFar;
	costSoFar[{startx, starty}] = 0;
	std::set<std::pair<int, int>> visited;
	int directions[8][2] = { {0,1}, {1,0}, {0,-1}, {-1,0}, {1,1}, {1, -1}, {-1, 1}, {-1,-1} };
	while (!pq.empty()){
		auto [score, x, y, path] = pq.top();
		pq.pop();
		if (visited.find({ x, y }) != visited.end()) {
			continue;
		}
		visited.insert(std::make_pair(x, y));
		if (x == goalx && y == goaly) {
			printPath(path, goalx, goaly);
			return path;
		}
		for (auto& dir : directions) {
			int newX = x + dir[0];
			int newY = y + dir[1];
			if (newX >= 0 && newX < size && newY >= 0 && newY < size) {
				int dirScore = (dir[0] != 0 && dir[1] != 0) ? static_cast<int>(std::sqrt(2)) : 1;
				int terrainScore = (board[newX][newY] == '^') ? 20 : 1;
				int g_score = costSoFar[{x, y}] + (dirScore * terrainScore);
				int h_score = std::sqrt(std::pow(goalx - newX, 2) + std::pow(goaly - newY, 2));
				int newCost = g_score + h_score;
				if (costSoFar.find({ newX, newY }) == costSoFar.end() || newCost < costSoFar[{newX, newY}]) {
					costSoFar[{newX, newY}] = newCost;
					std::vector<std::tuple<int, int>> newPath = path;
					newPath.push_back(std::make_tuple(newX, newY));
					pq.push(std::make_tuple(newCost, newX, newY, newPath));
				}
			}
		}
	}
	return std::vector<std::tuple<int, int>>{};
}

void Map::printPath(std::vector<std::tuple<int, int>> path, int endx, int endy) {
	for (std::tuple val : path) {
		board[std::get<0>(val)][std::get<1>(val)] = '*';
		//std::cout << std::endl;
		//printBoard(x, y, endx, endy);
		//std::cout << std::endl;*/
	}
	printBoard(endx, endy, endx, endy);
}

using aStarNode = std::tuple<double, int, int>;
std::vector<std::tuple<int, int>> Map::aStarSearchParentStyle(int startx, int starty, int goalx, int goaly, 
	bool drawPath, size_t CELL_SIZE) {
	std::priority_queue<aStarNode, std::vector< aStarNode>, std::greater<aStarNode>>  pq;
	printBoard(startx, starty, goalx, goaly);
	pq.push(std::make_tuple(0.0, startx, starty));
	std::map<std::pair<int, int>, int> costSoFar; // represents g_score
	costSoFar[{startx, starty}] = 0; // cost to reach start is 0
	std::map< std::pair<int, int>, std::pair<int, int>> parents;
	int directions[8][2] = { {0,1}, {1,0}, {0,-1}, {-1,0}, {1,1}, {1, -1}, {-1, 1}, {-1,-1}};
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
				double dirScore = (dir[0] != 0 && dir[1] != 0) ? std::sqrt(2) : 1;
				double terrainScore = (board[newX][newY] == '^') ? 20 : 1;
				double g_score = costSoFar[{x, y}] + (dirScore * terrainScore);
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

void Map::drawGridMap(size_t CELL_SIZE) {
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			Rectangle cellRect = { j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE };
			Color tileColor;
			std::vector<std::vector<char>> map_data = board;
			char tileType = map_data[i][j];
			if (tileType == '^') {
				tileColor = BLACK;      // Mountain
			}
			else if (tileType == '~') {
				tileColor = LIME;           // Grassland
			}
			else if (tileType == 'X') {
				tileColor = BLUE;           // Start Destination
			}
			else if (tileType == 'O') {
				tileColor = RED;            // End Destination
			}
			else {
				tileColor = DARKGREEN;      // Edge Case
			}
			DrawRectangleRec(cellRect, tileColor);
			// DrawRectangleLinesEx(cellRect, 1, Fade(BLACK, 0.2f));
		}
	}
}

void Map::drawMap(int obsticaleCount, int windowWidth, int windowHeight) {
	SetRandomSeed(12345);
	int count = 0;
	while (count < obsticaleCount) {
		int rectWidth = GetRandomValue(40, 150);
		int rectHeight = GetRandomValue(40, 150);
		int posX = GetRandomValue(0, windowWidth - rectWidth);
		int posY = GetRandomValue(0, windowHeight - rectHeight);
		DrawRectangle(posX, posY, rectWidth, rectHeight, BLUE);
		DrawRectangleLines(posX, posY, rectWidth, rectHeight, SKYBLUE);
	}
}



