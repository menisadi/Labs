#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: task

# Tool invocations
task: bin/1c.o 
	gcc -m32 -g -Wall -o task bin/1c.o
# Depends on the source and header files
bin/1c.o: src/1c.c
	gcc -g -Wall -m32 -ansi -c -o bin/1c.o src/1c.c 

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f bin/*.o task