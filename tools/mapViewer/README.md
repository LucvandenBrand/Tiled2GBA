# MapViewer

This simple GBA project allows for viewing your converted Tiled maps.

## Usage

Once compiled, simply open the GBA binary using the emulator of your choosing. 
The directional pad of the GBA allows you to scroll through the map.

## Development
The code for this project **requires DevkitARM to be installed**, and a global `DEVKITARM`
environment variable to be defined describing its directory.

This project includes a Makefile, which allows you to build the required binaries.
The `make` command will build a `mapViewer.gba`, which uses generated code stored in `src\asset`
as map data.

Alternatively, you can use `padbin` and `gbfs` to append binary map data to the compiled `gba` binary.
In this case it will display the appended map instead.