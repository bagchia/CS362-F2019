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
    printf("Unit Test 7: Tribute revealed cards reward calculation behaves unpredictably\n");
    int r, i;
    int seed = 2;
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
    G.hand[0][0] = tribute;
    G.deck[1][0] = copper;
    G.deck[1][1] = silver;
    int old_deck_count = G.deckCount[0];
    int old_hand_count = G.handCount[0];
    int old_actions = G.numActions;
    int old_coins = G.coins;
    int bonus = 0;
    int old_bonus = bonus;

    printf("Coins %d\n", bonus);

    printf("Playing player 0's tribute\n");

    cardEffect(tribute, 0, 0, 0, &G, 0, &bonus);
    printf("Coins %d\n", bonus);

    test_bool(bonus == old_bonus + 2, "Bonus has increased by exactly 4");
    test_bool(G.numActions == old_actions, "Number of actions are the same");
    test_bool(G.handCount[0] == old_hand_count, "Number of cards in hand stays the same");
}