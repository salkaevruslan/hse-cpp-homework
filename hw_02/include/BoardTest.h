#ifndef BOARDTEST_H
#define BOARDTEST_H

#include "Test.h"
#include "Board.h"

class BoardTest : public Test {
public:
    void runAllTests() override;

private:
    void testCorrectTurn();

    void testPointOccupied();

    void testOtherPlayerTurn();

    void testPointOutsideField1();

    void testPointOutsideField2();

    void testGameIsRunning();

    void testMoveAfterGameEnd();

    void testOWinByRow();

    void testOWinByColumn();

    void testOWinByFirstDiag();

    void testOWinBySecondDiag();

    void testXWinByRow();

    void testXWinByColumn();

    void testXWinByFirstDiag();

    void testXWinBySecondDiag();

    void testDraw();

};

#endif

