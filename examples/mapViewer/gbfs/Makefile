# Builds the required gbfs tools

build : gbfs padbin

gbfs : gbfs.h gbfs.c
	gcc -Wall -O2 gbfs.c -o gbfs

padbin : padbin.c
	gcc -Wall -O2 padbin.c -o padbin

clean :
	@rm -fv gbfs
	@rm -fv padbin

#EOF
