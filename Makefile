.PHONY: all format clean run

COMPILE_OPTIONS=-Wall -Werror

#directories
OBJ=obj
SRC=src

#sources
SOURCES=$(shell find $(SRC)/ -type f -name '*.cpp')

#objects
OBJECTS=$(addprefix $(OBJ)/, $(patsubst %.cpp, %.o, $(SOURCES)))

all: format bin/hangman

bin/hangman: $(OBJECTS)
	$(CXX) $(COMPILE_OPTIONS) $^ -o $@

obj/src/%.o: src/%.cpp
	$(CXX) $(COMPILEFLAGS) -I src -c $< -o $@

format:
	find . -type f -name '*.cpp' -o -name '*.h' | xargs clang-format -i

clean:
	cd obj && find . ! -name '.keep' -type f | xargs rm -f
	cd obj && find . -type d -empty | xargs rm -f
	cd bin && find . ! -name '.keep' -type f | xargs rm -f
	cd bin && find . -type d -empty | xargs rm -f

run:
	cd bin && ./hangman