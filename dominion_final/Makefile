CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest_bug6: unittest_bug6.c dominion.o rngs.o interface.o
	gcc -o unittest_bug6 -g  unittest_bug6.c interface.o dominion.o rngs.o -coverage $(CFLAGS)

unittest_bug7: unittest_bug7.c dominion.o rngs.o interface.o
	gcc -o unittest_bug7 -g  unittest_bug7.c interface.o dominion.o rngs.o -coverage $(CFLAGS)


unittestresults: clean unittest_bug6 unittest_bug7
	unittest_bug6 > unittestresults.out
	echo -e "\n\n" >> unittestresults.out
	unittest_bug7 >> unittestresults.out
	echo -e "\n\n" >> unittestresults.out

	echo -e "\n\nCoverage Results:\n" >> unittestresults.out
	gcov dominion.gcda -b -f >> unittestresults.out




player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
