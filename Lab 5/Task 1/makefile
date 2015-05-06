#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: myshell

# Tool invocations
myshell: bin/myshell.o bin/LineParser.o
	gcc -m32 -g -Wall -o myshell bin/myshell.o bin/LineParser.o
# Depends on the source and header files
bin/myshell.o: src/myshell.c
	gcc -g -Wall -m32 -ansi -c -o bin/myshell.o src/myshell.c 

bin/LineParser.o: src/LineParser.c
	gcc -g -Wall -m32 -ansi -c -o bin/LineParser.o src/LineParser.c 
	
#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f bin/*.o myshell