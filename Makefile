# Compiler & Flags
CXX = g++
CXXFLAGS = -Wall -Wextra -fdiagnostics-color=always -g -std=c++17 -I./include

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = build
BIN_DIR = .

# Target & Source Files
TARGET = $(BIN_DIR)/program.exe
ROOT_SOURCES = main.cpp
SRC_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
ALL_SOURCES = $(ROOT_SOURCES) $(SRC_SOURCES)
HEADERS = $(wildcard $(INC_DIR)/*.h)

# Object files
ROOT_OBJECTS = $(addprefix $(OBJ_DIR)/,$(ROOT_SOURCES:.cpp=.o))
SRC_OBJECTS = $(addprefix $(OBJ_DIR)/,$(notdir $(SRC_SOURCES:.cpp=.o)))
ALL_OBJECTS = $(ROOT_OBJECTS) $(SRC_OBJECTS)

.PHONY: all run clean help

all: $(TARGET)

$(TARGET): $(ALL_OBJECTS) | $(BIN_DIR) $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(ALL_OBJECTS) -o $(TARGET)

$(OBJ_DIR)/main.o: main.cpp $(HEADERS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) | $(OBJ_DIR)
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
	@echo "  make run  - Build and run the project"
	@echo "  make clean - Remove build artifacts"
	@echo "  make run  - Build and run"
	@echo "  make clean - Remove build artifacts"