#OBJS specifies which files to compile as part of the project
OBJS = src/main.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = ln_engine

clean:
	rm -rf ./bin

bin/dev:
	mkdir -p ./bin/dev

bin/dev/ln_engine: bin/dev
	clang++ -Wall -std=c++11 $(OBJS) -lSDL2 -o bin/dev/$(OBJ_NAME)

build-dev: bin/dev/ln_engine

rebuild-dev: clean build-dev

run-dev: 
	./bin/dev/ln_engine

build-and-run-dev: build-dev run-dev

rebuild-and-run-dev: clean build-and-run-dev




