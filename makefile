#
# This is an example Makefile for a countwords program.  This
# program uses both the scanner module and a counter module.
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = g++
STD = c++11
CFLAGS  = -g -Wall
MAIN = Casino

#Source files
SRCS = Main.cpp CardDeck.cpp ACard.cpp Account.cpp  InsertionSort.cpp BlackJack.cpp Poker.cpp

OBJS = $(SRCS:.cpp=.o)

.PHONY: depend clean

all: $(MAIN)
	@echo build Complete

$(MAIN):$(OBJS)
	$(CC) $(CFLAGS) -std=$(STD) -o $(MAIN) $(OBJS)	


#default: Lab4

# To create the executable file count we need the object files
#
#
#Lab4:  Lab4.o Sorting_Algorithms.o
#	$(CC) $(CFLAGS) -o $(MAIN) Lab4.o Sorting_Algorithms.o
#
#Lab4.o: Lab4.cpp
#	$(CC) $(CFLAGS) -c Lab4.cpp
#
#orting_Algorithms.o: Sorting_Algorithms.cpp Sorting_Algorithms.h
#	$(CC) $(CFLAGS) -c Sorting_Algorithms.cpp
#
# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#

run:
	./$(MAIN)

.cpp.o:
	$(CC) $(CFLAGS) -std=$(STD) -c $< -o $@

clean: 
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $^

# DO NOT DELETE THIS LINE -- make depend needs it

test.o: /usr/include/stdlib.h /usr/include/features.h
test.o: /usr/include/stdc-predef.h /usr/include/alloca.h /usr/include/time.h
test.o: /usr/include/xlocale.h Poker.h CardDeck.h ACard.h Account.h
test.o: DisplayMod.h
CardDeck.o: /usr/include/stdlib.h /usr/include/features.h
CardDeck.o: /usr/include/stdc-predef.h /usr/include/alloca.h
CardDeck.o: /usr/include/time.h /usr/include/xlocale.h CardDeck.h ACard.h
ACard.o: ACard.h
Account.o: Account.h DisplayMod.h
Poker.o: /usr/include/stdlib.h /usr/include/features.h
Poker.o: /usr/include/stdc-predef.h /usr/include/alloca.h Poker.h CardDeck.h
Poker.o: ACard.h Account.h DisplayMod.h InsertionSort.h InsertionSort.cpp
