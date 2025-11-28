#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include <string>
#include <vector>
#include <utility>

typedef std::vector<std::vector<int>> Matrix;
typedef std::pair<int, int> Position;

/**
 * @brief Main class for loading and solving mazes
 * 
 * Cell values in matrix:
 * 0 = empty space
 * 1 = post (o)
 * 2 = horizontal obstacle (-)
 * 3 = vertical obstacle (|)
 * 4 = goal (G)
 * 5 = start (S)
 * 8 = path marker (*)
 * 9 = node (N)
 */
class MazeSolver {
private:
    std::string mazePath;
    int totalRows;
    int totalCols;
    Position startPos;
    Position goalPos;
    bool mazeLoaded;

public:
    /**
     * @brief Constructor
     */
    MazeSolver();

    /**
     * @brief Load a maze from a file path
     * @param path Full path to the maze file (e.g., "/home/user/mazes/1.txt")
     * @return true if maze loaded successfully, false otherwise
     */
    bool loadMaze(const std::string& path);

    /**
     * @brief Get the maze as a matrix of integers
     * @return Matrix representation of the maze
     */
    Matrix getMazeMatrix();

    /**
     * @brief Get the maze with detected nodes marked
     * @return Matrix with nodes marked as 9
     */
    Matrix getMazeWithNodes();

    /**
     * @brief Solve the maze using Dijkstra's algorithm
     * @return Matrix with the shortest path marked with 8, 
     *         connecting line segments marked with 8 as well
     */
    Matrix solveMaze();

    /**
     * @brief Check if a position is valid (in bounds and not an obstacle)
     * @param pos Position to check
     * @return true if valid move, false otherwise
     */
    bool isValidMove(const Position& pos);

    /**
     * @brief Check if player has reached the goal
     * @param pos Current player position
     * @return true if at goal, false otherwise
     */
    bool isGoal(const Position& pos);

    /**
     * @brief Get the start position
     * @return Position of 'S' in the maze
     */
    Position getStartPosition();

    /**
     * @brief Get the goal position
     * @return Position of 'G' in the maze
     */
    Position getGoalPosition();

    /**
     * @brief Get maze dimensions
     * @return pair of (rows, cols)
     */
    std::pair<int, int> getDimensions();

    /**
     * @brief Print the maze matrix to console (for debugging)
     * @param matrix The matrix to print
     */
    static void printMatrix(const Matrix& matrix);

    /**
     * @brief Get a human-readable character for a cell value
     * @param cellValue The integer value from the matrix
     * @return Character representation
     */
    static char cellToChar(int cellValue);
};

#endif // MAZE_SOLVER_H
