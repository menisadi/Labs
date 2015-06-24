#format is target-name: target dependencies
#{-tab-}actions

# All Targets
all: dirs bin/digit_cnt 

# Tool invocations
bin/digit_cnt: lib/digit_cnt.o
	gcc -g -m32 -Wall -o bin/digit_cnt lib/digit_cnt.o

# Depends on the source and header files
lib/digit_cnt.o: digit_cnt.c 
	gcc -m32 -g -Wall -ansi -c -o lib/digit_cnt.o digit_cnt.c 


#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f lib/* bin/*

dirs: 
	mkdir -p bin lib 
	
	
