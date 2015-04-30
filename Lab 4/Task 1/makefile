#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: task1

# Tool invocations
# Executable "task" depends on the files main.o numbers.o and add.o.
task1: bin/main.o bin/start.o bin/util.o
	ld -melf_i386 bin/start.o bin/main.o bin/util.o -o task1
	
# Depends on the source and header files
bin/main.o: src/main.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector src/main.c -o bin/main.o

bin/util.o: src/util.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector src/util.c -o bin/util.o

bin/start.o: src/start.s
	nasm -f elf src/start.s -o bin/start.o

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f bin/*.o task1