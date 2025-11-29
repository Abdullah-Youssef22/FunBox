#include <iostream>
#include <unistd.h>
#include <termios.h>
#include "../../../include/util/GameLaunchers.h"
using namespace std;

namespace {
bool gameOver;
int score;
}
const int width = 21;
const int height = 11;
int x, y, fruitX, fruitY;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;

static bool kbhit() {
    struct termios oldt, newt;
    int ch;
    bool kbhit = false;

    tcgetattr(STDIN_FILENO, &oldt);   // Get the current terminal attributes
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echoing
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // Set new attributes

    ch = getchar();  // Read a character
    if(ch != EOF) {
        ungetc(ch, stdin);  // Put the character back into the input buffer
        kbhit = true;  // A key was pressed
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Restore the old terminal attributes
    return kbhit;
}

static char getch() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);   // Get the current terminal attributes
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echoing
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // Set new attributes

    ch = getchar();  // Read a character
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Restore the old terminal attributes

    return ch;
}


void Setup(){
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}



void Draw()
{
    system("clear");
    for (int i = 0; i < width+2; i++) {
      cout << "#";
    }


    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {   
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "*";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }


            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width+2; i++) {
        cout << "#";
    }
    cout << endl;
    cout << endl;
    cout << "\033[1mSCORE:\033[0m" << score << endl;
}




void Input() {
    if (kbhit())
    {
        switch (getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];

    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (x > width || x < 0 || y > height || y < 0) {
     gameOver = true;
    }
    //if (x >= width) x = 0; else if (x < 0) x = width - 1;
    //if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}



void GameLaunchers::launch_snake() {
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
    }
    return;
}


