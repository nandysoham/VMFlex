# Compiler settings
CXX = g++
CXXFLAGS = -O2 -std=c++17 -Wall
# DEBUGFLAG = -DDEBUG
 

# Source files
CPP_SOURCES = driver.cpp DeadCodeRemoval.cpp registerAllocator.cpp codeGenerator.cpp codeGenHelper.cpp Structure.cpp
OBJECTS = $(CPP_SOURCES:.cpp=.o) 

# Final target
TARGET = main
	


all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) ../CompFlex/helper.o ../CompFlex/this.o ../CompFlex/lex.yy.o ../CompFlex/gm.cc   $(OBJECTS) 

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DEBUGFLAG) -c $< -o $@

pre:
	cd ../CompFlex && make all
	cp ../CompFlex/code.txt code.tac


clean:
	# rm -f $(OBJECTS) $(TARGET)
	rm -f $(OBJECTS) $(TARGET)
	cd ../CompFlex && make clean

debug: CXXFLAGS += $(DEBUGFLAG)
debug: all

.PHONY: all clean debug
