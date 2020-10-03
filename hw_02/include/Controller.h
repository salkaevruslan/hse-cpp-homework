#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "BoardView.h"
#include "StdioBoardView.h"
#include "NcursesBoardView.h"	
#include <string>

class Controller final {
public:
	Controller(BoardView &view, Board &board);
	
	void runGame();

private:
	BoardView &view_; 
	Board &board_;

};

#endif