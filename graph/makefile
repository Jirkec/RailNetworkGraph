ifeq ($(OS), Windows_NT)
	BIN = graph.exe
	CC=gcc.exe
else
	BIN	= graph
	CC=gcc
endif
CFLAFS=-Wall -Wextra -pedantic -ansi
FILES=*.c *.h

$(BIN): $(FILES)
	$(CC) $^ -o $@ $(CFLAFS)
