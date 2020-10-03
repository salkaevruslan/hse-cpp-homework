#include "Controller.h"

Controller::Controller(BoardView &view, Board &board): view_(view), board_(board){
}


void Controller::runGame(){
	Point p{0, 0};
	Player player = Player::O;
	view_.drawField(player, board_);
	while (board_.getState() == GameState::Running){ 
		p = view_.readCoordinates();
		if(p.x == EXIT_CODE && p.y == EXIT_CODE)
			break;
		bool moved = view_.nextMove(p, player, board_);
		if(moved){
			if (player == Player::X) {
            	player = Player::O;
        	} else if (player == Player::O) {
           		player = Player::X;
        	}
        	view_.drawField(player, board_);
    	}
	}
	if(!(p.x == EXIT_CODE && p.y == EXIT_CODE))
		view_.printResult(board_);
	view_.closeView();
}