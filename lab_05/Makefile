.PHONY: clean
INC=-Iinclude
WARN=-Werror -Wall -Wextra

lab_05: obj/main.o obj/point_list.o obj/clist.o | bin
	gcc obj/main.o obj/point_list.o obj/clist.o $(INC) $(WARN) -O0 -g -o bin/lab_05

obj/main.o: src/main.c | obj
	gcc src/main.c $(INC) $(WARN) -O0 -g -c -o obj/main.o

obj/point_list.o: src/point_list.c include/point_list.h | obj
	gcc src/point_list.c $(INC) $(WARN) -O0 -g -c -o obj/point_list.o

obj/clist.o: src/clist.c include/clist.h | obj
	gcc src/clist.c $(INC) $(WARN) -O0 -g -c -o obj/clist.o

obj:
	mkdir -p obj

bin:
	mkdir -p bin

clean:
	rm -rf bin/*.o lab_05 bin obj
