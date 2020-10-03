#ifndef BOARD_H
#define BOARD_H

#include <vector>

const int BOARD_SIZE = 10;
const int GOAL_LENGTH = 5;

enum class PointState {
    X,
    O,
    None
};
enum class Player {
    X,
    O,
    None
};
enum class GameState {
    Running,
    XWin,
    OWin,
    Draw
};

struct Point{
    int x;
    int y;
};

class Board final {
public:
    Board();

    bool canMove(Point p, Player player) const;

    void move(Point p, Player player);

    GameState getState() const;

    PointState getFieldPoint(int x, int y) const;

    bool inside(int x, int y) const;

private:
    GameState game_state_;
    Player current_player_;
    int turns_left_;
    std::vector<std::vector<PointState>> field_;

    int count(Point p, PointState check_state, int dx, int dy) const;

    void checkFinish(Point p, Player player);

    void setWinner(PointState state);
};


#endif

