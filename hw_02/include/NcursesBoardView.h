#ifndef NCURSESBOARDVIEW_H
#define NCURSESBOARDVIEW_H

#include "BoardView.h"
#include <ncurses.h>

class NcursesBoardView final : public BoardView {
public:
    NcursesBoardView();

    Point readCoordinates() override;

    bool nextMove(Point p, Player player, Board &board) const override;

    void drawField(Player player,Board & board) const override;

    void printResult(Board &board) const override;

    void closeView() const override;

private:
    WINDOW *box_win;
    Point curr_point;

};


#endif