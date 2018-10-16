# GBFS
Takes an input file and packages it as a GBFS archive.
A GBFS archive can be appended to a (padded) `.gba` binary, such that it
can easily find your archived content and use it.

## Usage
Simply call `gbfs` from your command prompt with the archive and input file(s)
respectively. For example, archiving two Tiled2GBA generated maps would require the call: 
`gbfs mapdata.gbfs map1.bin map2.bin`

## Development
The code for this project is very simple, and can be easily build by passing
the sources to your average C(++) compiler. For your convenience, a Makefile
has been included. Simply call `make` and you should have your `gbfs` binary.

## Author
This tool is made by [Damian Yerrick](https://github.com/pinobatch).