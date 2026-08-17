# 🚀 Deep Space Miners: Dynamic A* Pathfinding & Physics Visualizer

![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg?style=flat-square&logo=cplusplus)
![Raylib](https://img.shields.io/badge/Render%20Engine-Raylib-red.svg?style=flat-square)
![Build](https://img.shields.io/badge/IDE-Visual%20Studio%202022-purple.svg?style=flat-square&logo=visualstudio)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=flat-square)

**Deep Space Miners** is an interactive, real-time 2D graphical game engine and algorithmic visualizer built in **C++20** using **Raylib**. The project showcases real-time weighted **A* (A-Star) pathfinding**, dynamic dynamic physics collision simulation, procedural map generation, and seamless switching between manual WASD player navigation and AI trajectory takeover.

---

## 🌟 Key Features

### 🗺️ 1. Procedural Grid & Terrain Costing
* **Procedural Mountain Clusters**: Generates 2x2 impassable mountain clusters on a grid matrix using seed-controlled pseudo-random generation.
* **Weighted Graph Search**: Tile terrain affects path costs—`TileType::MOUNTAIN` imposes a heavy cost weight penalty (\(20.0\)) compared to standard grassland (\(1.0\)), encouraging the pathfinder to route around natural terrain obstacles.

### ☄️ 2. Dynamic Asteroid Physics Simulation
* **Vector-Based Kinetic Physics**: Asteroids move continuously with independent floating-point velocity vectors (`asteroidVel`), updating real-time positions based on delta-time (`dt`).
* **Dual-Axis Bounce Collisions**: Asteroids dynamically bounce off screen edges and mountain tile boundaries along X and Y axes independently.
* **Live Safety Snapshotting**: Before executing a path search, the AI engine snapshots live asteroid grid coordinates (`blockedTiles`), preventing the player from routing through active hazard zones.

### 🛸 3. Hybrid Manual & Autonomous AI Navigation
* **Manual WASD Control**: Instant responsive continuous-world vector movement.
* **Collision Detection & AI Takeover**: If manual movement hits a obstacle or when the player left-clicks anywhere on the grid, the AI pathfinding system dynamically calculates the optimal safe route and smoothly interpolates the player avatar along target waypoints.

---

## 🎮 Interactive Controls

| Input | Action |
| :--- | :--- |
| **W / A / S / D** | Manual player movement across the space grid |
| **Left Mouse Click** | Set AI destination goal location anywhere on the map |
| **Automatic AI Mode** | Pathfinding recalculates around dynamic bouncing asteroids and terrain obstacles |

---

## 🔬 Core System Architecture (`Map` & `Raylib`)

```
RaylibAStar/
├── RaylibAStar.cpp    # Game loop, Raylib window setup, input handling, HUD rendering
└── LearningC++/
    ├── Map.h          # Grid definition, Tile struct, Asteroid physics, A* signatures
    └── Map.cpp        # Procedural map generation, physics update loop, A* search algorithm
```

---

## 💻 Engine & Algorithmic Highlights

### 1. Weighted 8-Directional A\* Search with Dynamic Hazard Avoidance (`Map.cpp`)
```cpp
// Snapshot current locations of dynamic moving asteroids
std::set<std::pair<int, int>> blockedTiles;
for (const auto& pos : asteroidWorldPos) {
    int gridRow = (int)roundf(pos.y / (float)CELL_SIZE);
    int gridCol = (int)roundf(pos.x / (float)CELL_SIZE);
    if (gridRow >= 0 && gridRow < (int)size && gridCol >= 0 && gridCol < (int)size) {
        blockedTiles.insert({ gridRow, gridCol });
    }
}

// 8-Way Search with Euclidean Heuristic & Terrain Cost
double dirScore = (dir[0] != 0 && dir[1] != 0) ? std::sqrt(2) : 1.0;
double terrainScore = (board[newX][newY].type == TileType::MOUNTAIN) ? 20.0 : 1.0;

double g_score = costSoFar[{x, y}] + (dirScore * terrainScore);
double h_score = std::sqrt(std::pow(goalx - newX, 2) + std::pow(goaly - newY, 2));
```

### 2. Physics Update & Boundary Bouncing (`Map.cpp`)
```cpp
// X and Y axis bouncing off screen bounds and mountain walls
if (nextX < 0 || nextX > screenW ||
    (nextC >= 0 && nextC < (int)size && board[currR][nextC].type == TileType::MOUNTAIN)) {
    asteroidVel[i].x *= -1;
} else {
    asteroidWorldPos[i].x = nextX;
}
```

---

## 🛠️ Build & Run Instructions

### Prerequisites
* **Compiler**: Visual Studio 2022 (MSVC) with C++20 standard enabled.
* **Graphics Library**: [Raylib](https://www.raylib.com/) (installed via `vcpkg` or statically linked).

### Visual Studio Build Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/PranayBruceChoudhary/LearningC.git
   ```
2. Open `LearningC++.slnx` in Visual Studio 2022.
3. Set **RaylibAStar** as the **Startup Project** (`Right-click RaylibAStar project -> Set as Startup Project`).
4. Select `Debug` or `Release` (`x64`).
5. Press `F5` to build and run the simulation!

---

## 🤝 License
This project is open-source and available under the [MIT License](LICENSE).
