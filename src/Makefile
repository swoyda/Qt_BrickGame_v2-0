LIB_DIR = snake
CC = g++
CFLAGS = -g -Wall -Wextra -Werror -std=c++17
TEST_FLAGS= -lgtest -lgtest_main -lpthread
GCOV_FLAGS= -fprofile-arcs -ftest-coverage
PREFIX ?= 
DIST_DIR := dist
INSTALL_DIR := $(PREFIX)game
OBJ_FSM := Tetris/tetris.o
DOXYFILE := Doxyfile

PROGRAM = Brick_game
SSOURCES = brick_game/snake/*.cpp brick_game/snake/*.h gui/cli/main.cpp gui/cli/main.h brick_game/defines.h
TSOURCES = tetris.a
SOURCES = brick_game/snake/model.cpp
TEST_SOURCES = tests/*.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

all: clear install
install: tetris.o compile desktop
	@mkdir -p $(INSTALL_DIR)
	@cp $(PROGRAM)_cli $(INSTALL_DIR)
	@cp $(PROGRAM) $(INSTALL_DIR)
uninstall:
	clear
	@rm -rf $(INSTALL_DIR)
compile: snake.a
	$(CC) $(CFLAGS)  snake.a $(TSOURCES) -lncurses -o $(PROGRAM)_cli

clear:
	rm -rf *.gch brick_game/snake/*gch *.o *.a $(PROGRAM) test
	rm -rf ./gcov/*.o ./gcov/*.gc*
	rm -rf *report* *.gc* latex html gui/desktop/BrickGameCore/build/Desktop_Qt_6_6_3_MinGW_64_bit-Release/release/*.o
	rm -rf gui/cli/*.gc* *.o *.a dist Brick_game

clean: clear
snake.a:
	$(CC) -c $(SSOURCES) $(CFLAGS)
	ar rc snake.a *.o
	ranlib snake.a
desktop:
	rm -rf desk
	mkdir desk
	cd desk && qmake ../gui/desktop/BrickGameCore
	cd desk && make
	mv desk/BrickGameCore Brick_game
	rm -rf desk
tetris.o:
	gcc brick_game/tetris/*.c brick_game/tetris/*.h brick_game/tetris/core/*.c brick_game/tetris/common/*.h -Wpedantic brick_game/tetris/core/inc/*.h -g -Wall -Wextra -c
	ar rc tetris.a *.o
	ranlib tetris.a
%.o: %.cpp
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $< -o $@
model.o:
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -lgtest -lgtest_main -lpthread -c -o $@ -lncurses
test: clean
	$(CC) $(GCOV_FLAGS) $(CFLAGS) $(TEST_SOURCES) $(TEST_FLAGS) $(SOURCES)  -o test -lncurses $(TEST_FLAGS)
	./test
gcov_report: clean test
	./test > /dev/null
	lcov --no-external --directory . --capture --output-file report.info
	genhtml report.info --output-directory html_report
	xdg-open html_report/index.html
dvi: $(DOXYFILE)
	@doxygen $(DOXYFILE)
dist: clean
	@mkdir -p $(DIST_DIR)
	@tar czf $(DIST_DIR)/$(PROGRAM).tar.gz brick_game gui Doxyfile Makefile
clang:
	clang-format --style=Google -i brick_game/snake/*.cpp gui/cli/*.cpp brick_game/snake/*.h tests/*.cpp gui/desktop/BrickGameCore/*.cpp gui/desktop/BrickGameCore/snake/*.cpp
valgrind:
	valgrind -s --tool=memcheck --leak-check=full --track-origins=yes test

valgrind_plus:
	CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test
.PHONY: all install uninstall clean dvi dist