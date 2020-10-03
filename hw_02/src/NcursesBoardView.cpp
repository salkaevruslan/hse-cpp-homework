#include "NcursesBoardView.h"
#include <cassert>
#include <iostream>

static constexpr int BOARD_START_X = 2;

static constexpr int BOARD_START_Y = 2;

static constexpr int STEP_CODE = -2;

NcursesBoardView::NcursesBoardView() : BoardView(), curr_point{BOARD_START_X, BOARD_START_Y} {
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    refresh();
    box_win = newwin(BOARD_SIZE + 2, 2 * BOARD_SIZE + 3, curr_point.y, curr_point.x);
    assert(box_win);
    box(box_win, 0, 0);
    wrefresh(box_win);
}

void NcursesBoardView::drawField(Player player, Board &board) const {
    mvwprintw(stdscr, 0, 0, "%s", "Press x to exit");
    if (board.getState() == GameState::Running) {
        if (player == Player::X) {
            mvwprintw(stdscr, 1, 0, "%s", "X move:");
        }
        if (player == Player::O) {
            mvwprintw(stdscr, 1, 0, "%s", "O move:");
        }
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            PointState point = board.getFieldPoint(i, j);
            switch (point) {
                case PointState::None:
                    mvwprintw(stdscr, 3 + i, 4 + 2 * j, "%s", ".");
                    break;
                case PointState::X:
                    mvwprintw(stdscr, 3 + i, 4 + 2 * j, "%s", "X");
                    break;
                case PointState::O:
                    mvwprintw(stdscr, 3 + i, 4 + 2 * j, "%s", "O");
                    break;
                default:
                    std::abort();
            }
        }
    }
    refresh();
    wmove(box_win, curr_point.y, curr_point.x);
    wrefresh(box_win);
}

bool NcursesBoardView::nextMove(Point p, Player player, Board &board) const {
    drawField(player, board);
    if(p.x == STEP_CODE && p.y == STEP_CODE){
        Point field_point;
        p.x = 0, p.y = 0;
        field_point.x = curr_point.y - BOARD_START_Y + 1;
        field_point.y = (curr_point.x - BOARD_START_X) / 2;
        bool can = board.canMove(field_point, player);
        if (can) {
            board.move(field_point, player);
            return true;
        } else {
            return false;
        }
    }
    return false;
}

void NcursesBoardView::printResult(Board &board) const {
    switch (board.getState()){
        case GameState::Draw:
            mvwprintw(stdscr, 1, 0, "%s", "Draw.");
            break;
        case GameState::XWin:
            mvwprintw(stdscr, 1, 0, "%s", "X wins!");
            break;
        case GameState::OWin:
            mvwprintw(stdscr, 1, 0, "%s", "O wins!");
            break;
        default:
            std::abort();
    }
    refresh();
    wmove(box_win, curr_point.y, curr_point.x);
    wrefresh(box_win);
    char ch = 0;
    if (ch != 'x')
         while ((ch = getch()) != 'x');
}

Point NcursesBoardView::readCoordinates() {
    int ch = 0;
    ch = getch();
    Point p{STEP_CODE + 2, STEP_CODE + 2};
    switch (ch) {
        case KEY_LEFT:
            if (curr_point.x > BOARD_START_X) {
                curr_point.x -= 2;
            }
            break;
        case KEY_RIGHT:
            if (curr_point.x < 2 * BOARD_SIZE - 1) {
                curr_point.x += 2;
            }
            break;
        case KEY_UP:
            if (curr_point.y > BOARD_START_Y - 1) {
                curr_point.y--;
            }
            break;
        case KEY_DOWN:
            if (curr_point.y < BOARD_SIZE) {
                curr_point.y++;
            }
            break;
        case 'x':
            p.x = EXIT_CODE;
            p.y = EXIT_CODE;
            break;
        case ' ':
            p.x = STEP_CODE;
            p.y = STEP_CODE;
            break;
    }
    return p;
}

void NcursesBoardView::closeView() const {
    endwin();
}
