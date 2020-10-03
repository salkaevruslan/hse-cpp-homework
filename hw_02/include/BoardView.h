#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include "Board.h"

const int EXIT_CODE = -1;

class BoardView {
public:
    BoardView();

    virtual bool nextMove(Point p, Player player, Board &board) const = 0;

    virtual void drawField(Player player, Board &board) const = 0;

    virtual Point readCoordinates() = 0;

    virtual void printResult(Board &board) const = 0;

    virtual void closeView() const = 0;

protected:
	Point curr_point; 
};

#endif