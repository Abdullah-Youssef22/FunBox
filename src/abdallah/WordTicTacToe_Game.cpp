#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "../../include/util/BoardGame_Classes.h"
#include "../../include/util/GameLaunchers.h"
#include "../../include/WordTicTacToe_Classes.h"
using namespace std;

void GameLaunchers::launch_word_tic_tac_toe() {
    srand(static_cast<unsigned int>(time(0)));

    UI<char>* game_ui = new WordTicTacToe_UI();
    Board<char>* word_board = new WordTicTacToe_board();

    Player<char>** players = game_ui->setup_players();

    for (int i = 0; i < 2; i++) {
        if (players[i]->get_type() == PlayerType::AI) {
            WordTicTacToe_UI* word_ui = dynamic_cast<WordTicTacToe_UI*>(game_ui);
            if (word_ui) {
                string name = players[i]->get_name();
                char symbol = (i == 0) ? 'X' : 'O';
                delete players[i]; 

                players[i] = new WordTicTacToe_AIPlayer(name, symbol,
                    dynamic_cast<WordTicTacToe_board*>(word_board));
            }
        }

        players[i]->set_board_ptr(word_board);
    }

    GameManager<char> word_game(word_board, players, game_ui);
    word_game.run();

    delete word_board;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
    delete game_ui;
}