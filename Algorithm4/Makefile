# paths in which make will search for files which are not present in current directory
VPATH = src/segment_tree 		\
		src/insert_operator 	\
		src

# for preprocessing of header file
IFLAGS 	= -I include

# basic variables needed
GCC   	= gcc 
MAIN.c 	= main.c
FLAG 	= -lm -Wall -g 
-O      = -o
-C      = -c

# which purticular type of file to search from purticular directory
vpath %.c src
vpath %.h include


#rules 

result: constraints.o precalculation.o searching_and_sorting.o time_functions.o tools.o main.c
	$(GCC) $(IFLAGS) $(^) $(FLAG) $@

constraints.o: constraints.c
precalculation.o: precalculation.c
searching_and_sorting.o: searching_and_sorting.c
time_functions.o: time_functions.c
tools.o: tools.c
insertion_operator.o: insertion_operator.c
ridesharing.o: ridesharing.c
segment_tree.o: segment_tree.c

%.o: %.c
	$(GCC) $(IFLAGS) $(-C) $(FLAG) $< 

.PHONY: clean
clean:
	rm *.o
