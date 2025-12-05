#include "../../include/InfinityTicTacToe_Classes.h"

Infinity_TicTacToe_Board::Infinity_TicTacToe_Board()
    : Board<char>(3, 3)
{
    for (auto& row : board)
        for (auto& cell : row)
            cell = '.';
}

bool Infinity_TicTacToe_Board::update_board(Move<char>* move)
{
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate move
    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;

    // Undo move
    if (mark == 0)
    {
        if (board[x][y] != '.')
        {
            board[x][y] = '.';
            n_moves--;

            queue<pair<int, int>> temp;
            while (!moveQueue.empty()) {
                auto p = moveQueue.front();
                moveQueue.pop();
                if (!(p.first == x && p.second == y))
                    temp.push(p);
            }
            moveQueue = temp;
        }
        return true;
    }

    if (board[x][y] != '.')
        return false;

    board[x][y] = toupper(mark);
    n_moves++;
	counter++;
    moveQueue.push({ x, y });

   
   
    if (counter % 3 == 0)
    {
        checking('X');
        checking('O');

        auto oldest = moveQueue.front();
        moveQueue.pop(); // each three moving --> remove old moving

        int ox = oldest.first;
        int oy = oldest.second;
        board[ox][oy] = '.'; 
        n_moves--;
    }
     return true;
}

bool Infinity_TicTacToe_Board::is_lose(Player<char>* player)
{
    return false;
}

bool Infinity_TicTacToe_Board::is_draw(Player<char>* player)
{
    if(counter == 13 && !checking('X') && !checking('O'))
    
        {
            display_draw();
        }
    return counter==13 && !checking('X') && !checking('O');
}

bool Infinity_TicTacToe_Board::game_is_over(Player<char>* player)
{
    return is_win(player) || is_draw(player);
}

bool Infinity_TicTacToe_Board::checking(char sym)
{
   for(int i=0;i<3;i++)
   {
       if(board[i][0]==sym && board[i][1]==sym && board[i][2]==sym)
           return true;
       //====================================================================== 
       if(board[0][i]==sym && board[1][i]==sym && board[2][i]==sym)
           return true;
       //======================================================================  
   }
   if(board[0][0]==sym && board[1][1]==sym && board[2][2]==sym)
       return true;
       //==========================================================================
   if(board[0][2]==sym && board[1][1]==sym && board[2][0]==sym)
	   return true;
   //==========================================================================
   return false;
}



bool Infinity_TicTacToe_Board::is_win(Player<char>* player)
{
    if (checking(player->get_symbol()))
    {
        display_winner(player);
    }
    return checking(player->get_symbol());
}

void Infinity_TicTacToe_Board::display_winner(Player<char>* player) {
    cout << GREEN << "\nCongratulations " << player->get_name()
        << "! You have won the game as player " << player->get_symbol() << "!" << RESET << endl;
    cout << "\nGame Over! Press Enter to continue...";
    cin.ignore();
    cin.get();
    return;
    
}
void Infinity_TicTacToe_Board::display_draw() {
    cout << YELLOW << "\nThe game ended in draw!" << RESET << endl;
    cout << "\nGame Over! Press Enter to continue...";
    cin.ignore();
    cin.get();
	return;
}





Infinity_TicTacToe_UI::Infinity_TicTacToe_UI()
    : UI<char>("Welcome to Infinity_TicTacToe_UI!", 3) {}

Move<char>* Infinity_TicTacToe_UI::get_move(Player<char>* player)
{
    int x, y;
    if (player->get_type() == PlayerType::HUMAN)
    {
        cout << "\nPlease enter your move x and y (0 to 2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER)
    {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}

Player<char>* Infinity_TicTacToe_UI::create_player(string & name, char symbol, PlayerType type)
{
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Infinity_TicTacToe_Player(name, symbol, type);
}

