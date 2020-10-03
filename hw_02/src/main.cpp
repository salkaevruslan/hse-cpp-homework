#include "Controller.h"
#include <cassert>
#include <cstring>
#include <iostream>

int main(int argc, char *argv[]) {
    Board board;
    bool silent_mode = false;
    if (argc == 2 && !strcmp(argv[1], "silent")) {
        silent_mode = true;
        return 0;
    }
    if(argc == 2 && !strcmp(argv[1], "curses")) {
        NcursesBoardView ncurses_board_view;
        Controller controller(ncurses_board_view, board);
        controller.runGame();
        return 0;
    }
    if(argc == 1) {
        StdioBoardView stdio_board_view(silent_mode);
        Controller controller(stdio_board_view, board);
        controller.runGame();
        return 0;
    }
    std::cout << "Wrong command.\n";
    return 0;
}