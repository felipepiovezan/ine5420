CC=g++
INCLUDES=src/
CFLAGS=-Wall -std=c++11
CPP_FILES=$(wildcard src/cg/*.cpp) $(wildcard src/ui/*.cpp)
OBJ_FILES=$(addprefix build/,$(subst src/,,$(CPP_FILES:.cpp=.o)))

build/cg/%.o: src/cg/%.cpp
	$(CC) -c $< -o $@ -I $(INCLUDES) $(CFLAGS)

build/ui/%.o: src/ui/%.cpp
	$(CC) -c $< -o $@ -I $(INCLUDES) $(CFLAGS) `pkg-config --cflags --libs gtkmm-3.0`

all: prepare $(OBJ_FILES)
	$(CC) $(OBJ_FILES) src/*.cpp -o cg -I $(INCLUDES) $(CFLAGS) `pkg-config --cflags --libs gtkmm-3.0`

prepare:
	mkdir -p build/cg
	mkdir -p build/ui

test:
	echo $(OBJ_FILES)
	echo "Nothing yet to do"

clean:
	rm *.o -f
	rm cg -f
	rm build/* -rf
