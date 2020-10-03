.PHONY: clean
CXX = g++
INC = -Iinclude
WARN = -Werror -Wall -Wextra

all: lab_12

lab_12: obj/main.o obj/Test.o
	$(CXX) obj/main.o obj/Test.o $(INC) $(WARN) -O0 -g -o lab_12

obj/main.o: src/main.cpp include/my_vector.h include/my_vector_test.h include/my_vector_impl.h | obj
	$(CXX) src/main.cpp $(INC) $(WARN) -O0 -g -c -o obj/main.o

obj/Test.o: src/Test.cpp include/Test.h include/my_vector.h include/my_vector_impl.h | obj
	$(CXX) src/Test.cpp $(INC) $(WARN) -O0 -g -c -o obj/Test.o

obj:
	mkdir -p obj

clean:
	rm -rf obj/*.o lab_12 obj
