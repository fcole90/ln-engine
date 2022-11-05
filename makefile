clean:
	rm -rf ./bin

bin/dev:
	mkdir -p ./bin/dev

bin/dev/ln_engine: bin/dev
	clang++ -Wall -std=c++11 src/main.cpp -o bin/dev/ln_engine

build-dev: bin/dev/ln_engine

rebuild-dev: clean build-dev

run-dev: 
	./bin/dev/ln_engine

build-and-run-dev: build-dev run-dev

rebuild-and-run-dev: clean build-and-run-dev




