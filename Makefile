# COMPILER & FLAGS
CXX = g++
CXXFLAGS = -fdiagnostics-color=always -g
LDFLAGS = 

# TARGET & SOURCE FILES 
TARGET = project.exe
SOURCES = main.cpp classes.cpp
HEADERS = classes.h
OBJECTS = $(SOURCES:.cpp=.o)

# BUILD RULES
$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@


.PHONY: clean run all

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

help:
	@echo "Available targets:"
	@echo "  make      - Build the project"
	@echo "  make run  - Build and run"
	@echo "  make clean - Remove build artifacts"