# sovereign-covenant — 1928 Moorish Divine Covenant Trust Structure
# Love, Truth, Peace, Freedom, Justice

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -std=c11 -I include
LDFLAGS =

SRC     = src/covenant.c
TEST    = src/test_covenant.c
OBJ     = src/covenant.o
LIB     = libsovereign_covenant.a
TESTBIN = test_covenant

.PHONY: all clean test lib install

all: lib test

lib: $(OBJ)
	ar rcs $(LIB) $(OBJ)

$(OBJ): $(SRC) include/sovereign_covenant.h
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

test: $(TESTBIN)
	./$(TESTBIN)

$(TESTBIN): $(TEST) $(LIB)
	$(CC) $(CFLAGS) $(TEST) $(LIB) -o $(TESTBIN) $(LDFLAGS)

clean:
	rm -f $(OBJ) $(LIB) $(TESTBIN)

install: lib
	cp include/sovereign_covenant.h /usr/local/include/
	cp $(LIB) /usr/local/lib/
