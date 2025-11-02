# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -w

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
else ifeq ($(DETECTED_OS),Darwin)
    # macOS
    INCLUDE_PATH = -I/usr/local/include -I/opt/homebrew/include
    LIB_PATH = -L/usr/local/lib -L/opt/homebrew/lib
    LDFLAGS = $(LIB_PATH) -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
    RM = rm -f
    RM_DIR = rm -rf
    EXECUTABLE = game
    MKDIR = mkdir -p
else
    # Linux
    INCLUDE_PATH = -I/usr/local/include
    LIB_PATH = -L/usr/local/lib
    LDFLAGS = $(LIB_PATH) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    RM = rm -f
    RM_DIR = rm -rf
    EXECUTABLE = game
    MKDIR = mkdir -p
endif

# Add include path to compiler flags
CXXFLAGS += $(INCLUDE_PATH)

# Source files
SOURCES = demo_testing.cpp Scene.cpp StoreScene.cpp OutdoorScene.cpp GreenHouseScene.cpp ../Backend/Player.cpp ../Backend/Inventory.cpp ../Backend/Worker.cpp ../Backend/Greenhouse.cpp ../Backend/Memento.cpp ../Backend/Plant.cpp ../Backend/Caretaker.cpp ../Backend/Command.cpp ../Backend/Customer.cpp ../Backend/CustomerFactory.cpp ../Backend/Game.cpp ../Backend/GrowthCycle.cpp ../Backend/Observer.cpp ../Backend/PlantState.cpp ../Backend/SeedAdapter.cpp ../Backend/Store.cpp ../Backend/Subject.cpp InventoryUI.cpp Demo.cpp CustomerFlyweight.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = Scene.cpp StoreScene.h OutdoorScene.h GreenHouseScene.h ../Backend/Player.h ../Backend/Inventory.h ../Backend/Worker.h ../Backend/Greenhouse.h ../Backend/Memento.h ../Backend/Plant.h ../Backend/Caretaker.cpp ../Backend/Command.cpp ../Backend/Customer.h ../Backend/CustomerFactory.h ../Backend/Game.h ../Backend/GrowthCycle.h ../Backend/Observer.h ../Backend/PlantState.h ../Backend/PlantFactory.h ../Backend/SeedAdapter.h ../Backend/Store.h ../Backend/Subject.h Slot.h CustomerVisual.h CustomerManager.h InventoryUI.h Demo.h CustomerFlyweight.h

# Target executable
TARGET = $(EXECUTABLE)

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

# Clean build files
clean:
	@echo "Cleaning..."
ifeq ($(DETECTED_OS),Windows)
	-@for %%f in ($(OBJECTS)) do if exist "%%f" del /Q "%%f"
	-@if exist "$(TARGET)" del /Q "$(TARGET)"
else
	-@$(RM) $(OBJECTS) $(TARGET)
endif
	@echo "Clean complete!"


# Run the game
run: $(TARGET)
	@echo "Starting game..."
	./$(TARGET)

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
	@if exist "$(RAYLIB_PATH)\include\raylib.h" (echo ✓ Found raylib.h) else (echo ≡ƒö¿ raylib.h NOT FOUND)
	@echo ""
	@echo "Checking for libraylib.a..."
	@if exist "$(RAYLIB_PATH)\lib\libraylib.a" (echo ✓ Found libraylib.a) else (echo ≡ƒö¿ libraylib.a NOT FOUND)
	@echo ""
	@echo "If files are not found, you need to:"
	@echo "1. Download raylib from: https://github.com/raysan5/raylib/releases"
	@echo "2. Extract to C:\raylib\"
	@echo "3. Or set RAYLIB_PATH in this Makefile to your raylib location"
else
	@echo "Try running: pkg-config --cflags --libs raylib"
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
	@echo "  make          - Build the game"
	@echo "  make run      - Build and run the game"
	@echo "  make clean    - Remove build files"
	@echo "  make rebuild  - Clean and build"
	@echo "  make check    - Check raylib installation"
	@echo "  make info     - Show build configuration"
	@echo "  make help     - Show this help"

.PHONY: all clean run rebuild check info help