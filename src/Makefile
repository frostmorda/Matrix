CC = g++
SRC = matrix.cpp
OBJS = $(SRC:.cpp=.o)
CFLAGS = -Wall -Wextra -Werror -std=c++17 -lstdc++
DEBUG_FLAG = -g
MAIN_SRC = main.cpp
GCOVFLAG = --coverage
LIB_NAME = matrix.a
TEST_SRCS = test.cpp
.PHONY: test $(LIB_NAME)

all: clean $(LIB_NAME)

$(LIB_NAME): $(OBJS)
	ar rcs $(LIB_NAME) $(OBJS)

$(OBJS):
	$(CC) $(CFLAGS) $(SRC) -c -o $@	

build_test: $(LIB_NAME)
	$(CC) $(CFLAGS) $(TEST_SRCS) $(LIB_NAME) -I./ -L./ -lgtest -o test $(DEBUG_FLAG)
	
test: clean build_test
	./test

gcov_report:
	$(CC) $(CFLAGS) $(GCOVFLAG) $(CFLAGS) $(TEST_SRCS) $(SRC) -I./ -L./ -lgtest -o test
	./test
	lcov -t test -o test.info -c -d .
	genhtml test.info -o report
clean:
	rm -rf *.o *.a *.gcno test ./report ./*.dSYM test.info *.out *.gcda

check:
	python3 ../materials/linters/cpplint.py --extensions=cpp *.cpp *.h
	cppcheck --enable=all --suppress=missingIncludeSystem . *.cpp
	CK_FORK=no leaks --atExit -- ./test
