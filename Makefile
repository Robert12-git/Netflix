build:
	gcc main.c stack.c queue.c utils.c list.c -std=c99 -o tema2 -Wall -g

run:
	./tema2 data.in data.out

valgrind:
	valgrind --leak-check=full ./tema2 data.in data.out

clean:
	rm -rf ./tema2