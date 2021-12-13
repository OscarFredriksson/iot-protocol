SRC := $(wildcard src/*.cpp)
FLAGS := -std=c++20 -o -pthread


main: $(SRC)
	g++ $^ $(FLAGS) $@

run: main
	./main