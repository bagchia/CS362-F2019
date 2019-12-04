#include "dominion.h"
#include "dominion_helpers.h"
#include "test_assert.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TRUE 1
#define FALSE 0

int myAssert(int a, char* msg)
{
    test_bool(a, msg);
}

int countCardsInHand(int supplyPos, struct gameState *state, int player)
{
    int i, count = 0;
    for(i = 0; i < state->handCount[player]; i++)
    {
        if(state->hand[player][i] == supplyPos)
            count++;
    }
    return count;
}

int isCardInHand(int supplyPos, struct gameState *state, int player)
{
    int i;
    for(i = 0; i < state->handCount[player]; i++)
    {
        if(state->hand[player][i] == supplyPos)
            return TRUE;
    }
    return FALSE;
}

int isCardInDeck(int supplyPos, struct gameState *state, int player)
{
    int i;
    for(i = 0; i < state->deckCount[player]; i++)
    {
        if(state->deck[player][i] == supplyPos)
            return TRUE;
    }
    return FALSE;
}

int isCardInDiscard(int supplyPos, struct gameState *state, int player)
{
    int i;
    for(i = 0; i < state->discardCount[player]; i++)
    {
        if(state->discard[player][i] == supplyPos)
            return TRUE;
    }
    return FALSE;
}

int main () {

    int numPlayers, player, numOpponents, opponent1, coins, p, deckCount, discardCount, handCount, seed, i;

    struct gameState G, G_2;
    struct gameState pre_1;

    int k[10] = {ambassador, council_room, tribute, gardens, mine,
                 remodel, smithy, village, baron, minion
                };

    seed = 10;
    numPlayers = 2;
    numOpponents = 0;
    player = 0;

    printf ("** Testing isGameOver checking all 27 supply piles **\n");

    //
    // check that mine replaced treasure with another treasute vosting up to 3 more than it.
    //

    // 1: test copper to silver
    // 2: test silver to gold
    // 3: test copper to gold (should fail)
    // 4: boundary case for gold

    initializeGame(numPlayers, k, seed, &G);

    // 1: give player a remodel card
    G.handCount[player] = 2;
    G.hand[player][0] = remodel;

    G.whoseTurn = player;

    // create copies of game state for test. also create control game state pre_1
    memcpy(&pre_1, &G, sizeof(struct gameState));
    memcpy(&G_2, &G, sizeof(struct gameState));

    // 1: set supply piles to 0
    G.supplyCount[sea_hag] = 0;
    G.supplyCount[treasure_map] = 0;
    G.supplyCount[smithy] = 0;

    // 2: set other supply piles to 0
    G_2.supplyCount[smithy] = 0;
    G_2.supplyCount[embargo] = 0;
    G_2.supplyCount[council_room] = 0;

    int out1 = isGameOver(&G);
    int out2 = isGameOver(&G_2);

    // assertions for G_4
    myAssert(out1 == 1, "Game should be over");
    myAssert(out2 == 1, "Game should be over");

    exit(0);

}