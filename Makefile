CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -g -Iinclude -Wunused-parameter -L/usr/lib
SRC = $(shell find src -name '*.cpp')
OBJ = $(patsubst %.cpp,out/%.o,$(SRC))
TARGET = bin/mex
all: $(TARGET)
$(TARGET): $(OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^ -ldpp -lpthread -lssl -lcrypto
out/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf out bin logs include/token.hpp include/token.h
.PHONY: all clean
