#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "test_assert.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main()
{
    srand(time(NULL));
    printf("Unit Test 6: Score is incorrectly calculated using the discard pile size when enumerating the player’s deck\n");
    int r, i;
    int seed = 2 ;
    // set your card array
    int kingdom[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    // declare the game state
    struct gameState G;
    // declare the arrays
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];

    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
    //
    // set the state of your variables
    // comment on what this is going to test
    //
    memset(&G, 23, sizeof(struct gameState)); // set the game state
    r = initializeGame(2, kingdom, seed, &G); // initialize a new game
    G.hand[0][0] = curse;
    G.handCount[0] = 1;
    G.discard[0][0] = province;
    G.discardCount[0] = 1;
    G.deck[0][0] = estate;
    G.deck[0][1] = estate;
    G.deck[0][2] = estate;
    G.deckCount[0] = 3;

    printHand(0, &G);
    printDeck(0, &G);
    printDiscard(0, &G);

    printf("Calculating player 0's score\n");

    int score = scoreFor(0, &G);
    test_bool(score == 8, "Player 0's score is exactly 8");
    
}