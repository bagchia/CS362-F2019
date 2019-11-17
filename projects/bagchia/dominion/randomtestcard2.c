#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "test_assert.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NUM_ITERATIONS 1000;

int main()
{
    srand(time(NULL));
    printf("Random Test 2: Minion\n");
    int r, i;
    int seed = 2;
    int handCount = 5;
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
    r = initializeGame(3, kingdom, seed, &G); // initialize a new game
    G.handCount[0] = handCount;               // set any other variables
    //Fill the player's hand with coppers as a place holder
    for (i = 0; i < 1000; i++)
    {
        int j;
        int hands_five = 0;
        for (j = 0; j < 3; j++)
        {
            G.handCount[j] = rand_range(2, 7);
            if (G.handCount[j] >= 5)
            {
                hands_five++;
            }
            for (int k = 0; k < G.handCount[j]; k++)
            {
                G.hand[j][k] = rand_range(curse, treasure_map);
            }
        }

        int player2_five = 0;
        int old_hand_p2[G.handCount[1]];
        memcpy(old_hand_p2, G.hand[1], sizeof(int) * G.handCount[1]);
        if (G.handCount[1] >= 5)
        {
            player2_five = 1;
        }

        G.hand[0][0] = minion;
        int choice = rand_range(0, 1);
        int old_coins = G.coins;
        int old_hand_count = G.handCount[0];
        int old_played_count = G.playedCardCount;
        int old_deck_count = G.deckCount[0];
        int num_minions = count_array(G.hand[0], G.handCount[0], minion);
        int played_minions = count_array(G.playedCards, G.playedCardCount, minion);
        int old_hand[G.handCount[0]];
        memcpy(old_hand, G.hand[0], sizeof(int) * G.handCount[0]);

        for (j = 0; j < 3; j++)
        {
            printHand(j, &G);
        }

        if (choice == 0)
        {
            minionEffect(1, 0, &G, 0);
        }
        else
        {
            minionEffect(0, 1, &G, 0);
        }
        printf("Playing Minion with choice = %d\n", choice);
        if (choice == 0)
        {
            test_bool(count_array(G.hand[0], G.handCount[0], minion) == num_minions - 1, "The player now has 1 less minion in hand");
            test_bool(count_array(G.playedCards, G.playedCardCount, minion) == played_minions + 1, "There is exactly 1 more minion in the played cards");
            test_bool(G.coins == old_coins + 2, "The number of coins has increased by exactly 2");
        }
        else
        {
            test_bool(count_array(G.hand[0], G.handCount[0], minion) == num_minions - 1, "The player now has 1 less minion in hand");
            test_bool(count_array(G.playedCards, G.playedCardCount, minion) == played_minions + 1, "There is exactly 1 more minion in the played cards");
            test_bool(memcmp(old_hand, G.hand[0], sizeof(int) * G.handCount[0]) != 0, "Current player got a new hand");
            test_bool(G.handCount[0] == 4, "Current player has 4 cards");
            if (player2_five)
            {
                test_bool(memcmp(old_hand_p2, G.hand[1], sizeof(int) * G.handCount[1]) == 0, "Player with > 5 cards got a new hand");
            }
        }
    }
}