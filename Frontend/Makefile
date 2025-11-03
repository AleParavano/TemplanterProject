# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -w

# Detect OS
ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
    # Raylib installation path on Windows
    RAYLIB_PATH ?= C:/raylib
else
    DETECTED_OS := $(shell uname -s)
endif

# Platform-specific settings
ifeq ($(DETECTED_OS),Windows)
    # Windows (MinGW)
    INCLUDE_PATH = -I$(RAYLIB_PATH)/include
    LIB_PATH = -L$(RAYLIB_PATH)/lib
    LDFLAGS = $(LIB_PATH) -lraylib -lopengl32 -lgdi32 -lwinmm
    RM = del /Q /F
    RM_DIR = rmdir /S /Q
    EXECUTABLE = game.exe
    MKDIR = if not exist
    VALGRIND = 
else ifeq ($(DETECTED_OS),Darwin)
    # macOS
    INCLUDE_PATH = -I/usr/local/include -I/opt/homebrew/include
    LIB_PATH = -L/usr/local/lib -L/opt/homebrew/lib
    LDFLAGS = $(LIB_PATH) -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
    RM = rm -f
    RM_DIR = rm -rf
    EXECUTABLE = game
    MKDIR = mkdir -p
    VALGRIND = valgrind
else
    # Linux
    INCLUDE_PATH = -I/usr/local/include
    LIB_PATH = -L/usr/local/lib
    LDFLAGS = $(LIB_PATH) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    RM = rm -f
    RM_DIR = rm -rf
    EXECUTABLE = game
    MKDIR = mkdir -p
    VALGRIND = valgrind
endif

# Valgrind flags
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose
VALGRIND_SUPPRESSIONS = --suppressions=valgrind.supp

# Add include path to compiler flags
CXXFLAGS += $(INCLUDE_PATH)

# Debug build flags (for valgrind)
DEBUG_FLAGS = -g -O0

# Source files
SOURCES = demo_testing.cpp Scene.cpp StoreScene.cpp OutdoorScene.cpp GreenHouseScene.cpp ../Backend/Player.cpp ../Backend/Inventory.cpp ../Backend/Worker.cpp ../Backend/Greenhouse.cpp ../Backend/Memento.cpp ../Backend/Plant.cpp ../Backend/Caretaker.cpp ../Backend/Command.cpp ../Backend/Customer.cpp ../Backend/CustomerFactory.cpp SceneManager.cpp ../Backend/Game.cpp ../Backend/GrowthCycle.cpp ../Backend/Observer.cpp ../Backend/PlantState.cpp ../Backend/SeedAdapter.cpp ../Backend/Store.cpp ../Backend/Subject.cpp InventoryUI.cpp Demo.cpp CustomerFlyweight.cpp UI.cpp ../Backend/Serializer.cpp WarehouseScene.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = Scene.h StoreScene.h OutdoorScene.h GreenHouseScene.h ../Backend/Player.h ../Backend/Inventory.h ../Backend/Worker.h ../Backend/Greenhouse.h ../Backend/Memento.h ../Backend/Plant.h ../Backend/Caretaker.h ../Backend/Command.h ../Backend/Customer.h ../Backend/CustomerFactory.h SceneManager.h ../Backend/Game.h ../Backend/GrowthCycle.h ../Backend/Observer.h ../Backend/PlantState.h ../Backend/PlantFactory.h ../Backend/SeedAdapter.h ../Backend/Store.h ../Backend/Subject.h Slot.h CustomerVisual.h CustomerManager.h InventoryUI.h Demo.h CustomerFlyweight.h ObjectTypes.h PlantVisualStrategy.h UI.h ../Backend/Serializer.h WarehouseScene.h

# Target executable
TARGET = $(EXECUTABLE)
DEBUG_TARGET = $(EXECUTABLE)_debug

# Default target
all: $(TARGET)
	@echo "Build complete! Run '$(TARGET)' to play."

# Link object files to create executable
$(TARGET): $(OBJECTS)
	@echo "Linking..."
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Debug build for valgrind
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: clean $(TARGET)
	@echo "Debug build complete! Use 'make valgrind' to run with valgrind."

# Clean build files
clean:
	@echo "Cleaning..."
ifeq ($(DETECTED_OS),Windows)
	-@for %%f in ($(OBJECTS)) do if exist "%%f" del /Q "%%f"
	-@if exist "$(TARGET)" del /Q "$(TARGET)"
	-@if exist "$(DEBUG_TARGET)" del /Q "$(DEBUG_TARGET)"
else
	-@$(RM) $(OBJECTS) $(TARGET) $(DEBUG_TARGET)
endif
	@echo "Clean complete!"


# Run the game
run: $(TARGET)
	@echo "Starting game..."
	./$(TARGET)

# Run with valgrind (memory leak detection)
valgrind: debug
ifeq ($(DETECTED_OS),Windows)
	@echo "Valgrind is not available on Windows."
	@echo "Consider using WSL (Windows Subsystem for Linux) or a Linux VM."
