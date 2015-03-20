CC=g++
INCLUDES=include/
CFLAGS=-Wall -std=c++11 -O2
CPP_FILES=$(wildcard lib/cg/*.cpp) $(wildcard lib/ui/*.cpp)
OBJ_FILES=$(addprefix build/,$(subst lib/,,$(CPP_FILES:.cpp=.o)))

build/cg/%.o: lib/cg/%.cpp
	$(CC) -c $< -o $@ -I $(INCLUDES) $(CFLAGS)

build/ui/%.o: lib/ui/%.cpp
	$(CC) -c $< -o $@ -I $(INCLUDES) $(CFLAGS) `pkg-config --cflags --libs gtkmm-3.0`

all: prepare $(OBJ_FILES)
	$(CC) $(OBJ_FILES) lib/*.cpp -o cg -I $(INCLUDES) $(CFLAGS) `pkg-config --cflags --libs gtkmm-3.0`

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
