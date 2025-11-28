// #include <iostream>
// #include <unistd.h>
// #include <termios.h>
// using namespace std;
//
// bool kbhit() {
//     bool kbhit;
//     struct termios oldt, newt;
//     int ch;
//     tcgetattr(STDIN_FILENO, &oldt);   // Get the current terminal attributes
//     newt = oldt;
//     newt.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echoing
//     tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // Set new attributes
//
//     ch = getchar();  // Read a character
//     if(ch != EOF) {
//         ungetc(ch, stdin);  // Put the character back into the input buffer
//         kbhit = true;  // A key was pressed
//     }
//
//     tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Restore the old terminal attributes
//     return kbhit;
// }
//
// char getch() {
//     struct termios oldt, newt;
//     char ch;
//     tcgetattr(STDIN_FILENO, &oldt);   // Get the current terminal attributes
//     newt = oldt;
//     newt.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echoing
//     tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // Set new attributes
//
//     ch = getchar();  // Read a character
//     tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Restore the old terminal attributes
//
//     return ch;
// }
//
// int count = 0;
// char lastKey;
// class Observer {
//   private:
//     int keyCount;
//     void (*callback)();
//   public:
//     Observer(void (*fn)()) {
//       keyCount = 0;
//       callback = fn;
//     }
//     char ch;
//     void watch() {
//         keyCount++;
//         callback();
//         ch = getch();
//         lastKey = ch; // Track the last key pressed
//     }
//     void getKeycount() {
//         count = keyCount;
//     }
// };
//
// bool gameOver = false;
// int xWidth = 63;
// int yHeight = 21;
// int xShip = xWidth / 2;
// int yShip = yHeight - 4;
// int score;
//
// /*======ship==
//   _
//  /|\
//  [O]
// /A|A\
//  ^ ^   
//  ============*/
//
// //==============================================DRAW FUNCTION=========
// void draw() {
//     system("clear");
//     for (int i = 0; i <= xWidth; i++) {
//         cout << "#";
//     } cout << endl;
//
//     for (int i = 0; i <= yHeight - 2; i++) {
//         for (int j = 0; j <= xWidth + 2; j++) {
//             if (j == 0 || j == xWidth) {
//                 cout << "#";
//             } else if (j == xShip && i == yShip) {
//                 cout << "O";
//             } else if (j == xShip - 1 && i == yShip) {
//                 cout << "[";
//             } else if (j == xShip + 1 && i == yShip) {
//                 cout << "]";
//             } else if (j == xShip && i == yShip - 1) {
//                 cout << "|";
//             } else if (j == xShip - 1 && i == yShip - 1) {
//                 cout << "/";
//             } else if (j == xShip + 1 && i == yShip - 1) {
//                 cout << "\\";
//             } else if (j == xShip && i == yShip - 2) {
//                 cout << "_";
//             } else if (j == xShip && i == yShip + 1) {
//                 cout << "|";
//             } else if (j == xShip + 1 && i == yShip + 1) {
//                 cout << "A";
//             } else if (j == xShip - 1 && i == yShip + 1) {
//                 cout << "A";
//             } else if (j == xShip + 2 && i == yShip + 1) {
//                 cout << "\\";
//             } else if (j == xShip - 2 && i == yShip + 1) {
//                 cout << "/";
//             } else if (j == xShip - 1&& i == yShip + 2) {
//                 cout << "^";
//             } else if (j == xShip + 1&& i == yShip + 2) {
//                 cout << "^";
//             } else {
//                 cout << " ";
//             }
//         }
//         cout << endl;
//     }
//
//     for (int i = 0; i <= xWidth; i++) {
//         cout << "#";
//     } cout << endl;
// }
// //=====================================================================
//
// Observer slave(draw);
//
// void input() {
//     switch (lastKey) {
//         case 'w':
//             yShip--; // Move up
//             break;
//         case 'a':
//             xShip--; // Move left
//             break;
//         case 's':
//             yShip++; // Move down
//             break;
//         case 'd':
//             xShip++; // Move right
//             break;
//         case 'x':
//             gameOver = true;
//             break;
//         case ' ':
//             break;
//         default:
//             break;
//     }
//
//     if (slave.ch == 'w' && lastKey == 'w') {
//         yShip--; // Continue moving up
//     } else if (slave.ch == 'a' && lastKey == 'a') {
//         xShip--; // Continue moving left
//     } else if (slave.ch == 's' && lastKey == 's') {
//         yShip++; // Continue moving down
//     } else if (slave.ch == 'd' && lastKey == 'd') {
//         xShip++; // Continue moving right
//     }
//
//     if (slave.ch == 'w' && lastKey == 'a') {
//         yShip--; // Move up and left
//         xShip--;
//     } else if (slave.ch == 'w' && lastKey == 'd') {
//         yShip--; // Move up and right
//         xShip++;
//     } else if (slave.ch == 's' && lastKey == 'a') {
//         yShip++; // Move down and left
//         xShip--;
//     } else if (slave.ch == 's' && lastKey == 'd') {
//         yShip++; // Move down and right
//         xShip++;
//     }
// }
//
// void logic() {
//     // we add game logic here if necessary
// }
//
// int main() {
//     draw();
//     while (!gameOver) {
//         slave.watch();
//         input();
//     }
//     return 0;
// }

