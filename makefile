# Source files
SRC_FILES := $(shell find ./src/**/*.cpp -printf "%p ")

# Target executable name
TARGET_NAME = ln_engine

# Compiler
CC = clang++

#Compiler Flags
COMPILER_FLAGS = -Wall -std=c++20

# Linker Flags
LINKER_FLAGS = -lSDL2

clean:
	rm -rf ./bin

bin/dev:
	mkdir -p ./bin/dev

bin/dev/ln_engine: bin/dev
	$(CC) $(COMPILER_FLAGS) $(SRC_FILES) $(LINKER_FLAGS) -o bin/dev/$(TARGET_NAME)

build-dev: bin/dev/$(TARGET_NAME)

rebuild-dev: clean build-dev

run-dev: 
	./bin/dev/$(TARGET_NAME)

build-and-run-dev: build-dev run-dev

rebuild-and-run-dev: clean build-and-run-dev

# Code generation
generate_colors:
	python3 scripts/generate_css_colors.py

# --- Linting ---
# Generates a compile commands file from recording a make execution.
compile_commands.json:
	make lint-update-compile-commands

lint-update-compile-commands:
	make clean; bear --config bear.json -- make build-dev

lint: compile_commands.json
	clang-tidy -header-filter=.* $(SRC_FILES)

lint-fix: compile_commands.json
	clang-tidy -fix-errors -header-filter=.* $(SRC_FILES)


# Web Assembly Test
bin/web:
	mkdir -p ./bin/web

build-web: bin/web
	em++ $(COMPILER_FLAGS) $(SRC_FILES) -s USE_SDL=2 -o bin/web/index.html

run-web:
	emrun ./bin/web/index.html

build-and-run-web: build-web run-web

rebuild-and-run-web: clean build-and-run-web
