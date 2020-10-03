#include "StdioBoardView.h"
#include <iostream>
#include <string>

StdioBoardView::StdioBoardView(bool silent_mode) : BoardView(), silent_mode_(silent_mode) {
}

bool StdioBoardView::nextMove(Point p, Player player, Board &board) const {
    bool can = board.canMove(p, player);
    if (can) {
        board.move(p, player);
        return true;
    } else {
        std::cout << "Bad move!\n";
        if(std::cout.fail())
            std::abort();
        if (player == Player::X)
            std::cout << "X move:";
        if (player == Player::O)
            std::cout << "O move:";
        if(std::cout.fail())
            std::abort();
        return false;
    }
}

void StdioBoardView::drawField(Player player, Board &board) const {
    std::cout << '\n';
    if (!silent_mode_) {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if(std::cout.fail())
                    std::abort();
                PointState point = board.getFieldPoint(i, j);
                if (point == PointState::None) {
                    std::cout << '.';
                    continue;
                }
                if (point == PointState::X) {
                    std::cout << 'X';
                    continue;
                }
                if (point == PointState::O) {
                    std::cout << 'O';
                    continue;
                }
            }
            std::cout << '\n';
            if(std::cout.fail())
                std::abort();
        }
    }
    if (board.getState() == GameState::Running) {
        if (player == Player::X)
            std::cout << "X move:";
        if (player == Player::O)
            std::cout << "O move:";
        if(std::cout.fail())
            std::abort();
    }
}

void StdioBoardView::printResult(Board &board) const {
    switch (board.getState()){
        case GameState::Draw:
            std::cout << "Draw.\n";
            break;
        case GameState::XWin:
            std::cout << "X wins!\n";
            break;
        case GameState::OWin:
            std::cout << "O wins!\n";
            break;
        default:
            std::abort();
    }
    if(std::cout.fail())
        std::abort();
}

void StdioBoardView::closeView() const {
}

Point StdioBoardView::readCoordinates() {
    std::string s, word;
    int temp = 0;
    Point p{BOARD_SIZE, BOARD_SIZE};
    int numbers_read = 0;
    std::getline(std::cin, s);
    if(std::cin.fail())
        std::abort();
    s += ' ';
    for (char c : s) {
        if (c == ' ') {
            if (!word.empty()) {
                try {
                    temp = std::stoi(word);
                    if (numbers_read > 1) {
                        p.x = BOARD_SIZE;
                        p.y = BOARD_SIZE;
                        break;
                    }
                    if (numbers_read == 1) {
                        p.y = temp;
                        ++numbers_read;
                    }
                    if (numbers_read == 0) {
                        p.x = temp;
                        ++numbers_read;
                    }
                }
                catch (std::invalid_argument const &e) {
                    numbers_read = 2;
                }
                word.clear();
            }
        } else {
            word += c;
        }
    }
    return p;
}
