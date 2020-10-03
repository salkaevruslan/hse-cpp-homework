#include "BoardTest.h"

void BoardTest::runAllTests() {
    testCorrectTurn();
    testPointOccupied();
    testOtherPlayerTurn();
    testPointOutsideField1();
    testPointOutsideField2();
    testGameIsRunning();
    testOWinByRow();
    testOWinByColumn();
    testOWinByFirstDiag();
    testOWinBySecondDiag();
    testMoveAfterGameEnd();
    testXWinByRow();
    testXWinByColumn();
    testXWinByFirstDiag();
    testXWinBySecondDiag();
    testDraw();
}

void BoardTest::testCorrectTurn() {
    Board b;
    b.move({0, 0}, Player::O);
    DO_CHECK(b.canMove({0, 1}, Player::X));
}

void BoardTest::testPointOccupied() {
    Board b;
    b.move({0, 0}, Player::O);
    DO_CHECK(!b.canMove({0, 0}, Player::X));
}

void BoardTest::testOtherPlayerTurn() {
    Board b;
    b.move({0, 0}, Player::O);
    DO_CHECK(!b.canMove({1, 1}, Player::O));
}

void BoardTest::testPointOutsideField1() {
    Board b;
    DO_CHECK(!b.canMove({10, 1}, Player::O));
}

void BoardTest::testPointOutsideField2() {
    Board b;
    DO_CHECK(!b.canMove({5, -1}, Player::O));
}

void BoardTest::testGameIsRunning() {
    Board b;
    b.move({0, 0}, Player::O);
    b.move({0, 1}, Player::X);
    b.move({1, 0}, Player::O);
    b.move({4, 5}, Player::X);
    b.move({5, 5}, Player::O);
    DO_CHECK(b.getState() == GameState::Running);
}

void BoardTest::testOWinByRow() {
    Board b;
    b.move({0, 0}, Player::O);
    b.move({1, 0}, Player::X);
    b.move({0, 1}, Player::O);
    b.move({1, 1}, Player::X);
    b.move({0, 2}, Player::O);
    b.move({1, 2}, Player::X);
    b.move({0, 4}, Player::O);
    b.move({1, 4}, Player::X);
    b.move({0, 3}, Player::O);
    DO_CHECK(b.getState() == GameState::OWin);
}


void BoardTest::testOWinByColumn() {
    Board b;
    b.move({0, 0}, Player::O);
    b.move({0, 1}, Player::X);
    b.move({1, 0}, Player::O);
    b.move({1, 1}, Player::X);
    b.move({2, 0}, Player::O);
    b.move({2, 1}, Player::X);
    b.move({3, 0}, Player::O);
    b.move({3, 1}, Player::X);
    b.move({4, 0}, Player::O);
    DO_CHECK(b.getState() == GameState::OWin);
}

void BoardTest::testOWinByFirstDiag() {
    Board b;
    b.move({0, 0}, Player::O);
    b.move({9, 9}, Player::X);
    b.move({1, 1}, Player::O);
    b.move({8, 8}, Player::X);
    b.move({2, 2}, Player::O);
    b.move({7, 7}, Player::X);
    b.move({3, 3}, Player::O);
    b.move({6, 6}, Player::X);
    b.move({4, 4}, Player::O);
    DO_CHECK(b.getState() == GameState::OWin);
}

void BoardTest::testOWinBySecondDiag() {
    Board b;
    b.move({0, 9}, Player::O);
    b.move({9, 9}, Player::X);
    b.move({1, 8}, Player::O);
    b.move({8, 8}, Player::X);
    b.move({2, 7}, Player::O);
    b.move({7, 7}, Player::X);
    b.move({4, 5}, Player::O);
    b.move({6, 6}, Player::X);
    b.move({3, 6}, Player::O);
    DO_CHECK(b.getState() == GameState::OWin);
}

void BoardTest::testMoveAfterGameEnd() {
    Board b;
    b.move({0, 9}, Player::O);
    b.move({9, 9}, Player::X);
    b.move({1, 8}, Player::O);
    b.move({8, 8}, Player::X);
    b.move({2, 7}, Player::O);
    b.move({7, 7}, Player::X);
    b.move({4, 5}, Player::O);
    b.move({6, 6}, Player::X);
    b.move({3, 6}, Player::O);
    DO_CHECK(!b.canMove({2, 2}, Player::X));
}

void BoardTest::testXWinByRow() {
    Board b;
    b.move({0, 9}, Player::O);
    b.move({0, 0}, Player::X);
    b.move({0, 8}, Player::O);
    b.move({0, 1}, Player::X);
    b.move({0, 7}, Player::O);
    b.move({0, 3}, Player::X);
    b.move({0, 5}, Player::O);
    b.move({0, 4}, Player::X);
    b.move({4, 4}, Player::O);
    b.move({0, 2}, Player::X);
    DO_CHECK(b.getState() == GameState::XWin);
}

void BoardTest::testXWinByColumn() {
    Board b;
    b.move({0, 9}, Player::O);
    b.move({0, 0}, Player::X);
    b.move({0, 8}, Player::O);
    b.move({1, 0}, Player::X);
    b.move({0, 7}, Player::O);
    b.move({2, 0}, Player::X);
    b.move({0, 5}, Player::O);
    b.move({4, 0}, Player::X);
    b.move({0, 4}, Player::O);
    b.move({3, 0}, Player::X);
    DO_CHECK(b.getState() == GameState::XWin);
}

void BoardTest::testXWinByFirstDiag() {
    Board b;
    b.move({0, 9}, Player::O);
    b.move({0, 0}, Player::X);
    b.move({0, 8}, Player::O);
    b.move({1, 1}, Player::X);
    b.move({0, 7}, Player::O);
    b.move({2, 2}, Player::X);
    b.move({0, 5}, Player::O);
    b.move({3, 3}, Player::X);
    b.move({0, 4}, Player::O);
    b.move({4, 4}, Player::X);
    DO_CHECK(b.getState() == GameState::XWin);
}

void BoardTest::testXWinBySecondDiag() {
    Board b;
    b.move({0, 9}, Player::O);
    b.move({9, 0}, Player::X);
    b.move({0, 8}, Player::O);
    b.move({8, 1}, Player::X);
    b.move({0, 7}, Player::O);
    b.move({7, 2}, Player::X);
    b.move({0, 5}, Player::O);
    b.move({6, 3}, Player::X);
    b.move({0, 4}, Player::O);
    b.move({5, 4}, Player::X);
    DO_CHECK(b.getState() == GameState::XWin);
}

void BoardTest::testDraw() {
    Board b;
    for (int i = 0; i < 5; ++i) {
        b.move({2 * i, 0}, Player::O);
        for (int j = 1; j <= 4; ++j)
        {
            b.move({2 * i, j}, Player::X);
            b.move({2 * i, j + 4}, Player::O);
        }
        b.move({2 * i, 9}, Player::X);

        b.move({2 * i, 9}, Player::O);
        for (int j = 1; j <= 4; ++j)
        {
            b.move({2 * i, j + 4}, Player::X);
            b.move({2 * i, j}, Player::O);
        }
        b.move({2 * i, 0}, Player::X);
    }
    DO_CHECK(b.getState() == GameState::Draw);
}






