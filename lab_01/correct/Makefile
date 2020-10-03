all: dirs build

build: io util algorithm
	gcc -Wall -Wextra -Werror -Iinclude src/main.c obj/*.o -o bin/lab_01

io: src/io.c
	gcc -Wall -Wextra -Werror -Iinclude src/io.c -c -o obj/io.o

util: src/util.c
	gcc -Wall -Wextra -Werror -Iinclude src/util.c -c -o obj/util.o

algorithm: src/algorithm.c
	gcc -Wall -Wextra -Werror -Iinclude src/algorithm.c -c -o obj/algorithm.o

dirs:
	mkdir -p bin obj

clean:
	rm -rf bin/*.o lab_01 bin obj

