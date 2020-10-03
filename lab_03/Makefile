.PHONY: clean
INC=-Iinclude
WARN=-Werror -Wall -Wextra

lab_03: obj/main.o obj/clist.o | bin
	gcc obj/main.o obj/clist.o $(INC) $(WARN) -O0 -g -o bin/lab_03

obj/main.o: src/main.c | obj
	gcc src/main.c $(INC) $(WARN) -O0 -g -c -o obj/main.o

obj/clist.o: src/clist.c | obj
	gcc src/clist.c $(INC) $(WARN) -O0 -g -c -o obj/clist.o

obj:
	mkdir -p obj

bin:
	mkdir -p bin

clean:
	rm -rf bin/*.o lab_03 bin obj
