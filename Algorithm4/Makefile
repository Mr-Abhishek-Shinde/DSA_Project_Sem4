# paths in which make will search for files which are not present in current directory
VPATH = src

# for preprocessing of header file
HFLAGS 	= -I include

# basic variables needed
GCC   	= gcc 
MAIN.c 	= main.c
FLAG 	= -Wall -lm -g -c -o
-C      = -c

# which purticular type of file to search from purticular directory
vpath %.c src
vpath %.h include


#rules 

result: 
	$(GCC) $(HFLAGS) $(^) $(FLAG) $@

%.o: %.c
	$(GCC) $(HFLAGS) $(-C) $(FLAG) $<

.PHONY: clean
clean:
	rm *.o
