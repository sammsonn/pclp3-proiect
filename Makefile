CC=gcc
DEPS=main.c functions.c
EXE=main

build: $(DEPS)
	$(CC) -Wall $^ -o $(EXE) -g

run:
	./$(EXE)

.PHONY: clean

clean:
	rm -f $(EXE)