.PHONY: clean
CXX = g++
INC = -Iinclude
CUR = -lncurses
WARN = -Werror -Wall -Wextra

all: hw_02 test_hw_02

hw_02: obj/main.o obj/Controller.o obj/Board.o obj/BoardView.o obj/StdioBoardView.o obj/NcursesBoardView.o
	$(CXX) obj/main.o obj/Controller.o obj/Board.o obj/BoardView.o obj/StdioBoardView.o obj/NcursesBoardView.o $(INC) $(CUR) $(WARN) -O0 -g -o hw_02

test_hw_02: obj/test.o obj/Test.o obj/BoardTest.o obj/Board.o
	$(CXX) obj/test.o obj/Test.o obj/BoardTest.o obj/Board.o $(INC) $(WARN) -O0 -g -o test_hw_02

obj/main.o: src/main.cpp | obj
	$(CXX) src/main.cpp $(INC) $(WARN) -O0 -g -c -o obj/main.o

obj/Controller.o: src/Controller.cpp include/Controller.h | obj
	$(CXX) src/Controller.cpp $(INC) $(WARN) -O0 -g -c -o obj/Controller.o

obj/BoardView.o: src/BoardView.cpp include/BoardView.h | obj
	$(CXX) src/BoardView.cpp $(INC) $(WARN) -O0 -g -c -o obj/BoardView.o

obj/StdioBoardView.o: src/StdioBoardView.cpp include/StdioBoardView.h | obj
	$(CXX) src/StdioBoardView.cpp $(INC) $(WARN) -O0 -g -c -o obj/StdioBoardView.o

obj/NcursesBoardView.o: src/NcursesBoardView.cpp include/NcursesBoardView.h | obj
	$(CXX) src/NcursesBoardView.cpp $(INC)  $(CUR) $(WARN) -O0 -g -c -o obj/NcursesBoardView.o

obj/Board.o: src/Board.cpp include/Board.h | obj
	$(CXX) src/Board.cpp $(INC) $(WARN) -O0 -g -c -o obj/Board.o

obj/test.o: test/test.cpp | obj
	$(CXX) test/test.cpp $(INC) $(WARN) -O0 -g -c -o obj/test.o

obj/Test.o: test/Test.cpp include/Test.h | obj
	$(CXX) test/Test.cpp $(INC) $(WARN) -O0 -g -c -o obj/Test.o

obj/BoardTest.o: test/BoardTest.cpp include/BoardTest.h | obj
	$(CXX) test/BoardTest.cpp $(INC) $(WARN) -O0 -g -c -o obj/BoardTest.o

obj:
	mkdir -p obj

clean:
	rm -rf obj/*.o hw_02 test_hw_02 obj
