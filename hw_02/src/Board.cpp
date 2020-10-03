#include "Board.h"
#include <cassert>

Board::Board(): game_state_(GameState::Running), current_player_(Player::O), turns_left_(BOARD_SIZE * BOARD_SIZE) {
    field_.resize(BOARD_SIZE, std::vector<PointState>(BOARD_SIZE, PointState::None));
}

bool Board::inside(int x, int y) const {
    return (0 <= x && x < BOARD_SIZE && 0 <= y && y < BOARD_SIZE);
}

bool Board::canMove(Point p, enum Player player) const {
    if (game_state_ != GameState::Running)
        return false;
    if (player != current_player_ || current_player_ == Player::None)
        return false;
    if (!inside(p.x, p.y))
        return false;
    if (field_[p.x][p.y] != PointState::None)
        return false;
    return true;
}

void Board::move(Point p, Player player) {
    assert(turns_left_ > 0);
    assert(player == Player::X || player == Player::O);
    if (player == Player::X) {
        field_[p.x][p.y] = PointState::X;
        current_player_ = Player::O;
    }
    if (player == Player::O) {
        field_[p.x][p.y] = PointState::O;
        current_player_ = Player::X;
    }
    checkFinish(p, player);
    turns_left_--;
    if (!turns_left_)
        game_state_ = GameState::Draw;
}

enum GameState Board::getState() const {
    return game_state_;
}

void Board::checkFinish(Point p, Player player) {
    assert(player == Player::X || player == Player::O);
    PointState check_state = PointState::None;
    if (player == Player::X) {
        check_state = PointState::X;
    }
    if (player == Player::O) {
        check_state = PointState::O;
    }
    if (count(p, check_state, 0, 1) >= GOAL_LENGTH) {
        setWinner(check_state);
        return;
    }
    if (count(p, check_state, 1, 0) >= GOAL_LENGTH) {
        setWinner(check_state);
        return;
    }
    if (count(p, check_state, 1, 1) >= GOAL_LENGTH) {
        setWinner(check_state);
        return;
    }
    if (count(p, check_state, 1, -1) >= GOAL_LENGTH) {
        setWinner(check_state);
        return;
    }
    if (turns_left_ == 0)
        game_state_ = GameState::Draw;
}

int Board::count(Point p, enum PointState check_state, int dx, int dy) const {
    assert(field_[p.x][p.y] == check_state);
    int length = 1;
    int x_check = p.x + dx;
    int y_check = p.y + dy;
    while (inside(x_check, y_check) && field_[x_check][y_check] == check_state) {
        ++length, y_check += dy, x_check += dx;
    }
    x_check = p.x - dx;
    y_check = p.y - dy;
    while (inside(x_check, y_check) && field_[x_check][y_check] == check_state) {
        ++length, y_check -= dy, x_check -= dx;
    }
    return length;
}

void Board::setWinner(enum PointState state) {
    assert(state == PointState::X || state == PointState::O);
    if (state == PointState::X)
        game_state_ = GameState::XWin;
    if (state == PointState::O)
        game_state_ = GameState::OWin;
    current_player_ = Player::None;
}

enum PointState Board::getFieldPoint(int x, int y) const {
    assert(inside(x,y));
    return field_[x][y];
}


