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


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
	gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o interface.o
	gcc -o unittest1 -g  unittest1.c interface.o dominion.o rngs.o -coverage $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o interface.o
	gcc -o unittest2 -g  unittest2.c interface.o dominion.o rngs.o -coverage $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o interface.o
	gcc -o unittest3 -g  unittest3.c interface.o dominion.o rngs.o -coverage $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o interface.o
	gcc -o unittest4 -g  unittest4.c interface.o dominion.o rngs.o -coverage $(CFLAGS)

unittest5: unittest5.c dominion.o rngs.o interface.o
	gcc -o unittest5 -g  unittest5.c interface.o dominion.o rngs.o -coverage $(CFLAGS)

unittestresults: clean unittest1 unittest2 unittest3 unittest4 unittest5
	unittest1 > unittestresults.out
	echo -e "\n\n" >> unittestresults.out
	unittest2 >> unittestresults.out
	echo -e "\n\n" >> unittestresults.out
	unittest3 >> unittestresults.out
	echo -e "\n\n" >> unittestresults.out
	unittest4 >> unittestresults.out
	echo -e "\n\n" >> unittestresults.out
	unittest5 >> unittestresults.out
	echo -e "\n\nCoverage Results:\n" >> unittestresults.out
	gcov dominion.gcda -b -f >> unittestresults.out
clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
