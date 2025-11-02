# ============================
# TEMPLANTER Project Makefile 
# Compiles Frontend and Backend together
# ============================

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
              ../Backend/Worker.cpp

# Combined source files
ALL_SRC = $(FRONTEND_SRC) $(BACKEND_SRC)

# Object files
OBJECTS = $(ALL_SRC:.cpp=.o)

# Default target
all: $(TARGET)

# Build executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(RAYLIB_INCLUDE) $(RAYLIB_LIB) $(RAYLIB_LIBS)
	@echo "✓ Build successful! Run with: .\\$(TARGET)"

# Compile backend files
Backend/%.o: Backend/%.cpp
	$(CXX) $(CXXFLAGS) $(RAYLIB_INCLUDE) -c $< -o $@

# Compile frontend files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(RAYLIB_INCLUDE) -c $< -o $@

# Clean build artifacts
clean:
ifeq ($(OS),Windows_NT)
	cmd /C "del /Q *.o 2>nul & del /Q Backend\\*.o 2>nul & del /Q $(TARGET) 2>nul"
else
	rm -f *.o ../Backend/*.o $(TARGET)
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
