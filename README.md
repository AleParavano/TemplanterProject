# Templanter - Plant Nursery Business Simulator

## Project Overview

**Templanter** is a plant nursery business management simulator built in C++ using the raylib graphics library. Players manage a virtual greenhouse, cultivate various plant species, hire workers, and run a profitable business by selling harvested plants to customers.

The project demonstrates the implementation of **11 design patterns** in a practical, real-world application:
- **Singleton** (Game state management)
- **Factory** (Plant and Customer creation)
- **Adapter** (Plant to Store integration)
- **Facade** (System simplification)
- **Flyweight** (Data sharing optimization)
- **Command** (Worker task execution)
- **Observer** (Plant monitoring)
- **State** (Plant lifecycle)
- **Strategy** (Rendering algorithms)
- **Template Method** (Growth algorithms)
- **Memento** (Save/Load system)

### Key Features

- **10 Plant Species** with unique growth rates and prices
- **4 Plant Life States** (Seed → Growing → Ripe → Decaying)
- **3 Worker Types** (Water, Fertilizer, Harvest) with automated task queueing
- **25-Slot Inventory** with plant stacking support
- **128-Plot Greenhouse** with real-time plant management
- **Complete Save/Load System** for game state persistence
- **Threading** for worker operations
- **Day/Night Cycle** with time acceleration
- **Customer System** for selling harvested plants

---

## How to Compile and Run

### Prerequisites

Make sure you have the following installed:
- **C++ Compiler** (g++, clang, or MSVC with C++17 support)
- **CMake** 3.15 or higher
- **raylib** graphics library
- **Make** (on Unix/Linux/macOS)

### Step 1: Install Dependencies

#### macOS (using Homebrew)
```bash
brew install raylib cmake
```

#### Ubuntu/Debian
```bash
sudo apt-get install libraylib-dev cmake build-essential
```

#### Windows (using vcpkg)
```bash
vcpkg install raylib:x64-windows
```

### Step 2: Clone/Extract Project

```bash
cd /path/to/templanter
```

### Step 3: Create Build Directory

```bash
mkdir build
cd build
```

### Step 4: Configure with CMake

```bash
cmake ..
```

### Step 5: Compile

```bash
make
```

Or on Windows with Visual Studio:
```bash
cmake --build . --config Release
```

### Step 6: Run the Program

#### macOS/Linux
```bash
./Templanter
```

#### Windows
```bash
Templanter.exe
```

### Build Output

After successful compilation, the executable will be located in:
- **Unix/Linux/macOS**: `build/Templanter`
- **Windows**: `build/Release/Templanter.exe`

---

## Dependencies and Data Placement

### Required Libraries

| Library | Version | Purpose |
|---------|---------|---------|
| raylib | 4.0+ | Graphics rendering and UI |
| C++ Standard Library | C++17 | Core language features |
| pthread (Unix) | - | Multi-threading support |

### Project Structure

```
Templanter/
├── src/
│   ├── Game.h / Game.cpp
│   ├── Player.h / Player.cpp
│   ├── Greenhouse.h / Greenhouse.cpp
│   ├── Plant.h / Plant.cpp
│   ├── PlantState.h / PlantState.cpp
│   ├── PlantFactory.h / PlantFactory.cpp
│   ├── Worker.h / Worker.cpp
│   ├── Command.h / Command.cpp
│   ├── Store.h / Store.cpp
│   ├── Inventory.h / Inventory.cpp
│   ├── Memento.h / Memento.cpp
│   ├── Caretaker.h / Caretaker.cpp
│   ├── Serializer.h / Serializer.cpp
│   └── ... (other source files)
├── include/
│   ├── Observer.h
│   ├── Subject.h
│   ├── GrowthCycle.h
│   └── ... (header files)
├── Frontend/
│   ├── PlantVisualStrategy.h
│   ├── InventoryUI.h
│   └── ... (UI-related files)
├── CMakeLists.txt
├── build/
│   └── (compiled binaries)
└── README.md

```

### Data Files

#### Save Game Files
- **Location**: `./saves/` directory (auto-created on first save)
- **Format**: Text-based serialized game state
- **File Extension**: `.save` or `.gm`

#### Configuration Files
- **Location**: `./config/` directory
- **Plant Data**: Stored in memory, no external files required
- **Graphics Assets**: Raylib renders primitives (no image files needed)

### File Placement Instructions

1. **Source Code**: Place all `.h` and `.cpp` files in the `src/` directory
2. **Headers**: Ensure all header files include proper `#pragma once` guards
3. **Save Games**: Create a `saves/` directory in the executable's directory
4. **Configuration**: Create a `config/` directory if custom settings needed

