CC=g++
INCLUDES=include/
CFLAGS=-Wall -std=c++11 -O3
CPP_FILES=$(wildcard lib/cg/*.cpp) $(wildcard lib/ui/*.cpp)  $(wildcard lib/utils/*.cpp)
OBJ_FILES=$(addprefix build/,$(subst lib/,,$(CPP_FILES:.cpp=.o)))

build/ui/%.o: lib/ui/%.cpp include/ui/%.h
	$(CC) -c $< -o $@ -I $(INCLUDES) $(CFLAGS) `pkg-config --cflags --libs gtkmm-3.0`

build/%.o: lib/%.cpp include/%.h
	$(CC) -c $< -o $@ -I $(INCLUDES) $(CFLAGS)

build/%.o: lib/%.cpp
	$(CC) -c $< -o $@ -I $(INCLUDES) $(CFLAGS)

all: prepare $(OBJ_FILES)
	$(CC) $(OBJ_FILES) lib/*.cpp -o cg -I $(INCLUDES) $(CFLAGS) `pkg-config --cflags --libs gtkmm-3.0`

prepare:
	mkdir -p build/cg
	mkdir -p build/ui
	mkdir -p build/utils

clean:
	rm cg -f
	rm build/* -rf
