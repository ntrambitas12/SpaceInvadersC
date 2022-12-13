
#NAME: Nicholas Trambitas
#Makefile for lab 3.


#change the last dependency for each new lab
all: lab4 lab4u 

#this entry has to change for lab 2 - 4
# NEVER compile .c files with this rule - it lacks needed compile time flags
# There is an entry below that turns .c files into .o files

#build for lab4
lab4: lab4.o output.o motion.o code.o memory.o functions.o reliable.o linkedlist.o
	gcc -g -o $@ $^ -lncurses -L. -linvaders 
#build for lab4 unreliable
lab4u: lab4.o output.o motion.o code.o memory.o functions.o unreliable.o linkedlist.o
	gcc -g -o $@ $^ -lncurses -L. -linvaders 



#this is where you create an entry to build your zip file
#it will also update with new labs

lab4.zip:	makefile proto1.c README proto1.h proto2.c proto2.h code.c code.h output.c output.h lab4.c lab4.h motion.c motion.h debug.h framerate.h memory.c memory.h functions.c functions.h linkedlist.c linkedlist.h struct.h proto3.h proto3.c linkedlistproto.c linkedlistproto.h linkedlistproto2.c linkedlistproto2.h lab3ARGC.c lab3ARGC.h altmem.h reliable.o unreliable.o invaders.h libinvaders.a
	# create the zip file
	zip $@ $^


#this entry stays for C code labs
tags: *.c
	ctags -R .

# this entry stays for C code labs
headers: *.c tags
	headers.sh


# this entry takes care of C files depending on header files
# It has the flags for compiling the c code
# It you don't like makefiles, consider typing the following line a few
# thousand times this semester and reconsider.
# Be sure that this one doesn't get an inserted line break anywhere
%.o:%.c *.h
	gcc -ansi -pedantic -Wimplicit-function-declaration -Wreturn-type -g -c $< -o $@


