# Tiled2GBA

Simple CLI for converting [Tiled](https://www.mapeditor.org) maps to data the **G**ame **B**oy **A**dvance understands.
Special thanks to [Jasper Vijn](https://www.coranac.com) for providing a great tutorial on GBA development!

## Releases
You can download binary releases [here](https://github.com/LucvandenBrand/Tiled2GBA/releases).

## Usage
Tiled2GBA can generate both compilable C code and appendable binary data. 
The latter is recommended (no need to recompile your project for changes in assets), 
and can be used with [GBFS](http://www.pineight.com/gba/#gbfs) in order to access it (see the example).

### Generating C code
Simply call `Tiled2GBA` from your command prompt, and provide a `map.tmx` and `map.c map.h` as
input and output parameters respectively. 
For example, `Tiled2GBA assets/map.tmx src/map.c src/map.h` would output compilable C code
into the `src` folder.

### Generating binary data
Simply call `Tiled2GBA` from your command prompt, and provide a `map.tmx` and `map.bin` as
input and output parameters respectively. 
For example, `Tiled2GBA assets/map.tmx assets/map.bin` would output appendable binary data
into the `assets` folder.

You can use the `--help` command for more information.

## Development
This project is written in C++ and contains a very simple Makefile to help you compile it.

### Contributing
Contributions are always welcome! You can make a contribution by:

1. Creating an issue, be sure your contribution has not been claimed by somebody else!
2. Forking the project.
3. Creating a pull-request to merge your solution back into the **develop** branch of this repository.

The **develop** branch is meant for in-development unstable releases, 
whilst the **master** branch is meant for stable production-ready releases.

### Licence
All source files are protected under the MIT Licence, except for the included libraries in `lib`.
The used libraries are open-source, but please read their included licenses for their specific
terms and conditions.