#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: mypipeline

# Tool invocations
mypipeline: bin/mypipeline.o
	gcc -m32 -g -Wall -o mypipeline bin/mypipeline.o
# Depends on the source and header files
bin/mypipeline.o: src/mypipeline.c
	gcc -g -Wall -m32 -ansi -c -o bin/mypipeline.o src/mypipeline.c 

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f bin/*.o mypipeline