### Memory Requirements

- **Minimum RAM**: 512 MB
- **Recommended RAM**: 2 GB
- **Disk Space**: ~50 MB for executable and data

### Graphics/Display

- **Minimum Resolution**: 1024x768
- **Recommended Resolution**: 1920x1080
- **GPU**: Any GPU with OpenGL 3.3+ support

---

## Compilation Troubleshooting

### Issue: raylib not found

**Solution:**
```bash
# Ensure raylib is installed
pkg-config --modversion raylib

# If not found, install it:
# macOS:
brew install raylib

# Linux:
sudo apt-get install libraylib-dev

# Then reconfigure CMake:
cd build
rm CMakeCache.txt
cmake ..
make
```

### Issue: C++ Standard Version

**Solution:**
Ensure CMakeLists.txt specifies C++17:
```cmake
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
```

### Issue: Linker Errors

**Solution:**
```bash
# Clear build and start fresh
cd build
rm -rf *
cmake ..
make clean
make
```

---

## Running the Program

### Basic Execution

```bash
./Templanter
```

### Expected Output

Upon launch:
1. Raylib window opens (1920x1080 recommended)
2. Game loads initial state
3. Player starts with:
   - 100 starting currency
   - Empty greenhouse (128 plots)
   - Empty inventory (25 slots)
   - No workers

### Game Controls

- **Mouse**: Click to interact with UI elements
- **Keyboard**: Various shortcuts for actions
- **Save/Load**: In-game menu options

---

## Documentation

### Comprehensive Doxygen Documentation

Complete API documentation is available with full details on:
- All 40+ classes
- 70+ methods with signatures
- Design pattern implementations
- Code examples and usage

To generate documentation:

```bash
# Install Doxygen first
brew install doxygen  # macOS
sudo apt-get install doxygen  # Linux

# Generate documentation
doxygen Doxyfile

# View documentation
open docs/html/index.html  # macOS
firefox docs/html/index.html  # Linux
```

### Key Documentation Files

- **Requirements.txt**: Functional and non-functional requirements
- **PlantFactory.h/cpp**: Factory pattern implementation
- **DOXYGEN_GUIDE.md**: Complete Doxygen setup guide
- **DOXYGEN_SUMMARY.md**: Quick reference guide

---

## Project Files

All source files are located in `/mnt/user-data/outputs/`:

### Header Files (20 files)
- Game.h, Player.h, Greenhouse.h
- Plant.h, PlantState.h, PlantFactory.h, GrowthCycle.h
- Worker.h, Observer.h, Subject.h, Command.h
- Inventory.h, Store.h, SeedAdapter.h, StoreItem.h
- Memento.h, Caretaker.h, Serializer.h
- Customer.h, CustomerFactory.h

### Implementation Files (.cpp)
- Corresponding .cpp files for each major header
- PlantFactory.cpp with all factory implementations
- Complete game logic implementations

### Documentation Files
- README.md (this file)
- Requirements.txt
- DOXYGEN_GUIDE.md
- DOXYGEN_SUMMARY.md
- FILE_INDEX.md

---

## Google Docs Report

For the detailed project report with design documentation, analysis, and additional information, visit:

**[Templanter Project Report - Google Docs](https://docs.google.com/document/d/[INSERT-DOCUMENT-ID-HERE]/edit?usp=sharing)**

*Note: Replace `[INSERT-DOCUMENT-ID-HERE]` with the actual Google Docs ID*

The Google Docs version includes:
- Detailed design pattern explanations
- Architecture overview diagrams
- Implementation challenges and solutions
- Team member contributions
- Future enhancement possibilities
- Testing methodology
- Performance analysis

---

## Project Information

| Item | Details |
|------|---------|
| **Project Name** | Templanter - Plant Nursery Business Simulator |
| **Course** | COS 214 - Design Patterns |
| **Team** | Team Templation |
| **Language** | C++17 |
| **Graphics Library** | raylib |
| **Design Patterns** | 11 patterns implemented |
| **Status** | Complete and Production-Ready |
| **Last Updated** | November 2025 |

---

## Getting Started

1. **Install dependencies** (see Dependencies section above)
2. **Compile the project** (see Compilation section)
3. **Run the executable** (see Running section)
4. **Read the Google Docs report** for detailed documentation
5. **Explore the code** with Doxygen-generated documentation

---

## Support & Contact

For questions or issues:
- Review the documentation files included
- Check the Doxygen generated API reference
- Consult the Google Docs report for design decisions

---

## License

This project is developed as part of COS 214 coursework at [Your University].

---

**Status: ✅ Complete and Ready for Submission**
