.PHONY: clean
INC=-Iinclude
WARN=-Werror -Wall -Wextra

hw_01: obj/main.o obj/bmp.o obj/stego.o | bin
	gcc obj/main.o obj/bmp.o obj/stego.o $(INC) $(WARN) -O0 -g -o bin/hw_01

obj/main.o: src/main.c | obj
	gcc src/main.c $(INC) $(WARN) -O0 -g -c -o obj/main.o

obj/bmp.o: src/bmp.c include/bmp.h | obj
	gcc src/bmp.c $(INC) $(WARN) -O0 -g -c -o obj/bmp.o

obj/stego.o: src/stego.c include/stego.h | obj
	gcc src/stego.c $(INC) $(WARN) -O0 -g -c -o obj/stego.o

obj:
	mkdir -p obj

bin:
	mkdir -p bin

clean:
	rm -rf bin/*.o hw_01 bin obj
