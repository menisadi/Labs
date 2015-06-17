PROGRAM = print


all: $(PROGRAM)

$(PROGRAM) : $(PROGRAM).o
	gcc -std=gnu99 -g -m32 -Wall -o $(PROGRAM) $(PROGRAM).o
	
$(PROGRAM).o : $(PROGRAM).c
	gcc -std=gnu99  -g -Wall -m32 -ansi -c -o $(PROGRAM).o $(PROGRAM).c

.PHONY : clean

clean : 
	rm -f *.o $(PROGRAM)