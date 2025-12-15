#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <thread>
#include "../../../include/util/GameLaunchers.h"

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#endif

using namespace std;

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

static char getch() {
#ifdef _WIN32
return _getch();
#else
struct termios oldt, newt;
char ch;
tcgetattr(STDIN_FILENO, &oldt);
newt = oldt;
newt.c_lflag &= ~(ICANON | ECHO);
tcsetattr(STDIN_FILENO, TCSANOW, &newt);

ch = getchar();
tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

return ch;
#endif
}

static void clearScreen() {
#ifdef _WIN32
system("cls");
#else
system("clear");
#endif
}

const int xWidth = 63;
const int yHeight = 21;

namespace {
bool gameOver = false;
int score = 0;
}
int xShip = xWidth / 2;
int yShip = yHeight - 4;
char lastKey = '\0';

struct Obstacle {
int x;
int y;
char symbol;
};

vector<Obstacle> obstacles;
int obstacleSpawnCounter = 0;
const int SPAWN_INTERVAL = 8; 
const int OBSTACLE_SPEED = 1;

void draw() {
clearScreen();

for (int i = 0; i <= xWidth; i++) {
   cout << "#";
}
cout << endl;

for (int i = 0; i <= yHeight - 2; i++) {
   for (int j = 0; j <= xWidth + 2; j++) {
       if (j == 0 || j == xWidth) {
           cout << "#";
       } 
       else {
           bool isObstacle = false;
           for (const auto& obs : obstacles) {
               if (obs.x == j && obs.y == i) {
                   cout << obs.symbol;
                   isObstacle = true;
                   break;
               }
           }
           
           if (!isObstacle) {
               // Draw ship
               if (j == xShip && i == yShip) {
                   cout << "O";
               } else if (j == xShip - 1 && i == yShip) {
                   cout << "[";
               } else if (j == xShip + 1 && i == yShip) {
                   cout << "]";
               } else if (j == xShip && i == yShip - 1) {
                   cout << "|";
               } else if (j == xShip - 1 && i == yShip - 1) {
                   cout << "/";
               } else if (j == xShip + 1 && i == yShip - 1) {
                   cout << "\\";
               } else if (j == xShip && i == yShip - 2) {
                   cout << "_";
               } else if (j == xShip && i == yShip + 1) {
                   cout << "|";
               } else if (j == xShip + 1 && i == yShip + 1) {
                   cout << "A";
               } else if (j == xShip - 1 && i == yShip + 1) {
                   cout << "A";
               } else if (j == xShip + 2 && i == yShip + 1) {
                   cout << "\\";
               } else if (j == xShip - 2 && i == yShip + 1) {
                   cout << "/";
               } else if (j == xShip - 1 && i == yShip + 2) {
                   cout << "^";
               } else if (j == xShip + 1 && i == yShip + 2) {
                   cout << "^";
               } else {
                   cout << " ";
               }
           }
       }
   }
   cout << endl;
}

for (int i = 0; i <= xWidth; i++) {
   cout << "#";
}
cout << endl;

cout << "Score: " << score << " | Press 'x' to quit" << endl;
}

void input() {
if (kbhit()) {
   lastKey = getch();
}

switch (lastKey) {
   case 'w':
       if (yShip > 0) yShip--;
       break;
   case 'a':
       if (xShip > 2) xShip--;
       break;
   case 's':
       if (yShip < yHeight - 5) yShip++;
       break;
   case 'd':
       if (xShip < xWidth - 2) xShip++;
       break;
   case 'x':
       gameOver = true;
       break;
}
}

void spawnObstacle() {
obstacleSpawnCounter++;

if (obstacleSpawnCounter >= SPAWN_INTERVAL) {
   obstacleSpawnCounter = 0;
   
   Obstacle newObs;
   newObs.x = (rand() % (xWidth - 4)) + 2;
   newObs.y = 0;
   newObs.symbol = '*';
   
   obstacles.push_back(newObs);
}
}

bool checkCollision() {
vector<pair<int, int>> shipPositions = {
   {xShip, yShip},         // Center O
   {xShip - 1, yShip},     // [
   {xShip + 1, yShip},     // ]
   {xShip, yShip - 1},     // |
   {xShip - 1, yShip - 1}, // /
   {xShip + 1, yShip - 1}, // backslash
   {xShip, yShip - 2},     // _
   {xShip, yShip + 1},     // |
   {xShip + 1, yShip + 1}, // A
   {xShip - 1, yShip + 1}, // A
   {xShip + 2, yShip + 1}, // backslash
   {xShip - 2, yShip + 1}, // /
   {xShip - 1, yShip + 2}, // ^
   {xShip + 1, yShip + 2}  // ^
};

for (const auto& obs : obstacles) {
   for (const auto& shipPos : shipPositions) {
       if (obs.x == shipPos.first && obs.y == shipPos.second) {
           return true;
       }
   }
}

return false;
}

// Game logic
void logic() {
for (auto& obs : obstacles) {
   obs.y += OBSTACLE_SPEED;
}

// remove obstacles that are off screen
obstacles.erase(
   remove_if(obstacles.begin(), obstacles.end(),
       [](const Obstacle& obs) { return obs.y > yHeight; }),
   obstacles.end()
);

spawnObstacle();

if (checkCollision()) {
   gameOver = true;
}

score++;
}

void GameLaunchers::launch_spaceship() {
  srand(time(0));

  cout << "=== SPACESHIP GAME ===\n";
  cout << "Controls: W/A/S/D to move, X to quit\n";
  cout << "Avoid the falling asteroids (*)\n";
  cout << "Press any key to start...\n";
  cin.get();

  while (!gameOver) {
      draw();
      input();
      logic();

      this_thread::sleep_for(chrono::milliseconds(100));
  }

  system("clear");
  cout << "\n=== GAME OVER ===\n";
  cout << "Final Score: " << score << endl;
  cout << "Thanks for playing!\n";
 return;
}

