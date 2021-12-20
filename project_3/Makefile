SRC := $(wildcard src/*.cpp) $(wildcard src/*/*.cpp) $(wildcard lib/*/*.cpp)
FLAGS := -std=c++20 -o
INCLUDES := lib/mqtt_cpp/include

main: $(SRC)
	g++ -I$(INCLUDES) $^ $(FLAGS) $@

run: main
	./main