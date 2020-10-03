.PHONY: clean
INC=-Iinclude
WARN=-Werror -Wall -Wextra

lab_02: obj/test.o obj/test_str.o obj/str.o | bin
	gcc obj/test.o obj/test_str.o obj/str.o $(INC) $(WARN) -O0 -g -o bin/lab_02

obj/test.o: src/test.c | obj
	gcc src/test.c $(INC) $(WARN) -O0 -g -c -o obj/test.o

obj/test_str.o: src/test_str.c | obj
	gcc src/test_str.c $(INC) $(WARN) -O0 -g -c -o obj/test_str.o

obj/str.o: src/str.c | obj
	gcc src/str.c $(INC) $(WARN) -O0 -g -c -o obj/str.o

obj:
	mkdir -p obj

bin:
	mkdir -p bin

clean:
	rm -rf bin/*.o lab_01 bin obj
