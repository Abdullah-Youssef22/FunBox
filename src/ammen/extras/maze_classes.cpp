//#include "../../../include/maze.h"
//#include <iostream>
//#include <fstream>
//#include <algorithm>
//#include <queue>
//#include <unordered_map>
//#include <climits>
//#include <boost/functional/hash.hpp>
//
//typedef std::pair<int, int> pCoord;
//typedef std::unordered_map<
//    pCoord,
//    std::vector<std::pair<pCoord, int>>,
//    boost::hash<pCoord>
//> AdjList;
//
//typedef std::priority_queue<
//    std::pair<int, pCoord>,
//    std::vector<std::pair<int, pCoord>>,
//    std::greater<>
//> priorityQueue;
//
//typedef std::unordered_map<
//    pCoord, int,
//    boost::hash<pCoord>
//> distanceMap;
//
//static int manhattanDistance(int x1, int y1, int x2, int y2) {
//    return abs(x2 - x1) + abs(y2 - y1);
//}
//
//static bool in_bounds(int r, int c, int rows, int cols) {
//    return r >= 0 && r < rows && c >= 0 && c < cols;
//}
//
//static int safe_get(const Matrix& m, int r, int c, int fallback = -1) {
//    if (r >= 0 && r < (int)m.size() && c >= 0 && c < (int)m[0].size()) 
//        return m[r][c];
//    return fallback;
//}
//
//MazeSolver::MazeSolver() 
//    : totalRows(0), totalCols(0), startPos({-1, -1}), goalPos({-1, -1}), mazeLoaded(false) {}
//
//bool MazeSolver::loadMaze(const std::string& path) {
//    mazePath = path;
//    std::ifstream maze(mazePath);
//    
//    if (!maze.is_open()) {
//        std::cerr << "Error: Could not open maze file: " << path << std::endl;
//        return false;
//    }
//
//    std::string line;
//    totalRows = 0;
//    totalCols = 0;
//    
//    while (std::getline(maze, line)) {
//        totalRows++;
//        if ((int)line.size() > totalCols) {
//            totalCols = (int)line.size();
//        }
//    }
//    
//    maze.close();
//    
//    if (totalRows == 0 || totalCols == 0) {
//        std::cerr << "Error: Empty maze file" << std::endl;
//        return false;
//    }
//
//    maze.open(mazePath);
//    int row = 0;
//    while (std::getline(maze, line)) {
//        for (int col = 0; col < (int)line.size(); col++) {
//            if (line[col] == 'S') {
//                startPos = {col, row};
//            } else if (line[col] == 'G') {
//                goalPos = {col, row};
//            }
//        }
//        row++;
//    }
//    maze.close();
//
//    if (startPos.first == -1 || goalPos.first == -1) {
//        std::cerr << "Error: Maze missing Start or Goal" << std::endl;
//        return false;
//    }
//
//    mazeLoaded = true;
//    return true;
//}
//
//Matrix MazeSolver::getMazeMatrix() {
//    if (!mazeLoaded) {
//        std::cerr << "Error: No maze loaded" << std::endl;
//        return Matrix();
//    }
//
//    std::ifstream maze(mazePath);
//    Matrix converted(totalRows, std::vector<int>(totalCols, 0));
//    std::string line;
//
//    for (int i = 0; i < totalRows; i++) {
//        if (!std::getline(maze, line)) {
//            line = std::string(totalCols, ' ');
//        }
//        if ((int)line.size() < totalCols) {
//            line.resize(totalCols, ' ');
//        }
//        
//        for (int j = 0; j < totalCols; j++) {
//            char ch = line[j];
//            if (ch == ' ') converted[i][j] = 0;
//            else if (ch == 'o') converted[i][j] = 1;
//            else if (ch == '-') converted[i][j] = 2;
//            else if (ch == '|') converted[i][j] = 3;
//            else if (ch == 'G') converted[i][j] = 4;
//            else if (ch == 'S') converted[i][j] = 5;
//            else converted[i][j] = 0;
//        }
//    }
//    maze.close();
//    return converted;
//}
//
//Matrix MazeSolver::getMazeWithNodes() {
//    Matrix mazeWithNodes = getMazeMatrix();
//    if (mazeWithNodes.empty()) return mazeWithNodes;
//
//    std::vector<Position> nodes;
//
//    for (int i = 0; i < totalRows; i++) {
//        for (int k = 0; k < totalCols; k++) {
//            int cur = safe_get(mazeWithNodes, i, k, 0);
//            
//            if (cur == 5 || cur == 4) {
//                nodes.push_back({k, i});
//            } else if (cur == 0) {
//                if (in_bounds(i, k-2, totalRows, totalCols) && 
//                    in_bounds(i, k+2, totalRows, totalCols) && 
//                    in_bounds(i-1, k, totalRows, totalCols) && 
//                    in_bounds(i+1, k, totalRows, totalCols)) {
//                    
//                    if (mazeWithNodes[i][k + 1] == 0 && mazeWithNodes[i][k - 1] == 0) {
//                        if ((mazeWithNodes[i][k + 2] == 0 || mazeWithNodes[i][k - 2] == 0) &&
//                            (mazeWithNodes[i + 1][k] == 0 || mazeWithNodes[i - 1][k] == 0)) {
//                            if ((mazeWithNodes[i + 1][k + 1] == 0 && mazeWithNodes[i + 1][k - 1] == 0) ||
//                                (mazeWithNodes[i - 1][k + 1] == 0 && mazeWithNodes[i - 1][k - 1] == 0)) {
//                                nodes.push_back({k, i});
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    for (const auto& node : nodes) {
//        if (in_bounds(node.second, node.first, totalRows, totalCols)) {
//            int current = mazeWithNodes[node.second][node.first];
//            if (current != 4 && current != 5) {
//                mazeWithNodes[node.second][node.first] = 9;
//            }
//        }
//    }
//
//    return mazeWithNodes;
//}
//
//Matrix MazeSolver::solveMaze() {
//    if (!mazeLoaded) {
//        std::cerr << "Error: No maze loaded" << std::endl;
//        return Matrix();
//    }
//
//    Matrix mazeWithNodes = getMazeWithNodes();
//    std::vector<Position> nodeList;
//
//    for (int y = 0; y < totalRows; y++) {
//        for (int x = 0; x < totalCols; x++) {
//            int val = mazeWithNodes[y][x];
//            if (val == 9 || val == 4 || val == 5) {
//                nodeList.push_back({x, y});
//            }
//        }
//    }
//
//    AdjList adjNodes;
//    for (const auto& node : nodeList) {
//        int x = node.first;
//        int y = node.second;
//
//        for (int jump = 1; x + jump < totalCols; jump++) {
//            int nx = x + jump;
//            int val = mazeWithNodes[y][nx];
//            
//            if (val == 9 || val == 4 || val == 5) {
//                int weight = manhattanDistance(x, y, nx, y);
//                adjNodes[{x, y}].push_back({{nx, y}, weight});
//                adjNodes[{nx, y}].push_back({{x, y}, weight});
//                break;
//            } else if (val == 1 || val == 2 || val == 3) {
//                break;
//            }
//        }
//
//        for (int jump = 1; y + jump < totalRows; jump++) {
//            int ny = y + jump;
//            int val = mazeWithNodes[ny][x];
//            
//            if (val == 9 || val == 4 || val == 5) {
//                int weight = manhattanDistance(x, y, x, ny);
//                adjNodes[{x, y}].push_back({{x, ny}, weight});   
//                adjNodes[{x, ny}].push_back({{x, y}, weight});   
//                break;
//            } else if (val == 1 || val == 2 || val == 3) {
//                break;
//            }
//        }
//    }
//
//    std::unordered_map<pCoord, pCoord, boost::hash<pCoord>> prev;
//    distanceMap distances;
//    priorityQueue pq;
//
//    pCoord start = {startPos.first, startPos.second};
//    pCoord goal = {goalPos.first, goalPos.second};
//
//    for (const auto& node : nodeList) {
//        pCoord p = {node.first, node.second};
//        distances[p] = (p == start) ? 0 : INT_MAX;
//    }
//
//    pq.push({0, start});
//
//    while (!pq.empty()) {
//        auto [currDist, currCoord] = pq.top(); 
//        pq.pop();
//
//        if (distances.find(currCoord) != distances.end() && 
//            currDist > distances[currCoord]) continue;
//
//        if (currCoord == goal) break;
//
//        auto it = adjNodes.find(currCoord);
//        if (it == adjNodes.end()) continue;
//
//        for (const auto& [neighCoord, weight] : it->second) {
//            int ndist = currDist + weight;
//            if (distances.find(neighCoord) == distances.end() || 
//                ndist < distances[neighCoord]) {
//                distances[neighCoord] = ndist;
//                prev[neighCoord] = currCoord;
//                pq.push({ndist, neighCoord});
//            }
//        }
//    }
//
//    if (prev.find(goal) == prev.end() && !(start == goal)) {
//        std::cerr << "No path found" << std::endl;
//        return getMazeMatrix();
//    }
//
//    std::vector<pCoord> pathNodes;
//    pCoord at = goal;
//    while (!(at == start)) {
//        pathNodes.push_back(at);
//        at = prev[at];
//    }
//    pathNodes.push_back(start);
//    std::reverse(pathNodes.begin(), pathNodes.end());
//
//    Matrix result = getMazeMatrix();
//    
//    for (size_t i = 0; i < pathNodes.size() - 1; i++) {
//        int x1 = pathNodes[i].first;
//        int y1 = pathNodes[i].second;
//        int x2 = pathNodes[i + 1].first;
//        int y2 = pathNodes[i + 1].second;
//
//        if (y1 == y2) {
//            int startX = std::min(x1, x2);
//            int endX = std::max(x1, x2);
//            for (int x = startX; x <= endX; x++) {
//                if (result[y1][x] == 0) {
//                    result[y1][x] = 8;
//                }
//            }
//        }
//        // Draw vertical line
//        else if (x1 == x2) {
//            int startY = std::min(y1, y2);
//            int endY = std::max(y1, y2);
//            for (int y = startY; y <= endY; y++) {
//                if (result[y][x1] == 0) {
//                    result[y][x1] = 8;
//                }
//            }
//        }
//    }
//
//    return result;
//}
//
//bool MazeSolver::isValidMove(const Position& pos) {
//    if (!mazeLoaded) return false;
//    
//    int x = pos.first;
//    int y = pos.second;
//    
//    if (!in_bounds(y, x, totalRows, totalCols)) return false;
//    
//    Matrix maze = getMazeMatrix();
//    int cell = maze[y][x];
//    
//    return (cell == 0 || cell == 4 || cell == 5);
//}
//
//bool MazeSolver::isGoal(const Position& pos) {
//    return pos == goalPos;
//}
//
//Position MazeSolver::getStartPosition() {
//    return startPos;
//}
//
//Position MazeSolver::getGoalPosition() {
//    return goalPos;
//}
//
//std::pair<int, int> MazeSolver::getDimensions() {
//    return {totalRows, totalCols};
//}
//
//void MazeSolver::printMatrix(const Matrix& matrix) {
//    if (matrix.empty()) {
//        std::cout << "(empty matrix)\n";
//        return;
//    }
//    
//    for (const auto& row : matrix) {
//        for (int val : row) {
//            std::cout << cellToChar(val);
//        }
//        std::cout << '\n';
//    }
//}
//
//char MazeSolver::cellToChar(int cellValue) {
//    switch (cellValue) {
//        case 0: return ' ';
//        case 1: return 'o';
//        case 2: return '-';
//        case 3: return '|';
//        case 4: return 'G';
//        case 5: return 'S';
//        case 8: return '*';
//        case 9: return '.';
//        default: return '?';
//    }
//}
