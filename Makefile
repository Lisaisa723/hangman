.PHONY: all format clean run test

COMPILE_OPTIONS=-Wall -Werror

#directories
OBJ=obj
SRC=src
TEST=test

#sources
SOURCES=$(shell find $(SRC)/ -type f -name '*.cpp')
TEST_SOURCES=$(shell find $(TEST)/ -type f -name '*.cpp')

#objects
OBJECTS=$(addprefix $(OBJ)/, $(patsubst %.cpp, %.o, $(SOURCES)))
TEST_OBJECTS=$(addprefix $(OBJ)/, $(patsubst %.cpp, %.o, $(TEST_SOURCES)))

all: format bin/hangman bin/test_hangman

#application
bin/hangman: $(OBJECTS)
	$(CXX) $(COMPILE_OPTIONS) $^ -o $@

obj/src/%.o: src/%.cpp
	$(CXX) $(COMPILEFLAGS) -I src -c $< -o $@

#test
bin/test_hangman: $(TEST_OBJECTS)
	$(CXX) $(COMPILEFLAGS) $^ -o $@

obj/test/%.o: test/%.cpp
	$(CXX) $(COMPILEFLAGS) -I src -I thirdparty -c $< -o $@

format:
	find . -type f -name '*.cpp' -o -name '*.h' | xargs clang-format -i

clean:
	cd obj && find . ! -name '.keep' -type f | xargs rm -f
	cd obj && find . -type d -empty | xargs rm -f
	cd bin && find . ! -name '.keep' -type f | xargs rm -f
	cd bin && find . -type d -empty | xargs rm -f

run:
	cd bin && ./hangman

test:
	cd bin && ./test_hangman