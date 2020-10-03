#ifndef STDIOBOARDVIEW_H
#define STDIOBOARDVIEW_H

#include "BoardView.h"

class StdioBoardView final : public BoardView {
public:
    StdioBoardView(bool silent_mode);

    bool nextMove(Point p, Player player, Board &board) const override;

    void drawField(Player player, Board &board) const override;

    Point readCoordinates() override;

    void printResult(Board &board) const override;

    void closeView() const override;

private:
    bool silent_mode_;

};


#endif
