# paths in which make will search for files which are not present in current directory
VPATH = src/constraints 		\
		src/insert_operator  	\
		src/tools 				\
		src 					

# for preprocessing of header file
FLAGS 	= -I include

# basic variables needed
GCC   	= gcc 
MAIN.c 	= main.c
-C      = -c
-O 		= -o
-LM   	= -lm
-G 		= -g

# which purticular type of file to search from purticular directory
vpath %.c src/constraints
vpath %.h include

#rules 

# main target
result: capacity_constraint.o compute_obj.o deadline_constraint.o insert_precalculate.o ridesharing.o mathematics.o main.c
	$(GCC) $(FLAGS) $^ $(-LM) $(-G) $(-O) $@

capacity_constraint.o: capacity_constraint.c 
compute_obj.o: compute_obj.c
deadline_constraint.o: deadline_constraint.c 
insert_precalculate.o: insert_precalculate.c
ridesharing.o: ridesharing.c
mathematics.o: mathematics.c

%.o: %.c
	$(GCC) $(FLAGS) $(-LM) $(-C) $<

.PHONY: clean
clean:
	rm *.o

