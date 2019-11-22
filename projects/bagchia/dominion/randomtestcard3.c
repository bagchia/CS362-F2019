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
    printf("Random Test 3: Tribute\n");
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
    //Give the three players random hands
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

        int old_hand_p2[G.handCount[1]];
        memcpy(old_hand_p2, G.hand[1], sizeof(int) * G.handCount[1]);
        int revealed_cards[2] = {G.hand[1][0], G.hand[0][1]};
        G.hand[0][0] = tribute;
        int num_treasure;
        int num_action;
        int num_victory;
        for (int j = 0; j <= 2; j++)
        {
            if (revealed_cards[i] == copper || revealed_cards[i] == silver || revealed_cards[i] == gold)
            { //Treasure cards
                num_treasure++;
            }

            else if (revealed_cards[i] == estate || revealed_cards[i] == duchy || revealed_cards[i] == province || revealed_cards[i] == gardens || revealed_cards[i] == great_hall)
            { //Victory Card Found
                num_action++;
            }
            else
            { //Action Card
                num_victory++;
            }
        }
        int old_coins = G.coins;
        int old_num_actions = G.numActions;
        int old_hand_count = G.handCount[0];
        int old_played_count = G.playedCardCount;
        int old_deck_count = G.deckCount[0];
        int old_p2_deck_count = G.deckCount[1];
        int num_minions = count_array(G.hand[0], G.handCount[0], minion);
        int played_minions = count_array(G.playedCards, G.playedCardCount, minion);
        int old_hand[G.handCount[0]];
        memcpy(old_hand, G.hand[0], sizeof(int) * G.handCount[0]);

        printHand(1, &G);
        printf("Playing Baron\n");
        tributeEffect(&G);
        test_bool(G.coins = old_coins + 2*num_treasure, "Player gained the appropriate amount of gold");
        test_bool(G.numActions == old_num_actions + 2*num_action, "Player gained the appropriate number of actions");
        test_bool(G.deckCount[0] == old_deck_count + 2*num_victory, "Player gained the approrpriate number of cards");
        test_bool(G.deckCount[1] == old_p2_deck_count -2, "Left player discarded 2 cards");
    }
}