else
	@echo "Running with valgrind..."
	@echo "Note: This will be slow. Press Ctrl+C to stop."
	@if [ -f valgrind.supp ]; then \
		$(VALGRIND) $(VALGRIND_FLAGS) $(VALGRIND_SUPPRESSIONS) ./$(TARGET); \
	else \
		$(VALGRIND) $(VALGRIND_FLAGS) ./$(TARGET); \
	fi
endif

# Run with valgrind and save output to file
valgrind-log: debug
ifeq ($(DETECTED_OS),Windows)
	@echo "Valgrind is not available on Windows."
else
	@echo "Running with valgrind and saving to valgrind.log..."
	@if [ -f valgrind.supp ]; then \
		$(VALGRIND) $(VALGRIND_FLAGS) $(VALGRIND_SUPPRESSIONS) --log-file=valgrind.log ./$(TARGET); \
	else \
		$(VALGRIND) $(VALGRIND_FLAGS) --log-file=valgrind.log ./$(TARGET); \
	fi
	@echo "Output saved to valgrind.log"
endif

# Quick memory check (less verbose)
memcheck: debug
ifeq ($(DETECTED_OS),Windows)
	@echo "Valgrind is not available on Windows."
else
	@echo "Running quick memory check..."
	$(VALGRIND) --leak-check=yes --error-exitcode=1 ./$(TARGET)
endif

# Generate valgrind suppressions file
valgrind-gen-suppressions: debug
ifeq ($(DETECTED_OS),Windows)
	@echo "Valgrind is not available on Windows."
else
	@echo "Generating suppressions (press Ctrl+C when done)..."
	$(VALGRIND) --leak-check=full --show-leak-kinds=all --gen-suppressions=all ./$(TARGET) 2>&1 | tee valgrind_suppressions.txt
	@echo "Review valgrind_suppressions.txt and add relevant sections to valgrind.supp"
endif

# Rebuild from scratch
rebuild: clean all

# Check if raylib is installed properly
check:
	@echo "========================================="
	@echo "Checking raylib installation..."
	@echo "========================================="
	@echo "Detected OS: $(DETECTED_OS)"
	@echo "Compiler: $(CXX)"
	@echo "Raylib path: $(RAYLIB_PATH)"
	@echo "Include path: $(INCLUDE_PATH)"
	@echo "Library path: $(LIB_PATH)"
	@echo ""
ifeq ($(DETECTED_OS),Windows)
	@echo "Checking for raylib.h..."
	@if exist "$(RAYLIB_PATH)\include\raylib.h" (echo ✓ Found raylib.h) else (echo ✗ raylib.h NOT FOUND)
	@echo ""
	@echo "Checking for libraylib.a..."
	@if exist "$(RAYLIB_PATH)\lib\libraylib.a" (echo ✓ Found libraylib.a) else (echo ✗ libraylib.a NOT FOUND)
	@echo ""
	@echo "If files are not found, you need to:"
	@echo "1. Download raylib from: https://github.com/raysan5/raylib/releases"
	@echo "2. Extract to C:\raylib\"
	@echo "3. Or set RAYLIB_PATH in this Makefile to your raylib location"
	@echo ""
	@echo "Note: Valgrind is not available on Windows."
else
	@echo "Try running: pkg-config --cflags --libs raylib"
	@echo ""
	@echo "Checking for valgrind..."
	@which $(VALGRIND) > /dev/null 2>&1 && echo "✓ valgrind found" || echo "✗ valgrind NOT FOUND (install with: sudo apt install valgrind)"
endif
	@echo "========================================="

# Show detailed info
info:
	@echo "Build Configuration:"
	@echo "  OS: $(DETECTED_OS)"
	@echo "  Compiler: $(CXX)"
	@echo "  Flags: $(CXXFLAGS)"
	@echo "  Libraries: $(LDFLAGS)"
	@echo "  Target: $(TARGET)"
	@echo "  Sources: $(SOURCES)"

# Help
help:
	@echo "Available targets:"
	@echo "  make               - Build the game"
	@echo "  make run           - Build and run the game"
	@echo "  make debug         - Build with debug symbols for valgrind"
	@echo "  make valgrind      - Run with valgrind (full leak check)"
	@echo "  make valgrind-log  - Run valgrind and save output to file"
	@echo "  make memcheck      - Quick memory leak check"
	@echo "  make valgrind-gen-suppressions - Generate suppressions for false positives"
	@echo "  make clean         - Remove build files"
	@echo "  make rebuild       - Clean and build"
	@echo "  make check         - Check raylib and valgrind installation"
	@echo "  make info          - Show build configuration"
	@echo "  make help          - Show this help"

.PHONY: all clean run rebuild check info help debug valgrind valgrind-log memcheck valgrind-gen-suppressions