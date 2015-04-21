#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: task

# Tool invocations
task: bin/hexaPrint.o 
	gcc -m32 -g -Wall -o task bin/hexaPrint.o
# Depends on the source and header files
bin/hexaPrint.o: src/hexaPrint.c
	gcc -g -Wall -m32 -ansi -c -o bin/hexaPrint.o src/hexaPrint.c 

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f bin/*.o task