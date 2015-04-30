#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: dent

# Tool invocations
dent: bin/getdent.o 
	gcc -m32 -g -Wall -o dent bin/getdent.o

# Depends on the source and header files
bin/getdent.o: src/getdent.c
	gcc -g -Wall -m32 -ansi -c -o bin/getdent.o src/getdent.c 

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f bin/*.o dent