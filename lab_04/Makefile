.PHONY: clean
INC=-Iinclude
WARN=-Werror -Wall -Wextra

lab_03: obj/main.o obj/mergesort.o | bin
	gcc obj/main.o obj/mergesort.o $(INC) $(WARN) -O0 -g -o bin/lab_04

obj/main.o: src/main.c | obj
	gcc src/main.c $(INC) $(WARN) -O0 -g -c -o obj/main.o

obj/mergesort.o: src/mergesort.c include/mergesort.h | obj
	gcc src/mergesort.c $(INC) $(WARN) -O0 -g -c -o obj/mergesort.o

obj:
	mkdir -p obj

bin:
	mkdir -p bin

clean:
	rm -rf bin/*.o lab_04 bin obj
