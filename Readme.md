# LN Engine

Custom Game Engine

## Requirements

- `build-essential`
- `clang`
- `sdl2`

### Ubuntu

You can install all the dependencies with

```sh
sudo apt install build-essential clang libsdl2-dev
```

Then, from the root, run:

```sh
make build-and-run-dev
```

Then, you can use the following to clean, rebuild and run:

```sh
make rebuild-and-run-dev
```

#### Linting and dev environment

You also need the following:

```sh
sudo apt install bear clangd
```

- `bear` is needed to produce the `compile_commands.json` file needed by `clang-tidy` for linting
- `clangd` is needed to enable the omonimous extension on VS Code.
