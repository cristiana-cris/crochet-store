# Compiler & Flags
CXX = g++
CXXFLAGS = -Wall -Wextra -fdiagnostics-color=always -g -std=c++17
CXXFLAGS += -I./include

# Directories
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = .

# Target & Source Files
TARGET = $(BIN_DIR)/program
SOURCES = main.cpp $(SRC_DIR)/containers.cpp $(SRC_DIR)/products.cpp $(SRC_DIR)/yarn.cpp
HEADERS = include/containers.h include/products.h include/yarn.h
OBJECTS = $(addprefix $(OBJ_DIR)/,$(notdir $(SOURCES:.cpp=.o)))



.PHONY: all run clean help

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: main.cpp $(HEADERS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)




run: $(TARGET)
	@$(TARGET)

clean:
	@rm -rf $(OBJ_DIR) $(TARGET)

help:
	@echo "Available targets:"
	@echo "  make      - Build the project"
	@echo "  make run  - Build and run"
	@echo "  make clean - Remove build artifacts"