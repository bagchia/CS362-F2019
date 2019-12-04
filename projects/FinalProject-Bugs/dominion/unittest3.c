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

    struct gameState G, G_2, G_3, G_4;
    struct gameState pre_1;

    int k[10] = {ambassador, council_room, tribute, gardens, mine,
                 remodel, smithy, village, baron, minion
                };

    seed = 10;
    numPlayers = 1;
    numOpponents = 0;
    player = 0;

    printf ("** Testing remodel incorrectly comparing the cost of cards to exchange **\n");

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
    memcpy(&G_3, &G, sizeof(struct gameState));
    memcpy(&G_4, &G, sizeof(struct gameState));

    // 1: give player baron
    G.hand[player][1] = baron;

    // 2: give player smithy
    G_2.hand[player][1] = smithy;

    // 3: give player embargo
    G_3.hand[player][1] = embargo;

    // 4: give player outpost
    G_4.hand[player][1] = outpost;

    // have player play the remodel and choose to reveal their curse card (2 of them)
    int out1 = cardEffect(remodel, 1, great_hall, 0, &G, 0, NULL);
    int out2 = cardEffect(remodel, 1, gold, 0, &G_2, 0, NULL);
    int out3 = cardEffect(remodel, 1, council_room, 0, &G_3, 0, NULL);
    int out4 = cardEffect(remodel, 1, duchy, 0, &G_4, 0, NULL);

    // assertions for G
    myAssert(isCardInHand(great_hall, &G, player) == TRUE, "correct card now in player's hand");
    myAssert(isCardInHand(baron, &G, player) == FALSE, "old card is no longer in player's hand");
    myAssert(isCardInDiscard(baron, &G, player) == FALSE, "old card is no longer in player's discard pile");

    // assertions for G_2
    myAssert(isCardInHand(gold, &G, player) == TRUE, "correct treasure now in player's hand");
    myAssert(isCardInHand(smithy, &G, player) == FALSE, "old treasure is no longer in player's hand");
    myAssert(isCardInDiscard(smithy, &G, player) == FALSE, "old treasure is no longer in player's discard pile");

    // assertions for G_3
    myAssert(out3 == -1, "invalid exchange returns -1");
    myAssert(isCardInHand(council_room, &G, player) == FALSE, "desired card card not in player's deck");
    myAssert(isCardInHand(embargo, &G, player) == TRUE, "card to be trashed not in player's deck");

    // assertions for G_4
    myAssert(isCardInHand(duchy, &G, player) == TRUE, "correct card now in player's hand");
    myAssert(isCardInDiscard(outpost, &G, player) == FALSE, "old card is no longer in player's discard pile");

    exit(0);

}