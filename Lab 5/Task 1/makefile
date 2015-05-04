#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: task

# Tool invocations
task: bin/task1a.o 
	gcc -m32 -g -Wall -o task bin/task1a.o bin/LineParser.o
# Depends on the source and header files
bin/task1a.o: src/task1a.c
	gcc -g -Wall -m32 -ansi -c -o bin/task1a.o src/task1a.c 

bin/LineParser.o: src/LineParser.c
	gcc -g -Wall -m32 -ansi -c -o bin/LineParser.o src/LineParser.c 
	
#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f bin/*.o task