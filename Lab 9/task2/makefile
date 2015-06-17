#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: dirs bin/main 

# Tool invocations
bin/main: lib/main.o
	ld  -o bin/main lib/main.o start.o -L/usr/lib32 -lc -T linking_script -dynamic-linker /lib32/ld-linux.so.2

# Depends on the source and header files
lib/main.o: main.c 
	gcc -m32 -g -Wall -ansi -c -o lib/main.o main.c


#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f lib/* bin/*

dirs: 
	mkdir -p bin lib 
	
	
