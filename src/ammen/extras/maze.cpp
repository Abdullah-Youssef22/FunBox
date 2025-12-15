#include "../../../include/util/GameLaunchers.h"
#include "../../../include/maze.h"
#include "../../../include/util/Menu.h"
#include <iostream> // Required for input/output operations (cout, cin)
#include <string>   // Required for string
#include <vector>   // Required for vector
#include <memory>   // Required for unique_ptr
#include <chrono>
#include <thread>


#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

using namespace std;
using namespace std::chrono;

static void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Non-blocking keyboard input
static bool kbhit() {
#ifdef _WIN32
    return _kbhit() != 0;
#else
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }

    return false;
#endif
}

static char getKey() {
#ifdef _WIN32
    return _getch();
#else
    return getchar();
#endif
}

void displayMazeWithPlayer(const Matrix& maze, const Position& playerPos) {
    for (int y = 0; y < (int)maze.size(); y++) {
        for (int x = 0; x < (int)maze[0].size(); x++) {
            if (Position(x, y) == playerPos) {
                cout << 'O';
            } else {
                cout << MazeSolver::cellToChar(maze[y][x]);
            }
        }
        cout << '\n';
    }
}

void watchDijkstraSolve(MazeSolver& solver) {
    cout << "\n=== DIJKSTRA'S ALGORITHM BENCHMARK ===\n\n";
    cout << "Original Maze:\n";
    MazeSolver::printMatrix(solver.getMazeMatrix());
    cout << "\nSolving...\n";

    auto start = high_resolution_clock::now();
    Matrix solution = solver.solveMaze();
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);

    cout << "\nSolution found!\n";
    MazeSolver::printMatrix(solution);

    cout << "\n--- Benchmark Results ---\n";
    cout << "Time taken: " << duration.count() / 1000.0 << " ms\n";
    cout << "           (" << duration.count() << " microseconds)\n";
}

void playMazeManually(MazeSolver& solver) {
    Position playerPos = solver.getStartPosition();
    Position goalPos = solver.getGoalPosition();
    Matrix maze = solver.getMazeMatrix();

    int moves = 0;
    bool gameRunning = true;
    string statusMessage = "";

    cout << "\n=== MANUAL PLAY MODE ===\n";
    cout << "Controls: W (up), A (left), S (down), D (right), Q (quit)\n";
    cout << "Goal: Reach 'G' starting from 'S'\n";
    cout << "Press any key to start...\n";
    cin.get();
    auto startTime = high_resolution_clock::now();

    while (gameRunning) {
        auto currentTime = high_resolution_clock::now();
        auto elapsed = duration_cast<seconds>(currentTime - startTime);

        clearScreen();
        cout << "=== MAZE GAME ===\n";
        cout << "Moves: " << moves << " | Time: " << elapsed.count() << "s | Position: (" 
             << playerPos.first << ", " << playerPos.second << ")\n";

        if (!statusMessage.empty()) {
            cout << "Status: " << statusMessage << "\n";
            statusMessage = "";
        }
        cout << "\n";

        displayMazeWithPlayer(maze, playerPos);


        if (solver.isGoal(playerPos)) {
            auto endTime = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(endTime - startTime);

            cout << "\nCONGRATULATIONS! You reached the goal!\n";
            cout << "\n--- Player Statistics ---\n";
            cout << "Total moves: " << moves << "\n";
            cout << "Time taken: " << duration.count() / 1000.0 << " seconds\n";
            break;
        }


        if (kbhit()) {
            char input = tolower(getKey());
            Position newPos = playerPos;

            switch (input) {
                case 'w': newPos.second--; break;
                case 's': newPos.second++; break; 
                case 'a': newPos.first--; break; 
                case 'd': newPos.first++; break; 
                case 'q': 
                    gameRunning = false;
                    cout << "\nGame quit.\n";
                    continue;
                default:
                    statusMessage = "Invalid key! Use W/A/S/D to move, Q to quit";
                    continue;
            }

            // Validate and apply move
            if (solver.isValidMove(newPos)) {
                playerPos = newPos;
                moves++;
            } else {
                statusMessage = "Can't move there - blocked!";
            }
        }

        this_thread::sleep_for(milliseconds(50));
    }
}

void showMenu() {
    cout << "\n=== MAZE GAME ===\n";
    cout << "1. Watch Dijkstra's algorithm solve the maze\n";
    cout << "2. Play the maze yourself\n";
    cout << "3. Show maze with nodes\n";
    cout << "4. Load different maze\n";
    cout << "5. Exit\n";
    cout << "\nChoice: ";
}

void GameLaunchers::launch_labyrinth() {
    MazeSolver solver;
    string mazePath;

    cout << "Enter maze file path: ";
    getline(cin, mazePath);

    if (!solver.loadMaze(mazePath)) {
        cerr << "Failed to load maze. Exiting.\n";
        return;
    }

    cout << "Maze loaded successfully!\n";
    auto [rows, cols] = solver.getDimensions();
    cout << "Dimensions: " << rows << " x " << cols << "\n";

    while (true) {
        showMenu();
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                watchDijkstraSolve(solver);
                cout << "\nPress Enter to continue...";
                cin.get();
                break;

            case 2:
                playMazeManually(solver);
                cout << "\nPress Enter to continue...";
                cin.get();
                break;

            case 3:
                cout << "\nMaze with nodes marked:\n";
                MazeSolver::printMatrix(solver.getMazeWithNodes());
                cout << "\nPress Enter to continue...";
                cin.get();
                break;

            case 4:
                cout << "Enter new maze file path: ";
                getline(cin, mazePath);
                if (solver.loadMaze(mazePath)) {
                    cout << "New maze loaded!\n";
                } else {
                    cerr << "Failed to load maze.\n";
                }
                break;

            case 5:
                cout << "Thanks for playing!\n";
                return;

            default:
                cout << "Invalid choice!\n";
        }
    }
    return;
}

