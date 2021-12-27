SRC := $(wildcard src/*.cpp) $(wildcard src/*/*.cpp) $(wildcard lib/*/*.cpp)
FLAGS := -std=c++20 -o
OPENSSL_DIR := /usr/local/opt/openssl@1.1
WOLFSSL_DIR := /usr/local/
INCLUDES := -Ilib/mqtt_cpp/include -I$(WOLFSSL_DIR)/include -L$(WOLFSSL_DIR)/lib -lwolfssl #-lcrypto

main: $(SRC)
	g++ $^ $(FLAGS) $@ $(INCLUDES)

run: main
	./main