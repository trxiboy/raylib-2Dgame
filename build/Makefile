SRC := $(wildcard ../src/*.cpp)
OBJ := $(SRC:.cpp=.o)

CXX := g++
CXXFLAGS := -O2 -Wall -Wno-missing-braces -I ../include/
LDFLAGS := -L ../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -mconsole

default: main.exe

main.exe: $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q ../src\*.o
	del /Q main.exe