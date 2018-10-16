# PadBin
Takes an input file and padds it to an integer multiple of a given number of bytes.
This can be used to prepare a `.gba` binary for appending GBFS data (due to
the way GBFS is capable of finding its archives).

## Usage
Simply call `padbin` from your command prompt with the byte number and the
file to pad respectively. 
For example, padding `mapViewer.gba` to 256 bytes (as is required for GBFS)
would require the call: 
`padbin 256 mapViewer.gba`

## Development
The code for this project is very simple, and can be easily build by passing
the sources to your average C(++) compiler. For your convenience, a Makefile
has been included. Simply call `make` and you should have your `padbin` binary.

## Author
This tool is made by [Damian Yerrick](https://github.com/pinobatch).