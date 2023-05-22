CC=gcc
DEPS=main.c functions.c
EXE=main

build: $(DEPS)
	$(CC) -Wall $^ -o $(EXE) -g
	touch input.in output.out

run:
	./$(EXE)

.PHONY: clean

clean:
	rm -f $(EXE)
	rm input.in output.out
