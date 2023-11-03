# Compiler settings
CXX = g++
CXXFLAGS = -O2 -std=c++17 -Wall
# DEBUGFLAG = -DDEBUG
 

# Source files
CPP_SOURCES = driver.cpp DeadCodeRemoval.cpp file2.cpp Structure.cpp
OBJECTS = $(CPP_SOURCES:.cpp=.o) 

# Final target
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) 

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DEBUGFLAG) -c $< -o $@


clean:
	# rm -f $(OBJECTS) $(TARGET)
	rm -f $(OBJECTS) $(TARGET)

debug: CXXFLAGS += $(DEBUGFLAG)
debug: all

.PHONY: all clean debug
