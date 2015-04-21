#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: task

# Tool invocations
# Executable "task" depends on the files main.o numbers.o and add.o.
task: bin/main.o bin/numbers.o bin/add.o
	gcc -m32 -g -Wall -o task bin/main.o bin/numbers.o bin/add.o

# Depends on the source and header files
bin/main.o: src/main.c
	gcc -g -Wall -m32 -ansi -c -o bin/main.o src/main.c 

bin/numbers.o: src/numbers.c
	gcc -g -Wall -m32 -ansi -c -o bin/numbers.o src/numbers.c  

bin/add.o: src/add.s
	nasm -g -f elf -w+all -o bin/add.o src/add.s

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f bin/*.o task