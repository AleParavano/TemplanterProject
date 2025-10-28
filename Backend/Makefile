CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -g -fsanitize=address -pthread 
LDFLAGS = -fsanitize=address -pthread

# Source files
SRC = PlantState.cpp \
      Plant.cpp \
	  Observer.cpp \
      Greenhouse.cpp \
      Worker.cpp \
      Inventory.cpp \
      Memento.cpp \
      Caretaker.cpp \
      Player.cpp \
      Game.cpp \
      plant_state_demo.cpp

# Object files (replace .cpp with .o)
OBJ = $(SRC:.cpp=.o)

# Executable name
EXEC = plant_state_demo

# Default target
all: $(EXEC)

# Link object files to create executable
$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ)

# Compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJ) $(EXEC)

# Rebuild everything
rebuild: clean all

# Run the demo
run: $(EXEC)
	./$(EXEC)

# Phony targets
.PHONY: all clean rebuild run

# Dependencies (optional but recommended)
PlantState.o: PlantState.cpp PlantState.h Plant.h
Plant.o: Plant.cpp Plant.h PlantState.h Subject.h Observer.h GrowthCycle.h
Greenhouse.o: Greenhouse.cpp Greenhouse.h Plant.h
Worker.o: Worker.cpp Worker.h Observer.h Command.h Plant.h
Inventory.o: Inventory.cpp Inventory.h Plant.h
Memento.o: Memento.cpp Memento.h Inventory.h Worker.h Greenhouse.h
Caretaker.o: Caretaker.cpp Caretaker.h Memento.h
Player.o: Player.cpp Player.h Inventory.h Worker.h Greenhouse.h Memento.h
Game.o: Game.cpp Game.h Player.h
plant_state_demo.o: plant_state_demo.cpp Game.h Plant.h Greenhouse.h