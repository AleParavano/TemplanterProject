# Makefile for Plant State System Project (Flat Structure)

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
LDFLAGS = -pthread

# Source files (all .cpp files in current directory)
SOURCES = Plant.cpp PlantState.cpp GrowthCycle.cpp Player.cpp Game.cpp Greenhouse.cpp Memento.cpp Inventory.cpp Observer.cpp Worker.cpp Subject.cpp Store.cpp SeedAdapter.cpp plant_inv-store_demo.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Output executable
TARGET = plant_demo

# Default target
all: $(TARGET)

# Link executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "✓ Build complete: $(TARGET)"

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	@./$(TARGET)

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "✓ Cleaned build artifacts"

# Clean and rebuild
rebuild: clean all

# Show help
help:
	@echo "Available targets:"
	@echo "  make all       - Build the project (default)"
	@echo "  make run       - Build and run the program"
	@echo "  make clean     - Remove build artifacts"
	@echo "  make rebuild   - Clean and rebuild"
	@echo "  make help      - Show this help message"

# Phony targets
.PHONY: all run clean rebuild help