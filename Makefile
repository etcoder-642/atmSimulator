CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
TARGET = bin/atm

# Updated to match your exact filenames in src/
SRCS = src/admin.cpp \
       src/Bank.cpp \
       src/display.cpp \
       src/utils.cpp \
       src/main.cpp \
       src/ticTacToe.cpp \
       src/Wallet.cpp

# This converts the .cpp list into a .o list
OBJS = $(SRCS:.cpp=.o)

all: dir $(TARGET)

# Creates the bin folder if it's missing
dir:
	mkdir -p bin

# Links the object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compiles each individual .cpp file into a .o file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleans up the project
clean:
	rm -f src/*.o
	rm -rf bin

clean:
	rm -f *.o virtualDisk