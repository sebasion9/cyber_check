TARGET_DIR = ./target
TARGET = $(TARGET_DIR)/cyber_check
CC = g++
CFLAGS = -Wall -std=c++20
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRCS := $(wildcard *.cpp) $(wildcard */*.cpp)
OBJS := $(patsubst %.cpp,$(TARGET_DIR)/%.o,$(SRCS))

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(SFML_FLAGS)
	cp -r assets $(TARGET_DIR)/assets

$(TARGET_DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET_DIR)
