#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: task

# Tool invocations
task: bin/count-words.o 
	gcc -m32 -g -Wall -o task bin/count-words.o
# Depends on the source and header files
bin/count-words.o: src/count-words.c
	gcc -g -Wall -m32 -ansi -c -o bin/count-words.o src/count-words.c 

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f bin/*.o task