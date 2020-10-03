.PHONY: clean
CXX = g++
INC = -Iinclude
WARN = -Werror -Wall -Wextra

all: lab_13

lab_13: obj/main.o
	$(CXX) obj/main.o $(INC) $(WARN) -O0 -g -o lab_13

obj/main.o: src/main.cpp include/my_array.h | obj
	$(CXX) src/main.cpp $(INC) $(WARN) -O0 -g -c -o obj/main.o

obj:
	mkdir -p obj

clean:
	rm -rf obj/*.o lab_13 obj
