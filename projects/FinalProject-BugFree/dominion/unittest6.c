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
    printf("Unit Test 6: Feast card incorrectly decides which cards are too expensive\n");
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
    G.hand[0][0] = feast;
    G.handCount[0] = 1;
    G.deckCount[0] = 0;
    G.discardCount[0] = 0;
    G.coins = 0;
    
    int old_num_feasts_hand = count_array(G.hand[0], G.handCount[0], feast);
    int old_num_estates_deck = count_array(G.deck[0], G.deckCount[0], estate);
    int old_discard_count = G.discardCount[0];
    int old_hand_count = G.handCount[0];
    int old_coins = G.coins;
    int bonus = 0;
    int old_bonus = bonus;


    printf("Playing player 0's feast for an estate\n");

    cardEffect(feast, estate, 0 , 0, &G, 0, &bonus);

    test_bool(count_array(G.hand[0], G.handCount[0], feast) == old_num_feasts_hand - 1, "1 less feast in player 0's hand");
    test_bool(count_array(G.discard[0], G.discardCount[0], estate) == old_num_estates_deck + 1, "1 more estate in player 0's discard");
    test_bool(G.handCount[0] == old_hand_count - 1, "Player 0's hand size decreased by 1");
    test_bool(G.coins == old_coins, "Coins are unchanged");
    test_bool(bonus == old_bonus, "Bonus is unchanged");
}