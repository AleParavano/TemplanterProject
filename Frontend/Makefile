# Compiler and flags
CXX = g++
CXXFLAGS = -O2 -std=c++17
RAYLIB_INCLUDE = -IC:\raylib\include
RAYLIB_LIB = -LC:\raylib\lib
RAYLIB_LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

# Output
TARGET = templanter.exe

# Frontend Source Files
FRONTEND_SRC = main.cpp \
               OutdoorScene.cpp \
               GreenHouseScene.cpp \
               StoreScene.cpp \
               WarehouseScene.cpp \
               SceneManger.cpp \
               UI.cpp

# Backend Source Files (from Backend folder)
BACKEND_SRC = ../Backend/Caretaker.cpp \
              ../Backend/Command.cpp \
              ../Backend/Customer.cpp \
              ../Backend/CustomerFactory.cpp \
              ../Backend/Game.cpp \
              ../Backend/Greenhouse.cpp \
              ../Backend/GrowthCycle.cpp \
              ../Backend/Inventory.cpp \
              ../Backend/Memento.cpp \
              ../Backend/Observer.cpp \
              ../Backend/Plant.cpp \
              ../Backend/PlantState.cpp \
              ../Backend/Player.cpp \
              ../Backend/SeedAdapter.cpp \
              ../Backend/Store.cpp \
              ../Backend/Subject.cpp \
              ../Backend/Worker.cpp \
              ../Backend/Serializer.cpp  # Includes the Serializer

# Combined source files
ALL_SRC = $(FRONTEND_SRC) $(BACKEND_SRC)

# Object files
# Generates object file names like: main.o, ../Backend/Caretaker.o, etc.
OBJECTS = $(ALL_SRC:.cpp=.o)

# Default target
all: $(TARGET)

# Build executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(RAYLIB_INCLUDE) $(RAYLIB_LIB) $(RAYLIB_LIBS)
	@echo "✓ Build successful! Run with: .\\$(TARGET)"

# Compile backend files
# Pattern rule to compile source files located one directory up (../Backend/%.cpp) 
# and place the object files in that same relative path (../Backend/%.o).
../Backend/%.o: ../Backend/%.cpp
	$(CXX) $(CXXFLAGS) $(RAYLIB_INCLUDE) -c $< -o $@

# Compile frontend files
# Places object files in the current directory (Frontend).
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(RAYLIB_INCLUDE) -c $< -o $@

# Clean build artifacts
clean:
ifeq ($(OS),Windows_NT)
	cmd /C "del /Q *.o 2>nul & del /Q ..\Backend\*.o 2>nul & del /Q $(TARGET) 2>nul"
else
	# POSIX/MinGW command (rm -f) uses forward slashes.
	# Deletes object files in the current directory and the Backend subdirectory.
	rm -f *.o $(TARGET)
	rm -f ../Backend/*.o
endif
	@echo "Clean complete!"

# Full rebuild
rebuild: clean all

# Run the project
run: $(TARGET)
	.\$(TARGET)

# Help
help:
	@echo "TEMPLANTER Makefile Commands:"
	@echo "  make          - Build the project"
	@echo "  make rebuild  - Clean and rebuild"
	@echo "  make clean    - Remove build artifacts"
	@echo "  make run      - Build and run the project"
	@echo "  make help     - Show this help message"

.PHONY: all clean rebuild run help